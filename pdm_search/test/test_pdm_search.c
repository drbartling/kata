
#include "pdm_search.h"
#include "unity.h"

#define sequenceSize (3)
#define sequenceLength ((1 << sequenceSize) - 1)

uint32_t        taps                         = 0x6;
static uint32_t testSequence[sequenceLength] = {
      0x5, 0x4, 0x2, 0x1, 0x6, 0x3, 0x7};
static uint32_t testSequenceLSB[sequenceLength] = {1, 0, 0, 1, 0, 1, 1};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Shift_returns_nextSequenceStep_when_GivenSizeThreeTaps(void)
{
    uint32_t reg                            = 0x7;
    uint32_t actualSequence[sequenceLength] = {0};

    for (int i = 0; i < sequenceLength; ++i)
    {
        reg               = LFSR_Shift(reg, taps);
        actualSequence[i] = reg;
    }

    TEST_ASSERT_EQUAL_UINT32_ARRAY(
          testSequence, actualSequence, sequenceLength);
}

void test_PhaseShift_returns_GivenSequence_when_shiftIsZero(void)
{
    uint32_t returnedSequence[sequenceLength] = {0};

    PDM_PhaseShift(testSequenceLSB, returnedSequence, sequenceLength, 0);

    TEST_ASSERT_EQUAL_UINT32_ARRAY(
          testSequenceLSB, returnedSequence, sequenceLength);
}

void test_PhaseShift_returns_RightShiftedSequence_when_shiftIsGreaterThan0(void)
{
    uint32_t returnedSequence[sequenceLength] = {0};
    int      shift                            = 2;
    //                                    was   {1, 0, 0, 1, 0, 1, 1}
    uint32_t expectedSequence[sequenceLength] = {1, 1, 1, 0, 0, 1, 0};

    PDM_PhaseShift(testSequenceLSB, returnedSequence, sequenceLength, shift);

    TEST_ASSERT_EQUAL_UINT32_ARRAY(
          expectedSequence, returnedSequence, sequenceLength);
}

void test_PhaseShift_CanUseGivenArrayAsTheReturnArray(void)
{
    int      shift                    = 5;
    uint32_t sequence[sequenceLength] = {1, 1, 1, 0, 0, 1, 0};

    PDM_PhaseShift(sequence, sequence, sequenceLength, shift);

    TEST_ASSERT_EQUAL_UINT32_ARRAY(testSequenceLSB, sequence, sequenceLength);
}

void test_PhaseShift_returns_RightShiftedSequence_when_shift_IsLessThan0(void)
{
    uint32_t returnedSequence[sequenceLength] = {0};
    int      shift                            = -2;
    //                                    was   {1, 0, 0, 1, 0, 1, 1}
    uint32_t expectedSequence[sequenceLength] = {0, 1, 0, 1, 1, 1, 0};

    PDM_PhaseShift(testSequenceLSB, returnedSequence, sequenceLength, shift);

    TEST_ASSERT_EQUAL_UINT32_ARRAY(
          expectedSequence, returnedSequence, sequenceLength);
}

void test_PhaseShift_CanShiftByLargeNegativeValues(void)
{
    uint32_t returnedSequence[sequenceLength] = {0};
    int      shift                            = -(3 + 7);
    //                                    was   {1, 0, 0, 1, 0, 1, 1}
    uint32_t expectedSequence[sequenceLength] = {1, 0, 1, 1, 1, 0, 0};

    PDM_PhaseShift(testSequenceLSB, returnedSequence, sequenceLength, shift);

    TEST_ASSERT_EQUAL_UINT32_ARRAY(
          expectedSequence, returnedSequence, sequenceLength);
}

void test_PhaseAmplitude_Returns_SameResultAs_PhaseShift_when_GivenOnePhase(
      void)
{
    int shift = 4;

    uint32_t expectedSequence[sequenceLength] = {0};
    PDM_PhaseShift(testSequenceLSB, expectedSequence, sequenceLength, shift);

    uint32_t amplitudes[sequenceLength] = {0};
    PDM_PhaseAmplitude(testSequenceLSB, sequenceLength, &shift, 1, amplitudes);

    TEST_ASSERT_EQUAL_UINT32_ARRAY(
          expectedSequence, amplitudes, sequenceLength);
}

void test_PhaseAmplitudeCombinations(void)
{
    int shifts1[2] = {0, 2};
    //                                {1, 0, 0, 1, 0, 1, 1}
    //                                {1, 1, 1, 0, 0, 1, 0}
    uint32_t expectedAmplitudes1[7] = {2, 1, 1, 1, 0, 2, 1};

    uint32_t amplitudes[sequenceLength] = {0};
    PDM_PhaseAmplitude(testSequenceLSB, sequenceLength, shifts1, 2, amplitudes);

    TEST_ASSERT_EQUAL_UINT32_ARRAY(
          expectedAmplitudes1, amplitudes, sequenceLength);

    int shifts2[2] = {0, 3};
    //                                {1, 0, 0, 1, 0, 1, 1}
    //                                {0, 1, 1, 1, 0, 0, 1}
    uint32_t expectedAmplitudes2[7] = {1, 1, 1, 2, 0, 1, 2};

    PDM_PhaseAmplitude(testSequenceLSB, sequenceLength, shifts2, 2, amplitudes);

    TEST_ASSERT_EQUAL_UINT32_ARRAY(
          expectedAmplitudes2, amplitudes, sequenceLength);

    int shifts3[3] = {0, 2, 3};
    //                                {1, 0, 0, 1, 0, 1, 1}
    //                                {1, 1, 1, 0, 0, 1, 0}
    //                                {0, 1, 1, 1, 0, 0, 1}
    uint32_t expectedAmplitudes3[7] = {2, 2, 2, 2, 0, 2, 2};

    PDM_PhaseAmplitude(testSequenceLSB, sequenceLength, shifts3, 3, amplitudes);

    TEST_ASSERT_EQUAL_UINT32_ARRAY(
          expectedAmplitudes3, amplitudes, sequenceLength);
}

void test_AmplitudesListGet_returns_ListOfUniqueValuesForAmplitudes(void)
{
    uint32_t result[7] = {0};

    uint32_t amplitudes1[7] = {2, 1, 2, 3, 1, 1, 2};
    PDM_AmplitudesListGet(amplitudes1, result, 7);
    uint32_t expectedResult1[7] = {3, 1, 2, 3, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expectedResult1, result, 7);

    uint32_t amplitudes2[7] = {2, 1, 1, 2, 0, 1, 2};
    PDM_AmplitudesListGet(amplitudes2, result, 7);
    uint32_t expectedResult2[7] = {3, 0, 1, 2, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expectedResult2, result, 7);

    uint32_t amplitudes3[7] = {0, 2, 1, 2, 0, 1, 2};
    PDM_AmplitudesListGet(amplitudes3, result, 7);
    uint32_t expectedResult3[7] = {3, 0, 1, 2, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expectedResult3, result, 7);

    uint32_t amplitudes4[7] = {2, 2, 2, 2, 0, 2, 2};
    PDM_AmplitudesListGet(amplitudes4, result, 7);
    uint32_t expectedResult4[7] = {2, 0, 2, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expectedResult4, result, 7);
}

void test_PhaseScore(void)
{
    int   shifts[2] = {0, 2};
    float score     = PDM_PhaseScore(taps, shifts, 2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.64, score);

    int shifts1[3] = {0, 2, 3};
    score          = PDM_PhaseScore(taps, shifts1, 3);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.71, score);
}

void test_PhaseBestScore(void)
{
    int   shifts[7] = {0};
    float score     = PDM_PhaseScoreBest(taps, shifts, 1);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.5, score);
    int expectedShift1[7] = {0};
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expectedShift1, shifts, 7);

    score = PDM_PhaseScoreBest(taps, shifts, 2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.57, score);
    int expectedShift2[7] = {0, 1};
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expectedShift2, shifts, 7);

    score = PDM_PhaseScoreBest(taps, shifts, 3);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.71, score);
    int expectedShift3[7] = {0, 2, 3};
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expectedShift3, shifts, 7);
}

void test_ShiftNext_Should_ReturnFalse_when_NoNextShiftRemains(void)
{
    int shifts[7]    = {0};
    int expected1[7] = {0};
    TEST_ASSERT_FALSE(PDM_ShiftNext(shifts, 1, 7));
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected1, shifts, 7);

    shifts[1]        = 6;
    int expected2[7] = {0, 6};
    TEST_ASSERT_FALSE(PDM_ShiftNext(shifts, 2, 7));
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected2, shifts, 7);

    shifts[2]        = 6;
    shifts[1]        = 5;
    int expected3[7] = {0, 5, 6};
    TEST_ASSERT_FALSE(PDM_ShiftNext(shifts, 3, 7));
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected3, shifts, 7);
}

void test_ShiftNext_should_InitializeToFirstShift(void)
{
    int shifts1[7]   = {0};
    int expected1[7] = {0, 1};
    TEST_ASSERT_TRUE(PDM_ShiftNext(shifts1, 2, 7));
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected1, shifts1, 7);

    int shifts2[7]   = {0};
    int expected2[7] = {0, 1, 2};
    TEST_ASSERT_TRUE(PDM_ShiftNext(shifts2, 3, 7));
    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected2, shifts2, 7);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Shift_returns_nextSequenceStep_when_GivenSizeThreeTaps);
    RUN_TEST(test_PhaseShift_returns_GivenSequence_when_shiftIsZero);
    RUN_TEST(
          test_PhaseShift_returns_RightShiftedSequence_when_shiftIsGreaterThan0);
    RUN_TEST(test_PhaseShift_CanUseGivenArrayAsTheReturnArray);
    RUN_TEST(
          test_PhaseShift_returns_RightShiftedSequence_when_shift_IsLessThan0);
    RUN_TEST(test_PhaseShift_CanShiftByLargeNegativeValues);
    RUN_TEST(
          test_PhaseAmplitude_Returns_SameResultAs_PhaseShift_when_GivenOnePhase);
    RUN_TEST(test_PhaseAmplitudeCombinations);
    RUN_TEST(test_AmplitudesListGet_returns_ListOfUniqueValuesForAmplitudes);
    RUN_TEST(test_PhaseScore);
    RUN_TEST(test_PhaseBestScore);
    RUN_TEST(test_ShiftNext_Should_ReturnFalse_when_NoNextShiftRemains);
    RUN_TEST(test_ShiftNext_should_InitializeToFirstShift);
    UNITY_END();
    return 0;
}

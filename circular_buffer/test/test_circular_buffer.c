
#include "unity.h"
#include "circular_buffer.h"

#define ArrayLength(x) (sizeof(x)/sizeof(x[0]))
#define EnumExpected(x) "Expected: " #x

void setUp(void) {
    CBF_BufferClear();
}

void tearDown(void) {
}

void test_BufferPut_should_ReturnSuccessWhenBufferIsNotFull(void) {

    TEST_ASSERT_EQUAL_MESSAGE(CBF_SUCCESS, CBF_BufferPut(42),
            EnumExpected(CBF_SUCCESS));
}

void test_BufferGet_should_ReturnSuccess_when_BuffferIsNotEmpty(void) {
    (void) CBF_BufferPut(42);
    CBF_DATA_T dataOut = 0;

    TEST_ASSERT_EQUAL_MESSAGE(CBF_SUCCESS, CBF_BufferGet(&dataOut),
            EnumExpected(CBF_SUCCESS));
}

void test_BufferGet_should_ReturnDataPutIntoBufferBy_BufferPut(void) {

    CBF_DATA_T dataIn = 35;
    CBF_DATA_T dataOut = 0;

    (void) CBF_BufferPut(dataIn);
    (void) CBF_BufferGet(&dataOut);
    TEST_ASSERT_EQUAL(dataIn, dataOut);

    dataIn = 1000;
    (void) CBF_BufferPut(dataIn);
    (void) CBF_BufferGet(&dataOut);
    TEST_ASSERT_EQUAL(dataIn, dataOut);

    dataIn = -1000;
    (void) CBF_BufferPut(dataIn);
    (void) CBF_BufferGet(&dataOut);
    TEST_ASSERT_EQUAL(dataIn, dataOut);
}

void test_BufferGet_should_ReturnDataPutIntoBufferBy_BufferPut_InOrder(void) {
    CBF_DATA_T dataIn[] = {42, 54, 21, 32, 1000, -1000};
    CBF_DATA_T dataOut[ArrayLength(dataIn)] = {0};

    for (int i = 0; i < ArrayLength(dataIn); i++) {
        CBF_BufferPut(dataIn[i]);
    }

    for (int i = 0; i < ArrayLength(dataIn); i++) {

        CBF_BufferGet(&dataOut[i]);
    }

    TEST_ASSERT_EQUAL_INT16_ARRAY(dataIn, dataOut, ArrayLength(dataIn));
}

void test_BufferGet_should_ReturnUnderflow_when_ReadingFromAnEmptyBuffer(void) {

    CBF_DATA_T dataOut = 0;
    TEST_ASSERT_EQUAL_MESSAGE(CBF_UNDERFLOW, CBF_BufferGet(&dataOut),
            EnumExpected(CBF_UNDERFLOW));
}

void test_BufferPut_should_ReturnOverflow_when_WritingToAFullBuffer(void) {
    for (int i = 0; i < CBF_BUFFER_SIZE - 1; i++) {

        TEST_ASSERT_EQUAL_MESSAGE(CBF_SUCCESS, CBF_BufferPut(i),
                EnumExpected(CBF_SUCCESS));
    }
    TEST_ASSERT_EQUAL_MESSAGE(CBF_OVERFLOW, CBF_BufferPut(42),
            EnumExpected(CBF_OVERFLOW));
}

void test_BufferClear_should_MakeTheCircularBufferEmpty(void) {
    (void) CBF_BufferPut(1681);
    CBF_BufferClear();

    CBF_DATA_T dataOut = 0;
    TEST_ASSERT_EQUAL_MESSAGE(CBF_UNDERFLOW, CBF_BufferGet(&dataOut),
            EnumExpected(CBF_UNDERFLOW));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_BufferPut_should_ReturnSuccessWhenBufferIsNotFull);
    RUN_TEST(test_BufferGet_should_ReturnSuccess_when_BuffferIsNotEmpty);
    RUN_TEST(test_BufferGet_should_ReturnDataPutIntoBufferBy_BufferPut);
    RUN_TEST(test_BufferGet_should_ReturnDataPutIntoBufferBy_BufferPut_InOrder);
    RUN_TEST(test_BufferGet_should_ReturnUnderflow_when_ReadingFromAnEmptyBuffer);
    RUN_TEST(test_BufferPut_should_ReturnOverflow_when_WritingToAFullBuffer);
    RUN_TEST(test_BufferClear_should_MakeTheCircularBufferEmpty);
    return UNITY_END();
}


//
// Section: Included Files
//

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "pdm_search.h"

//
// Section: Constants
//

//
// Section: Global Variable Declarations
//

//
// Section: Macros
//

//
// Section: Static Function Prototypes
//

//
// Section: Static Function Definitions
//

//
// Section:  Module APIs
//

uint32_t LFSR_Shift(uint32_t reg, uint32_t taps)
{
    uint32_t lsb      = reg & 1;
    uint32_t feedback = -lsb;
    reg >>= 1;
    reg ^= (feedback & taps);
    return reg;
}

int LFSR_Length(uint32_t taps)
{
    int length = 0;
    for (int i = taps; i; i >>= 1)
    {
        length++;
    }
    length = (1 << length) - 1;
    return length;
}

void PDM_AmplitudesListGet(const uint32_t amplitudes[],
                           uint32_t       list[],
                           int            length)
{
    size_t size = sizeof(uint32_t) * length;
    memset(list, 0, size);
    for (int i = 0; i < length; ++i)
    {
        bool found = false;
        int  j;
        for (j = 1; j <= list[0]; ++j)
        {
            if (amplitudes[i] == list[j])
            {
                found = true;
                break;
            }
            if (amplitudes[i] < list[j])
            {
                break;
            }
        }
        if (!found)
        {
            list[0]++;
            int k;
            for (k = list[0]; k > j; k--)
            {
                list[k] = list[k - 1];
            }
            list[k] = amplitudes[i];
        }
    }
}

void PDM_PhaseAmplitude(const uint32_t givenSequence[],
                        int            sequenceLength,
                        const int      shift[],
                        int            shiftCount,
                        uint32_t       amplitudes[])
{
    size_t    size            = sizeof(uint32_t) * sequenceLength;
    uint32_t *shiftedSequence = malloc(size);
    memset(amplitudes, 0, size);
    for (int i = 0; i < shiftCount; ++i)
    {
        PDM_PhaseShift(
              givenSequence, shiftedSequence, sequenceLength, shift[i]);
        for (int j = 0; j < sequenceLength; ++j)
        {
            amplitudes[j] += shiftedSequence[j];
        }
    }
    free(shiftedSequence);
}

float PDM_PhaseScore(uint32_t taps, const int shifts[], int shiftCount)
{
    int length = LFSR_Length(taps);
    size_t size = sizeof(uint32_t) * length;

    uint32_t *sequence = malloc(size);
    uint32_t  reg      = 0x07;
    for (int i = 0; i < length; ++i)
    {
        reg         = LFSR_Shift(reg, taps);
        sequence[i] = reg & 0x1;
    }

    uint32_t *amplitudes = calloc(length, sizeof(uint32_t));

    PDM_PhaseAmplitude(sequence, length, shifts, shiftCount, amplitudes);

    uint32_t *amplitudeList = malloc(size);

    PDM_AmplitudesListGet(amplitudes, amplitudeList, length);

    float score = amplitudeList[0];

    if (0 == amplitudeList[1])
    {
        score -= 0.5;
    }

    score += (float)shifts[shiftCount-1] / (float)length / 2.0;

    free(amplitudeList);
    free(amplitudes);
    free(sequence);

    return score;
}

float PDM_PhaseScoreBest(uint32_t taps, int shifts[], int shiftCount)
{
    size_t size = sizeof(uint32_t) * shiftCount;
    memset(shifts, 0, size);

    int length = LFSR_Length(taps);

    PDM_ShiftNext(shifts, shiftCount, length);

    int *testShifts = calloc(shiftCount, sizeof(int));
    memcpy(testShifts, shifts, size);

    float bestScore = PDM_PhaseScore(taps, testShifts, shiftCount);
    while (PDM_ShiftNext(testShifts, shiftCount, length))
    {
        float testScore = PDM_PhaseScore(taps, testShifts, shiftCount);
        if (testScore < bestScore)
        {
            bestScore = testScore;
            memcpy(shifts, testShifts, size);
        }
    }

    free(testShifts);
    return bestScore;
}

void PDM_PhaseShift(const uint32_t givenSequence[],
                    uint32_t       result[],
                    int            length,
                    int            shift)
{
    size_t    size = sizeof(uint32_t) * length;
    uint32_t *temp = malloc(size);
    memcpy(temp, givenSequence, size);

    shift %= length;
    shift += length;

    for (int i = 0; i < length; ++i)
    {
        result[(i + shift) % length] = temp[i];
    }
    free(temp);
}

bool PDM_Next(int shifts[], int shiftCount, int length)
{
    if (0 == shiftCount)
    {
        return true;
    }

    if (1 == shiftCount)
    {
        int shift = shifts[0] + 1;
        if (shift == length)
        {
            return true;
        }
        else
        {
            shifts[0] = shift;
            return false;
        }
    }

    if (true == PDM_Next(&shifts[1], shiftCount - 1, length))
    {
        int shift = shifts[0] + 1;
        if (shift == shifts[1])
        {
            return true;
        }
        else
        {
            shifts[0] = shift;
            for (int i = 0; i < shiftCount - 1; ++i)
            {
                shifts[i + 1] = shifts[i] + 1;
            }
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool PDM_ShiftNext(int shifts[], int shiftCount, int length)
{
    if (0 == shifts[1] && 1 < shiftCount)
    {
        for (int i = 0; i < shiftCount; ++i)
        {
            shifts[i] = i;
        }
        return true;
    }
    return !PDM_Next(&shifts[1], shiftCount - 1, length);
}

//
// End of File
//

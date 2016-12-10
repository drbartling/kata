
#ifndef PDM_SEARCH_H  // Guards against multiple inclusion
#define PDM_SEARCH_H

//
// Section: Included Files
//

#include <stdbool.h>
#include <stdint.h>

//
// Section: Constants
//

//
// Section: Data Types
//

//
// Section:  Module APIs
//

uint32_t LFSR_Shift(uint32_t reg, uint32_t taps);

void PDM_AmplitudesListGet(const uint32_t amplitudes[],
                           uint32_t       list[],
                           int            length);

void PDM_PhaseAmplitude(const uint32_t givenSequence[],
                        int            sequenceLength,
                        const int      shift[],
                        int            shiftCount,
                        uint32_t       amplitudes[]);

float PDM_PhaseScore(uint32_t taps, const int shifts[], int shiftCount);

float PDM_PhaseScoreBest(uint32_t taps, int shifts[], int shiftCount);

void PDM_PhaseShift(const uint32_t givenSequence[],
                    uint32_t       result[],
                    int            length,
                    int            shift);

bool PDM_ShiftNext(int shifts[], int shiftCount, int length);

#endif

//
// End of File
//

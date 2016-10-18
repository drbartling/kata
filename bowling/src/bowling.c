//
// Section: Included Files
//

#include "bowling.h"
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

//
// Section: Constants
//

//
// Section: Global Variable Declarations
//

static BWL_GAME_SCORE_T BWL_rollScores[BWL_ROLL_COUNT_MAX];
static uint8_t BWL_rollCount;

//
// Section: Macros
//

#define BWL_FrameBaseScore(roll) \
    (BWL_rollScores[roll] + BWL_rollScores[roll + 1])

#define BWL_SpareScore(roll) \
    (BWL_PIN_COUNT_MAX + BWL_rollScores[roll + 2])

#define BWL_FrameIsSpare(roll) \
    (BWL_PIN_COUNT_MAX == BWL_FrameBaseScore(roll))

#define BWL_FrameIsStrike(roll) \
    (BWL_PIN_COUNT_MAX == BWL_rollScores[roll])

#define BWL_StrikeScore(roll) \
    (BWL_PIN_COUNT_MAX + BWL_rollScores[roll + 1] + BWL_rollScores[roll + 2])

//
// Section: Static Function Prototypes
//

//
// Section: Static Function Definitions
//

//
// Section: Bowling APIs
//

void BWL_GameNew(void) {
    BWL_rollCount = 0;
    BWL_Roll(0, BWL_ROLL_COUNT_MAX);
    BWL_rollCount = 0;
}

BWL_GAME_SCORE_T BWL_GameScore(void) {
    BWL_GAME_SCORE_T gameScore = 0;
    for (int frame = 0, roll = 0; frame < BWL_FRAME_COUNT_MAX; frame++) {
        if (BWL_FrameIsStrike(roll)) {
            gameScore += BWL_StrikeScore(roll);
            roll += 1;
        } else if (BWL_FrameIsSpare(roll)) {
            gameScore += BWL_SpareScore(roll);
            roll += 2;
        } else {
            gameScore += BWL_FrameBaseScore(roll);
            roll += 2;
        }
    }
    return gameScore;
}

void BWL_Roll(BWL_PIN_COUNT_T pinsDown, BWL_ROLL_COUNT_T rolls) {
    for (int i = 0; i < rolls; i++) {
        BWL_rollScores[BWL_rollCount] = pinsDown;
        BWL_rollCount++;
    }
}

//
// End of File
//

#ifndef BOWLING_H    // Guards against multiple inclusion
#    define BOWLING_H

//
// Section: Included Files
//

#    include <stdbool.h>
#    include <stdint.h>

//
// Section: Constants
//

#    define BWL_ROLL_COUNT_MAX (21)
#    define BWL_FRAME_COUNT_MAX (10)
#    define BWL_PIN_COUNT_MAX (10)

//
// Section: Data Types
//

typedef uint16_t BWL_GAME_SCORE_T;
typedef uint8_t BWL_PIN_COUNT_T;
typedef uint8_t BWL_ROLL_COUNT_T;

//
// Section: Bowling Module APIs
//

void BWL_GameNew(void);
BWL_GAME_SCORE_T BWL_GameScore(void);
void BWL_Roll(BWL_PIN_COUNT_T pinsDown, BWL_ROLL_COUNT_T rolls);


#endif // BOWLING_H

//
// End of File
//

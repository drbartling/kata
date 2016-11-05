
//
// Section: Included Files
//

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include "roman_numerals.h"

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
void RN_IntToRoman(int num, char str[])
{
    while (num)
    {
        if (9 == num)
        {
            *str++ = 'I';
            *str++ = 'X';
            num -= 9;
        }
        else if (5 <= num)
        {
            *str++ = 'V';
            num -= 5;
        }
        else if (4 == num)
        {
            *str++ = 'I';
            *str++ = 'V';
            num -= 4;
        }
        else
        {
            *str++ = 'I';
            num--;
        }
    }
    *str = 0;
}

//
// End of File
//

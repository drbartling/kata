
//
// Section: Included Files
//

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "roman_numerals.h"

//
// Section: Constants
//

static const char RN_numerals[] = "IVXLCDM";

//
// Section: Global Variable Declarations
//

//
// Section: Macros
//

//
// Section: Static Function Prototypes
//

static inline int RN_AppendNine(char str[], int magnitude, int i);
static inline int RN_AppendFive(char str[], int magnitude, int i);
static inline int RN_AppendFour(char str[], int magnitude, int i);
static inline int RN_AppendOne(char str[], int magnitude, int i);
static inline void RN_StringTerminate(char str[], int i);

//
// Section: Static Function Definitions
//
static inline int RN_AppendNine(char str[], int magnitude, int i)
{
    str[i++] = RN_numerals[magnitude * 2];
    str[i++] = RN_numerals[magnitude * 2 + 2];
    return i;
}
static inline int RN_AppendFive(char str[], int magnitude, int i)
{
    str[i++] = RN_numerals[magnitude * 2 + 1];
    return i;
}
static inline int RN_AppendFour(char str[], int magnitude, int i)
{
    str[i++] = RN_numerals[magnitude * 2];
    str[i++] = RN_numerals[magnitude * 2 + 1];
    return i;
}
static inline int RN_AppendOne(char str[], int magnitude, int i)
{
    str[i++] = RN_numerals[magnitude * 2];
    return i;
}
static inline void RN_StringTerminate(char str[], int i)
{
    str[i] = 0;
}

//
// Section:  Module APIs
//
void RN_IntToRoman(int num, char str[])
{
    int index = 0;

    if (4000 <= num)
    {
        RN_StringTerminate(str, index);
        return;
    }

    while (num)
    {
        int magnitude = floor(log10(num));
        int scaler    = pow(10, magnitude);
        int digit     = num / scaler;
        if (9 == digit)
        {
            index = RN_AppendNine(str, magnitude, index);
            num -= 9 * scaler;
        }
        else if (5 <= digit)
        {
            index = RN_AppendFive(str, magnitude, index);
            num -= 5 * scaler;
        }
        else if (4 == digit)
        {
            index = RN_AppendFour(str, magnitude, index);
            num -= 4 * scaler;
        }
        else
        {
            index = RN_AppendOne(str, magnitude, index);
            num -= 1 * scaler;
        }
    }
    RN_StringTerminate(str, index);
}

//
// End of File
//


#ifndef ROMAN_NUMERALS_H  // Guards against multiple inclusion
#define ROMAN_NUMERALS_H

//
// Section: Included Files
//

#include <stdbool.h>
#include <stdint.h>

//
// Section: Constants
//

/// Largest value that can be represented as a roman numeral
#define RN_MAX (3999)

//
// Section: Data Types
//

//
// Section:  Module APIs
//

void RN_IntToRoman(int num, char str[]);

#endif

//
// End of File
//

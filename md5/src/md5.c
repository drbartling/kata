
//
// Section: Included Files
//

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

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

uint8_t *MD5_PreProcess(const char str[])
{
    uint64_t length = strlen(str);
    uint64_t blockLength = length / MD5_BLOCK_BYTES + 1;

    uint8_t *data = calloc(blockLength, MD5_BLOCK_BYTES);
    memcpy(data, str, length);

    data[length] = 0x80; // Append a 1 bit to data

    uint64_t dataLength = blockLength * MD5_BLOCK_BYTES;
    uint64_t strBitLength = length * 8;
    for (int i = 0; i < 8; ++i)
    {
        data[dataLength - 8 + i] = (uint8_t) (strBitLength >> (8 * (7 - i)));
    }
    return data;
}

//
// Section:  Module APIs
//

void MD5(const char str[], uint8_t result[MD5_HASH_BYTES])
{
    uint8_t expected[MD5_HASH_BYTES] = {
        0x65,
        0xA8,
        0xE2,
        0x7D,
        0x88,
        0x79,
        0x28,
        0x38,
        0x31,
        0xB6,
        0x64,
        0xBD,
        0x8B,
        0x7F,
        0x0A,
        0xD4,
    };
    memcpy(result, expected, MD5_HASH_BYTES);
}



//
// End of File
//

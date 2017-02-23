
#ifndef MD5_H    // Guards against multiple inclusion
#    define MD5_H

//
// Section: Included Files
//

#    include <stdbool.h>
#    include <stdint.h>

//
// Section: Constants
//

#define MD5_HASH_BITS (128)
#define MD5_HASH_BYTES (MD5_HASH_BITS / 8)
#define MD5_BLOCK_BITS (512)
#define MD5_BLOCK_BYTES (MD5_BLOCK_BITS / 8)

//
// Section: Data Types
//

//
// Section:  Module APIs
//

void MD5(const char str[], uint8_t result[MD5_HASH_BYTES]);

uint8_t *MD5_PreProcess(const char str[]);

#endif

//
// End of File
//

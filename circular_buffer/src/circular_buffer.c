
//
// Section: Included Files
//

#include "circular_buffer.h"
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

//
// Section: Constants
//

#ifdef TEST
#    define STATIC
#else
#    define STATIC static
#endif

//
// Section: Global Variable Declarations
//

STATIC CBF_DATA_T CBF_data[1412];
STATIC int8_t CBF_writeIndex;
STATIC int8_t CBF_readIndex;

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

CBF_ERROR_T CBF_BufferGet(CBF_DATA_T *dataOut) {
    *dataOut = CBF_data[CBF_readIndex++];
    return CBF_SUCCESS;
}

CBF_ERROR_T CBF_BufferPut(CBF_DATA_T dataIn) {
    CBF_data[CBF_writeIndex++] = dataIn;
    return CBF_SUCCESS;
}


//
// End of File
//

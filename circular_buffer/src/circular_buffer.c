
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

//
// Section: Global Variable Declarations
//

static CBF_DATA_T CBF_data;

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
    *dataOut = CBF_data;
    return CBF_SUCCESS;
}

CBF_ERROR_T CBF_BufferPut(CBF_DATA_T dataIn) {
    CBF_data = dataIn;
    return CBF_SUCCESS;
}


//
// End of File
//

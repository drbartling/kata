
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
// Section: Typedefs
//

typedef int16_t CBF_INDEX_T;

//
// Section: Global Variable Declarations
//

STATIC CBF_DATA_T CBF_data[CBF_BUFFER_SIZE];
STATIC CBF_INDEX_T CBF_writeIndex;
STATIC CBF_INDEX_T CBF_readIndex;

//
// Section: Macros
//

//
// Section: Static Function Prototypes
//

inline static bool CBF_IsEmpty(void);
inline static CBF_INDEX_T CBF_IndexIncrement(CBF_INDEX_T index);

//
// Section: Static Function Definitions
//

inline static bool CBF_IsEmpty(void) {
    return CBF_readIndex == CBF_writeIndex;
}

inline static CBF_INDEX_T CBF_IndexIncrement(CBF_INDEX_T index) {
    index++;
    index %= CBF_BUFFER_SIZE;
    return index;
}

//
// Section:  Module APIs
//

CBF_ERROR_T CBF_BufferGet(CBF_DATA_T *dataOut) {
    if (CBF_readIndex == CBF_writeIndex) {
        return CBF_UNDERFLOW;
    }
    CBF_readIndex = CBF_IndexIncrement(CBF_readIndex);
    *dataOut = CBF_data[CBF_readIndex];
    return CBF_SUCCESS;
}

CBF_ERROR_T CBF_BufferPut(CBF_DATA_T dataIn) {
    CBF_INDEX_T writeIndex = CBF_IndexIncrement(CBF_writeIndex);
    if (writeIndex == CBF_readIndex) {
        return CBF_OVERFLOW;
    }
    CBF_writeIndex = writeIndex;
    CBF_data[CBF_writeIndex] = dataIn;
    return CBF_SUCCESS;
}


//
// End of File
//

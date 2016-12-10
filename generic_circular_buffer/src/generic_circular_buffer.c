
//
// Section: Included Files
//

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "generic_circular_buffer.h"

//
// Section: Constants
//

//
// Section: Types
//

struct CBF_BUFFER_S
{
    void* buffer;
};

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

CBF_BUFFER_T
_CBF_BufferNew(size_t typeSize, size_t count)
{
    CBF_BUFFER_T newBuffer = malloc(sizeof(struct CBF_BUFFER_S));
    newBuffer->buffer      = malloc(typeSize * count);
    return newBuffer;
}

void* CBF_BufferPtrGet(CBF_BUFFER_T circBuffer)
{
    return circBuffer->buffer;
}

//
// End of File
//

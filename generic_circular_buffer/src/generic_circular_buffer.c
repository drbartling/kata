
//
// Section: Included Files
//

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "cbf_struct.h"
#include "generic_circular_buffer.h"

//
// Section: Constants
//

//
// Section: Types
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

int* CBF_PointerIncrement(CBF_BUFFER_T cbf, int* ptr);

//
// Section: Static Function Definitions
//

int* CBF_PointerIncrement(CBF_BUFFER_T cbf, int* ptr)
{
    ptr++;
    if (ptr == cbf->end)
    {
        ptr = cbf->buffer;
    }
    return ptr;
}

//
// Section:  Module APIs
//

CBF_BUFFER_T
_CBF_BufferNew(size_t typeSize, size_t count)
{
    CBF_BUFFER_T newBuffer = malloc(sizeof(struct CBF_BUFFER_S));
    newBuffer->buffer      = malloc(typeSize * count);
    newBuffer->write       = newBuffer->buffer;
    newBuffer->read        = newBuffer->buffer;
    newBuffer->end         = ((int*) newBuffer->buffer) + count;
    return newBuffer;
}

void CBF_BufferDelete(CBF_BUFFER_T circularBuffer)
{
    free(circularBuffer->buffer);
    free(circularBuffer);
}

int CBF_ElementRead(CBF_BUFFER_T cbf)
{
    int* ptr  = cbf->read;
    int  data = *ptr;
    cbf->read = CBF_PointerIncrement(cbf, ptr);
    return data;
}

void CBF_ElementWrite(CBF_BUFFER_T cbf, int data)
{
    int* ptr   = cbf->write;
    *ptr       = data;
    cbf->write = CBF_PointerIncrement(cbf, ptr);
}

bool CBF_IsEmpty(CBF_BUFFER_T cbf)
{
    return cbf->write == cbf->read;
}

//
// End of File
//

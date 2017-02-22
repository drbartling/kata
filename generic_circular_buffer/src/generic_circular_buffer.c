
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
// Section: Macros
//

/// @brief Returns the next n address after a given void pointer
#define CBF_VoidPointerIncrement(ptr, n) (((uint8_t*) ptr) + n)

/// @brief Copies from source pointer to dest pointer and increments pointers
#define CBF_DataCopyAndIncrement(source, dest)                                 \
    *dest++ = *((uint8_t*) source);                                            \
    source  = CBF_VoidPointerIncrement(source, 1);

//
// Section: Static Function Prototypes
//

void* CBF_PointerIncrement(CBF_BUFFER_T cbf, void* ptr);

//
// Section: Static Function Definitions
//

void* CBF_PointerIncrement(CBF_BUFFER_T cbf, void* ptr)
{
    ptr = CBF_VoidPointerIncrement(ptr, cbf->elementSize);
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
    newBuffer->end = ((uint8_t*) newBuffer->buffer) + (count * typeSize);
    newBuffer->elementSize = typeSize;
    return newBuffer;
}

void CBF_BufferDelete(CBF_BUFFER_T circularBuffer)
{
    free(circularBuffer->buffer);
    free(circularBuffer);
}

void* _CBF_ElementRead(CBF_BUFFER_T cbf)
{
    void* ptr = cbf->read;
    cbf->read = CBF_PointerIncrement(cbf, ptr);
    return ptr;
}

void _CBF_ElementWrite(CBF_BUFFER_T cbf, const void* data)
{
    uint8_t* ptr = cbf->write;
    for (int i = 0; i < cbf->elementSize; ++i)
    {
        CBF_DataCopyAndIncrement(data, ptr);
    }
    cbf->write = CBF_PointerIncrement(cbf, cbf->write);
}

bool CBF_IsEmpty(CBF_BUFFER_T cbf)
{
    return cbf->write == cbf->read;
}

//
// End of File
//

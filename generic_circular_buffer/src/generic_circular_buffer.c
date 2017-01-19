
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

void* CBF_PointerIncrement(CBF_BUFFER_T cbf, void* ptr);

//
// Section: Static Function Definitions
//

void* CBF_PointerIncrement(CBF_BUFFER_T cbf, void* ptr)
{
    ptr = ((uint8_t*) ptr) + cbf->elementSize;
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
_CBF_BufferNew(size_t typeSize, size_t count) {
  CBF_BUFFER_T newBuffer = malloc(sizeof(struct CBF_BUFFER_S));
  newBuffer->buffer = malloc(typeSize * count);
  newBuffer->write = newBuffer->buffer;
  newBuffer->read = newBuffer->buffer;
  newBuffer->end = ((uint8_t*)newBuffer->buffer) + (count * typeSize);
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
    void* ptr  = cbf->read;
    cbf->read = CBF_PointerIncrement(cbf, ptr);
    return ptr;
}

void _CBF_ElementWrite(CBF_BUFFER_T cbf, const void *data)
{
    volatile int *foo = data;
    uint8_t* ptr   = cbf->write;
    for (int i = 0; i < cbf->elementSize; ++i)
    {
        *ptr++ = *((uint8_t*)data);
        data = ((uint8_t*)data) + 1;
    }
    cbf->write     = CBF_PointerIncrement(cbf, cbf->write);
}

bool CBF_IsEmpty(CBF_BUFFER_T cbf)
{
    return cbf->write == cbf->read;
}

//
// End of File
//

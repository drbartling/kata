
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
    void* write;
    void* read;
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
    newBuffer->write       = newBuffer->buffer;
    newBuffer->read        = newBuffer->buffer;
    return newBuffer;
}

void CBF_BufferDelete(CBF_BUFFER_T circularBuffer)
{
    free(circularBuffer->buffer);
    free(circularBuffer);
}

int CBF_ElementRead(CBF_BUFFER_T buffer)
{
    int* ptr  = buffer->read;
    int  data = *ptr;
    ptr++;
    buffer->read = ptr;
    return data;
}

void CBF_ElementWrite(CBF_BUFFER_T buffer, int data)
{
    int* ptr = buffer->write;
    *ptr     = data;
    ptr++;
    buffer->write = ptr;
}

bool CBF_IsEmpty(CBF_BUFFER_T buffer)
{
    return buffer->write == buffer->read;
}

//
// End of File
//

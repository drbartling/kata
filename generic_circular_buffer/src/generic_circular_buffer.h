
#ifndef GENERIC_CIRCULAR_BUFFER_H  // Guards against multiple inclusion
#define GENERIC_CIRCULAR_BUFFER_H

//
// Section: Included Files
//

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//
// Section: Macros
//

#define CBF_BufferNew(type, count) _CBF_BufferNew(sizeof(type), (count))
#define CBF_ElementRead(type, buffer) *((type*)(_CBF_ElementRead(buffer)))
#define CBF_ElementWrite(type, buffer, data) \
  {                                          \
    type typedData = data;                   \
    _CBF_ElementWrite(buffer, &typedData);   \
  }

//
// Section: Constants
//

//
// Section: Data Types
//

typedef struct CBF_BUFFER_S* CBF_BUFFER_T;

//
// Section:  Module APIs
//

CBF_BUFFER_T _CBF_BufferNew(size_t typeSize, size_t count);
void CBF_BufferDelete(CBF_BUFFER_T);
void* _CBF_ElementRead(CBF_BUFFER_T buffer);
void _CBF_ElementWrite(CBF_BUFFER_T buffer, const void *data);
bool CBF_IsEmpty(CBF_BUFFER_T buffer);

#endif

//
// End of File
//

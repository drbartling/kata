
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

/**
 * @brief Allocates buffer, and provides pointer
 * @details Allocates a buffer of the type and size requested.  If unable to do
 * so, it will return a null pointer.
 *
 * @param type data type used for the buffer
 * @param count number of elements stored in the buffer
 *
 * @return pointer to newly allocated buffer
 * @return null if unable to allocate buffer
 */
#define CBF_BufferNew(type, count) _CBF_BufferNew(sizeof(type), (count))

/**
 * @brief reads/dequeues oldest element in the buffer
 * @details Dequeues the oldest element in the buffer, returning the data.
 *
 * @param type type used in the buffer
 * @param buffer pointer to the buffer
 *
 * @return Oldest data in the buffer
 */
#define CBF_ElementRead(type, buffer) *((type*) (_CBF_ElementRead(buffer)))

/**
 * @brief Writes/Enqueues data into the buffer
 *
 * @param type type of data used in the buffer
 * @param buffer pointer to the buffer
 * @param data data to write into the buffer
 *
 * @return none
 */
#define CBF_ElementWrite(type, buffer, data)                                   \
    {                                                                          \
        type typedData = data;                                                 \
        _CBF_ElementWrite(buffer, &typedData);                                 \
    }

//
// Section: Data Types
//

/// @brief pointer to CBF_Buffer object for application use
typedef struct CBF_BUFFER_S* CBF_BUFFER_T;

//
// Section:  Module APIs
//

CBF_BUFFER_T _CBF_BufferNew(size_t typeSize, size_t count);
void CBF_BufferDelete(CBF_BUFFER_T);
bool CBF_IsEmpty(CBF_BUFFER_T buffer);

/// @brief Do not use directly; use CBF_ElementRead()
void* _CBF_ElementRead(CBF_BUFFER_T buffer);

/// @brief Do not use directly; use CBF_ElementWrite()
void _CBF_ElementWrite(CBF_BUFFER_T buffer, const void* data);

#endif

//
// End of File
//

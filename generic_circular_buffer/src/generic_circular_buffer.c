
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
    int foo;
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
    return newBuffer;
}

//
// End of File
//

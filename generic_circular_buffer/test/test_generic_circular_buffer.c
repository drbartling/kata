
#include "generic_circular_buffer.h"
#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_BufferNew_Returns_PointerToBufferStruct(void)
{
    CBF_BUFFER_T testBuffer = CBF_BufferNew(int, 4);
    TEST_ASSERT_NOT_NULL(testBuffer);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_BufferNew_Returns_PointerToBufferStruct);
    return UNITY_END();
}


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
    CBF_BufferDelete(testBuffer);
}

void test_BufferNew_Should_CreatePointerToBuffer(void)
{
    CBF_BUFFER_T testBuffer = CBF_BufferNew(int, 4);
    int*         ptr        = CBF_BufferPtrGet(testBuffer);
    TEST_ASSERT_NOT_NULL(ptr);
    CBF_BufferDelete(testBuffer);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_BufferNew_Returns_PointerToBufferStruct);
    RUN_TEST(test_BufferNew_Should_CreatePointerToBuffer);
    return UNITY_END();
}

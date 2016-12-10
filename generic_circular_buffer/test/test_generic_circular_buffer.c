
#include "generic_circular_buffer.h"
#include "unity.h"

static CBF_BUFFER_T testBuffer;

void setUp(void)
{
    testBuffer = CBF_BufferNew(int, 4);
}

void tearDown(void)
{
    CBF_BufferDelete(testBuffer);
}

void test_BufferNew_Returns_PointerToBufferStruct(void)
{
    TEST_ASSERT_NOT_NULL(testBuffer);
}

void test_BufferNew_Should_CreatePointerToBuffer(void)
{
    int* ptr = CBF_BufferPtrGet(testBuffer);
    TEST_ASSERT_NOT_NULL(ptr);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_BufferNew_Returns_PointerToBufferStruct);
    RUN_TEST(test_BufferNew_Should_CreatePointerToBuffer);
    return UNITY_END();
}

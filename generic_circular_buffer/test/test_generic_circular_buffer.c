
#include "generic_circular_buffer.h"
#include "unity.h"

struct CBF_BUFFER_S
{
    void* buffer;
    void* write;
    void* read;
};

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
    TEST_ASSERT_NOT_NULL(testBuffer->buffer);
}

void test_BufferNew_should_initializeWriteToBufferStart(void)
{
    TEST_ASSERT_EQUAL_PTR(testBuffer->buffer, testBuffer->write);
}

void test_BufferNew_should_intializeReadToBufferStart(void)
{
    TEST_ASSERT_EQUAL_PTR(testBuffer->buffer, testBuffer->read);
}

void test_IsEmpty_should_returnTrue_when_bufferIsEmpty(void)
{
    TEST_ASSERT_TRUE(CBF_IsEmpty(testBuffer));
}

void test_IsEmpty_should_returnFalse_when_bufferIsNotEmpty(void)
{
    CBF_ElementWrite(testBuffer, 42);
    TEST_ASSERT_FALSE(CBF_IsEmpty(testBuffer));
}

void test_ElementRead_and_ElementWrite_workTogether_to_readAndWriteData(void)
{
    CBF_ElementWrite(testBuffer, 41);
    TEST_ASSERT_EQUAL(41, CBF_ElementRead(testBuffer));
}

void test_ElementRead_and_ElementWrite_workTogether_to_readAndWriteMultipleValues(
      void)
{
    int dataArray[3] = {32, 65, 4444};
    for (int i = 0; i < 3; ++i)
    {
        CBF_ElementWrite(testBuffer, dataArray[i]);
    }

    int readArray[3] = {0};
    for (int i = 0; i < 3; ++i)
    {
        readArray[i] = CBF_ElementRead(testBuffer);
    }

    TEST_ASSERT_EQUAL_INT_ARRAY(dataArray, readArray, 3);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_BufferNew_Returns_PointerToBufferStruct);
    RUN_TEST(test_BufferNew_Should_CreatePointerToBuffer);
    RUN_TEST(test_BufferNew_should_initializeWriteToBufferStart);
    RUN_TEST(test_BufferNew_should_intializeReadToBufferStart);
    RUN_TEST(test_IsEmpty_should_returnTrue_when_bufferIsEmpty);
    RUN_TEST(test_IsEmpty_should_returnFalse_when_bufferIsNotEmpty);
    RUN_TEST(
          test_ElementRead_and_ElementWrite_workTogether_to_readAndWriteData);
    RUN_TEST(
          test_ElementRead_and_ElementWrite_workTogether_to_readAndWriteMultipleValues);

    return UNITY_END();
}

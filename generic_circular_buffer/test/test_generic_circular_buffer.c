
#include "cbf_struct.h"
#include "generic_circular_buffer.h"
#include "unity.h"

static CBF_BUFFER_T testBuffer;

void setUp(void) { testBuffer = CBF_BufferNew(int, 4); }

void tearDown(void) { CBF_BufferDelete(testBuffer); }

void test_BufferNew_Returns_PointerToBufferStruct(void) {
  TEST_ASSERT_NOT_NULL(testBuffer);
}

void test_BufferNew_Should_CreatePointerToBuffer(void) {
  TEST_ASSERT_NOT_NULL(testBuffer->buffer);
}

void test_BufferNew_should_initializeWriteToBufferStart(void) {
  TEST_ASSERT_EQUAL_PTR(testBuffer->buffer, testBuffer->write);
}

void test_BufferNew_should_intializeReadToBufferStart(void) {
  TEST_ASSERT_EQUAL_PTR(testBuffer->buffer, testBuffer->read);
}

void test_IsEmpty_should_returnTrue_when_bufferIsEmpty(void) {
  TEST_ASSERT_TRUE(CBF_IsEmpty(testBuffer));
}

void test_IsEmpty_should_returnFalse_when_bufferIsNotEmpty(void) {
  CBF_ElementWrite(int, testBuffer, 42);
  TEST_ASSERT_FALSE(CBF_IsEmpty(testBuffer));
}

void test_ElementRead_and_ElementWrite_workTogether_to_readAndWriteData(void) {
  CBF_ElementWrite(int, testBuffer, 41);
  TEST_ASSERT_EQUAL(41, CBF_ElementRead(int, testBuffer));
}

void test_ElementRead_and_Write_workTogether_with_MultipleValues(void) {
  int dataArray[3] = {32, 65, 4444};
  for (int i = 0; i < 3; ++i) {
    CBF_ElementWrite(int, testBuffer, dataArray[i]);
  }

  int readArray[3] = {0};
  for (int i = 0; i < 3; ++i) {
    readArray[i] = CBF_ElementRead(int, testBuffer);
  }

  TEST_ASSERT_EQUAL_INT_ARRAY(dataArray, readArray, 3);
}

void test_ElementRead_and_Write_canHandleManyManyValues(void) {
  int dataArray[50000] = {-1000, 1000, 42, 9283, -9278};
  int readArray[50000] = {0};
  for (int i = 0; i < 50000; ++i) {
    CBF_ElementWrite(int, testBuffer, dataArray[i]);
    readArray[i] = CBF_ElementRead(int, testBuffer);
  }
  TEST_ASSERT_EQUAL_INT_ARRAY(dataArray, readArray, 50000);
}

void test_BufferNew_should_Store_SizeOf_Array_Element(void) {
  TEST_ASSERT_EQUAL(sizeof(int), testBuffer->elementSize);

  CBF_BUFFER_T testBuffer2 = CBF_BufferNew(long int, 4);
  TEST_ASSERT_EQUAL(sizeof(long int), testBuffer2->elementSize);
  CBF_BufferDelete(testBuffer2);
}

void test_ElementRead_and_Write_WorkWith_uint64(void) {
  CBF_BUFFER_T testBuffer2 = CBF_BufferNew(uint64_t, 4);

  uint64_t dataArray[3] = {42949672295, 8328764, 24};

  for (int i = 0; i < 3; ++i) {
    CBF_ElementWrite(uint64_t, testBuffer2, dataArray[i]);
  }

  uint64_t readArray[3] = {0};
  for (int i = 0; i < 3; ++i) {
    readArray[i] = CBF_ElementRead(uint64_t, testBuffer2);
  }

  TEST_ASSERT_EQUAL_UINT64_ARRAY(dataArray, readArray, 3);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_BufferNew_Returns_PointerToBufferStruct);
  RUN_TEST(test_BufferNew_Should_CreatePointerToBuffer);
  RUN_TEST(test_BufferNew_should_initializeWriteToBufferStart);
  RUN_TEST(test_BufferNew_should_intializeReadToBufferStart);
  RUN_TEST(test_IsEmpty_should_returnTrue_when_bufferIsEmpty);
  RUN_TEST(test_IsEmpty_should_returnFalse_when_bufferIsNotEmpty);
  RUN_TEST(test_ElementRead_and_ElementWrite_workTogether_to_readAndWriteData);
  RUN_TEST(test_ElementRead_and_Write_workTogether_with_MultipleValues);
  RUN_TEST(test_ElementRead_and_Write_canHandleManyManyValues);
  RUN_TEST(test_BufferNew_should_Store_SizeOf_Array_Element);
  RUN_TEST(test_ElementRead_and_Write_WorkWith_uint64);
  return UNITY_END();
}

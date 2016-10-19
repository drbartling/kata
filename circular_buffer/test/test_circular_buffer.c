
#include "unity.h"
#include "circular_buffer.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_BufferPut_should_ReturnSuccessWhenBufferIsNotFull(void) {
    TEST_ASSERT_EQUAL_MESSAGE(CBF_SUCCESS, CBF_BufferPut(42),
            "Expected CBF_SUCCESS");
}

void test_BufferGet_should_ReturnSuccess_when_BuffferIsNotEmpty(void) {
    (void) CBF_BufferPut(42);
    CBF_DATA_T dataOut = 0;

    TEST_ASSERT_EQUAL_MESSAGE(CBF_SUCCESS, CBF_BufferGet(&dataOut),
            "Expected CBF_SUCCESS");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_BufferPut_should_ReturnSuccessWhenBufferIsNotFull);
    RUN_TEST(test_BufferGet_should_ReturnSuccess_when_BuffferIsNotEmpty);
    return UNITY_END();
}

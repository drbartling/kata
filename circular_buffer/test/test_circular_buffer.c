
#include "unity.h"
#include "circular_buffer.h"

#define ArrayLength(x) (sizeof(x)/sizeof(x[0]))

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

void test_BufferGet_should_ReturnDataPutIntoBufferBy_BufferPut(void) {
    CBF_DATA_T dataIn = 35;
    CBF_DATA_T dataOut = 0;

    (void) CBF_BufferPut(dataIn);
    (void) CBF_BufferGet(&dataOut);
    TEST_ASSERT_EQUAL(dataIn, dataOut);

    dataIn = 1000;
    (void) CBF_BufferPut(dataIn);
    (void) CBF_BufferGet(&dataOut);
    TEST_ASSERT_EQUAL(dataIn, dataOut);

    dataIn = -1000;
    (void) CBF_BufferPut(dataIn);
    (void) CBF_BufferGet(&dataOut);
    TEST_ASSERT_EQUAL(dataIn, dataOut);
}

/*
void test_BufferGet_should_ReturnDataPutIntoBufferBy_BufferPut_InOrder(void) {
    CBF_DATA_T dataIn[] = {42, 54, 21, 32, 1000, -1000};
    CBF_DATA_T dataOut[ArrayLength(dataIn)] = {0};

    for (int i = 0; i < ArrayLength(dataIn); i++) {

    }
}
 */

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_BufferPut_should_ReturnSuccessWhenBufferIsNotFull);
    RUN_TEST(test_BufferGet_should_ReturnSuccess_when_BuffferIsNotEmpty);
    RUN_TEST(test_BufferGet_should_ReturnDataPutIntoBufferBy_BufferPut);
    return UNITY_END();
}
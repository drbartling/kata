
#include "unity.h"
#include "generic_circular_buffer.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_Template(void) {
    TEST_IGNORE_MESSAGE("Ignored test");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Template);
    return UNITY_END();
}

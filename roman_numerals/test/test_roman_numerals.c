
#include <string.h>
#include "roman_numerals.h"
#include "unity.h"

static char str[30];

void setUp(void)
{
    strcpy(str, "Fail!");
}

void tearDown(void)
{
}

void test_IntToRoman_should_returnEmptyString_when_numIsZero(void)
{
    RN_IntToRoman(0, str);
    TEST_ASSERT_EQUAL_STRING("", str);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_IntToRoman_should_returnEmptyString_when_numIsZero);
    return UNITY_END();
}

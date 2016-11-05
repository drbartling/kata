
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

void test_IntToRoman_should_return_EmptyString_when_numIsZero(void)
{
    RN_IntToRoman(0, str);
    TEST_ASSERT_EQUAL_STRING("", str);
}

void test_IntToRoman_should_return_Is_when_NumIsOneToThree(void)
{
    RN_IntToRoman(1, str);
    TEST_ASSERT_EQUAL_STRING("I", str);
    RN_IntToRoman(2, str);
    TEST_ASSERT_EQUAL_STRING("II", str);
    RN_IntToRoman(3, str);
    TEST_ASSERT_EQUAL_STRING("III", str);
}

void test_IntToRoman_should_return_IV_when_NumIsFour(void)
{
    RN_IntToRoman(4, str);
    TEST_ASSERT_EQUAL_STRING("IV", str);
}

void test_IntToRoman_should_return_V_when_NumIsFive(void)
{
    RN_IntToRoman(5, str);
    TEST_ASSERT_EQUAL_STRING("V", str);
}

void test_IntToRoman_should_return_VIs_when_NumIsSixToEight(void)
{

}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_IntToRoman_should_return_EmptyString_when_numIsZero);
    RUN_TEST(test_IntToRoman_should_return_Is_when_NumIsOneToThree);
    RUN_TEST(test_IntToRoman_should_return_IV_when_NumIsFour);
    RUN_TEST(test_IntToRoman_should_return_V_when_NumIsFive);
    return UNITY_END();
}


#include <string.h>
#include "roman_numerals.h"
#include "unity.h"

static char str[3000];

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
    RN_IntToRoman(6, str);
    TEST_ASSERT_EQUAL_STRING("VI", str);
    RN_IntToRoman(7, str);
    TEST_ASSERT_EQUAL_STRING("VII", str);
    RN_IntToRoman(8, str);
    TEST_ASSERT_EQUAL_STRING("VIII", str);
}

void test_IntToRoman_should_return_IX_when_NumIsNine(void)
{
    RN_IntToRoman(9, str);
    TEST_ASSERT_EQUAL_STRING("IX", str);
}

void test_IntToRoman_TensPlace(void)
{
    RN_IntToRoman(10, str);
    TEST_ASSERT_EQUAL_STRING("X", str);
    RN_IntToRoman(30, str);
    TEST_ASSERT_EQUAL_STRING("XXX", str);
    RN_IntToRoman(40, str);
    TEST_ASSERT_EQUAL_STRING("XL", str);
    RN_IntToRoman(50, str);
    TEST_ASSERT_EQUAL_STRING("L", str);
    RN_IntToRoman(70, str);
    TEST_ASSERT_EQUAL_STRING("LXX", str);
    RN_IntToRoman(90, str);
    TEST_ASSERT_EQUAL_STRING("XC", str);
}

void test_IntToRoman_Acceptance(void)
{
    RN_IntToRoman(1984, str);
    TEST_ASSERT_EQUAL_STRING("MCMLXXXIV", str);
    RN_IntToRoman(3999, str);
    TEST_ASSERT_EQUAL_STRING("MMMCMXCIX", str);
}

void test_IntToRoman_should_ReturnEmptyString_when_numIs4000OrMore(void)
{
    RN_IntToRoman(4000, str);
    TEST_ASSERT_EQUAL_STRING("", str);
    RN_IntToRoman(INT16_MAX, str);
    TEST_ASSERT_EQUAL_STRING("", str);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_IntToRoman_should_return_EmptyString_when_numIsZero);
    RUN_TEST(test_IntToRoman_should_return_Is_when_NumIsOneToThree);
    RUN_TEST(test_IntToRoman_should_return_IV_when_NumIsFour);
    RUN_TEST(test_IntToRoman_should_return_V_when_NumIsFive);
    RUN_TEST(test_IntToRoman_should_return_VIs_when_NumIsSixToEight);
    RUN_TEST(test_IntToRoman_should_return_IX_when_NumIsNine);
    RUN_TEST(test_IntToRoman_TensPlace);
    RUN_TEST(test_IntToRoman_Acceptance);
    RUN_TEST(test_IntToRoman_should_ReturnEmptyString_when_numIs4000OrMore);
    return UNITY_END();
}

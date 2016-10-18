
#include "unity.h"
#include "bowling.h"

void setUp(void) {
    BWL_GameNew();
}

void tearDown(void) {
}

void test_GameScore_should_Return0_when_GutterGameIsPlayed(void) {
    BWL_Roll(0, 20);

    TEST_ASSERT_EQUAL(0, BWL_GameScore());
}

void test_GameScore_should_Return40_when_RollingAllTwos(void) {
    BWL_Roll(2, 20);

    TEST_ASSERT_EQUAL(40, BWL_GameScore());
}

void test_NewGame_should_ResetTheScoreToZero(void) {
    BWL_Roll(2, 20);
    BWL_GameNew();

    TEST_ASSERT_EQUAL(0, BWL_GameScore());
}

void test_GameScore_should_CorrectlyScoreASpare(void) {
    BWL_Roll(4, 1);
    BWL_Roll(6, 1);
    BWL_Roll(6, 1);
    BWL_Roll(0, 17);

    TEST_ASSERT_EQUAL(22, BWL_GameScore());
}

void test_GameScore_should_CorrectlyScoreAStrike(void) {
    BWL_Roll(10, 1);
    BWL_Roll(3, 1);
    BWL_Roll(6, 1);
    BWL_Roll(0, 17);

    TEST_ASSERT_EQUAL(28, BWL_GameScore());
}

void test_GameScore_should_Return300_when_PerfectGameIsPlayed(void) {
    BWL_Roll(10, 500);

    TEST_ASSERT_EQUAL(300, BWL_GameScore());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_GameScore_should_Return0_when_GutterGameIsPlayed);
    RUN_TEST(test_GameScore_should_Return40_when_RollingAllTwos);
    RUN_TEST(test_NewGame_should_ResetTheScoreToZero);
    RUN_TEST(test_GameScore_should_CorrectlyScoreASpare);
    RUN_TEST(test_GameScore_should_CorrectlyScoreAStrike);
    RUN_TEST(test_GameScore_should_Return300_when_PerfectGameIsPlayed);
    return UNITY_END();
}

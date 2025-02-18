#include "../unity/unity.c"

#include "test_money.c"

void setUp() {}

void tearDown() {}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_createmoney_should_be_100_euros_13_cents);
    RUN_TEST(test_createmoney_should_be_0_euros_13_cents);
    RUN_TEST(test_createmoney_should_be_100_euros_00_cents);
    RUN_TEST(test_addmoney_should_be_2_euros_50_cents);
    RUN_TEST(test_addmoney_should_be_3_euros_50_cents);
    RUN_TEST(test_addmoney_should_be_4_euros_50_cents);
    RUN_TEST(test_submoney_should_be_3_euros_50_cents);
    RUN_TEST(test_submoney_should_be_neg3_euros_50_cents);
    return UNITY_END();
}
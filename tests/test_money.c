#include "../core.c"
#include "../unity/unity.c"

void test_createmoney_should_be_100_euros_13_cents(void)
{
    Money m;
    char m_str[] = "100,13";
    create_money(m_str, &m);
    TEST_ASSERT_EQUAL(100, m.euros);
    TEST_ASSERT_EQUAL(13, m.cents);
}

void setUp() {}

void tearDown() {}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_createmoney_should_be_100_euros_13_cents);
    return UNITY_END();
}
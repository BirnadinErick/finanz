#include "../core.c"

#define ASSERT_MONEY_EQUAL(E, C)         \
    TEST_ASSERT_EQUAL(E.euros, C.euros); \
    TEST_ASSERT_EQUAL(E.cents, C.cents);

void test_createmoney_should_be_0_euros_13_cents(void)
{
    Money m;
    char m_str[] = "0,13";
    create_money(m_str, &m);
    TEST_ASSERT_EQUAL(0, m.euros);
    TEST_ASSERT_EQUAL(13, m.cents);
}

void test_createmoney_should_be_100_euros_00_cents(void)
{
    Money m;
    char m_str[] = "100,00";
    create_money(m_str, &m);
    TEST_ASSERT_EQUAL(100, m.euros);
    TEST_ASSERT_EQUAL(0, m.cents);
}

void test_createmoney_should_be_100_euros_13_cents(void)
{
    Money m;
    char m_str[] = "100,13";
    create_money(m_str, &m);
    TEST_ASSERT_EQUAL(100, m.euros);
    TEST_ASSERT_EQUAL(13, m.cents);
}

void test_addmoney_should_be_4_euros_50_cents(void)
{
    Money mref = {.euros = 4, .cents = 50};
    Money m1 = {.euros = 2, .cents = 70};
    Money m2 = {.euros = 1, .cents = 80};
    add_money(&m1, &m2);
    ASSERT_MONEY_EQUAL(m1, mref);
}

void test_addmoney_should_be_3_euros_50_cents(void)
{
    Money mref = {.euros = 3, .cents = 50};
    Money m1 = {.euros = 2, .cents = 70};
    Money m2 = {.euros = 0, .cents = 80};
    add_money(&m1, &m2);
    ASSERT_MONEY_EQUAL(m1, mref);
}

void test_addmoney_should_be_2_euros_50_cents(void)
{
    Money mref = {.euros = 2, .cents = 50};
    Money m1 = {.euros = 1, .cents = 0};
    Money m2 = {.euros = 1, .cents = 50};
    add_money(&m1, &m2);
    ASSERT_MONEY_EQUAL(m1, mref);
}

void test_submoney_should_be_3_euros_50_cents(void)
{
    Money mref = {.euros = 3, .cents = 50};
    Money m1 = {.euros = 4, .cents = 70};
    Money m2 = {.euros = 1, .cents = 20};
    subtract_moeny(&m1, &m2);
    ASSERT_MONEY_EQUAL(m1, mref);
}

void test_submoney_should_be_neg3_euros_50_cents(void)
{
    Money mref = {.euros = -3, .cents = 50};
    Money m1 = {.euros = 0, .cents = 0};
    Money m2 = {.euros = 3, .cents = 50};
    subtract_moeny(&m1, &m2);
    ASSERT_MONEY_EQUAL(m1, mref);
}
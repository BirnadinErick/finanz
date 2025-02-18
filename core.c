#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int32_t euros;
    int32_t cents;
} Money;

typedef enum
{
    OK = 1,
    ERR,
    STR_NUM_CONV_ERR,
    STR_TOK_ERR
} Result;

Result create_money(char *m_str, Money *m)
{
    char *endptr1, *endptr2;

    char *euros_str = strtok(m_str, ",");
    if (euros_str == NULL)
        return STR_TOK_ERR;

    char *cents_str = strtok(NULL, ",");
    if (cents_str == NULL)
        return STR_TOK_ERR;

    int32_t euros = (int32_t)strtol(euros_str, &endptr1, 10);
    if (*endptr1 != '\0')
    {
        return STR_NUM_CONV_ERR;
    }

    int32_t cents = (int32_t)strtol(cents_str, &endptr2, 10);
    if (*endptr2 != '\0')
    {
        return STR_NUM_CONV_ERR;
    }

    m->cents = cents;
    m->euros = euros;
    return OK;
}

void print_moneyval(Money *m)
{
    printf("€ %d,%d", m->euros, m->cents);
    return;
}
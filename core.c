#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MALLOC(A) ((A *)malloc(sizeof(A)))

typedef struct
{
    int32_t euros;
    int32_t cents;
} Money;

typedef enum
{
    INIT,
    INCOME,
    SPENT,
    HOLDING,
} TYP;

typedef enum
{
    OK = 1,
    ERR,
    STR_NUM_CONV_ERR,
    STR_TOK_ERR,
    MALLOC_ERR
} Result;

Result create_money(char *m_str, Money *m)
{
    char *endptr1, *endptr2;
    char *m_str_ = (char *)strndup(m_str, 10);

    char *euros_str = strtok(m_str_, ",");
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

struct Record
{
    time_t timestamp; // created_at
    Money *money;     // value
    char *desc;       // description
    TYP trans_typ;    // typ
    struct Record *next;
};

typedef struct Record Record;

#define MAX_LEDGER_NAME_LEN 127
#define MAX_LEDGER_DESC_LEN 255

typedef struct
{
    Record *records;
    char *name;
} Ledger;

Result init_ledger(Ledger *l, const char *name, char *init_val)
{
    l->name = (char *)strndup(name, MAX_LEDGER_NAME_LEN);

    // create the HEAD record
    Money *mptr = MALLOC(Money);
    Record *rptr = MALLOC(Record);
    if (mptr == NULL || rptr == NULL)
    {
        return MALLOC_ERR;
    }

    create_money(init_val, mptr);

    rptr->timestamp = (time_t)time(NULL);
    rptr->desc = (char *)strdup("Initiate Ledger");
    rptr->money = mptr;
    rptr->trans_typ = INIT;
    rptr->next = NULL;

    l->records = rptr;

    return OK;
}

Result free_ledger(Ledger *l)
{
    // free records
    Record *HEAD = l->records;
    while (HEAD != NULL)
    {
        free(HEAD->money);
        free(HEAD->desc);

        HEAD = HEAD->next;
    }

    free(l->records);
    return OK;
}

Result add_record(Ledger *l, char *desc, char *val, TYP typ)
{
    // find the last record
    Record *curr = l->records;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }

    // create new record
    Money *mptr = MALLOC(Money);
    Record *rptr = MALLOC(Record);
    if (rptr == NULL || mptr == NULL)
    {
        return MALLOC_ERR;
    }

    create_money(val, mptr);
    rptr->money = mptr;
    rptr->timestamp = (time_t)time(NULL);
    rptr->desc = (char *)strndup(desc, MAX_LEDGER_DESC_LEN);
    rptr->trans_typ = typ;
    rptr->next = NULL;

    // append new record to the last record
    curr->next = rptr;
    return OK;
}

void add_money(Money *m_dst, Money *m_src)
{
    int32_t dst = m_dst->euros * 100 + m_dst->cents;
    int32_t src = m_src->euros * 100 + m_src->cents;
    dst += src;

    m_dst->euros = (int32_t)dst / 100;
    m_dst->cents = dst % 100;
}

void subtract_moeny(Money *m_dst, Money *m_src)
{
    int32_t dst = m_dst->euros * 100 + m_dst->cents;
    int32_t src = m_src->euros * 100 + m_src->cents;
    dst -= src;

    m_dst->euros = (int32_t)dst / 100;
    m_dst->cents = abs(dst % 100);
}

void print_ledger(Ledger *l)
{
    puts(l->name);

    Record *curr = l->records;
    size_t i = 1;
    Money m = {.euros = 0, .cents = 0};

    while (curr->next != NULL)
    {
        // Print Style Record: i. [TYP] [VAL] [DESC] ([TIME])
        printf("%ld. ", i++);    // i & incr
        switch (curr->trans_typ) // typ
        {
        case INIT:
            add_money(&m, curr->money);
            printf("[INIT]  ");
            break;
        case INCOME:
            add_money(&m, curr->money);
            printf("[INCOME] ");
            break;
        case SPENT:
            subtract_moeny(&m, curr->money);
            printf("[SPENT] ");
            break;
        case HOLDING:
            add_money(&m, curr->money);
            printf("[HOLDING] ");
            break;
        default:
            add_money(&m, curr->money);
            printf("[UNKNOWN TRANS_TYP] ");
            break;
        }
        printf(" %s ", curr->desc);         // description
        print_moneyval(curr->money);        // value
        printf("(%ld)\n", curr->timestamp); // creation time and LF

        curr = curr->next;
    }

    printf("Total Records: %ld\nBalance: ", --i);
    print_moneyval(&m);
    puts("\nEOF.");
    return;
}
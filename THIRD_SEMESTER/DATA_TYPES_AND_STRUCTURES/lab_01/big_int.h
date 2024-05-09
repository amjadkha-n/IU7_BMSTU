#ifndef BIGINT_H
#define BIGINT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INT_LEN 30
#define MAX_MULTYPLICATION_LEN 71

typedef struct
{
    int is_negative;
    int data[MAX_MULTYPLICATION_LEN];
    int data_len;
} bigint_t;

void print_bigint(bigint_t *a);
int str_to_bigint(bigint_t *a, char str[]);
int cmp_bigint(bigint_t *a, bigint_t *b);

#endif
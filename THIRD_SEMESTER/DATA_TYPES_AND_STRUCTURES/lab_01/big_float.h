#ifndef BIGFLOAT_H
#define BIGFLOAT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_MANTISSE_LEN 41

typedef struct
{
    int is_negative;
    int mantisse[MAX_MANTISSE_LEN];
    int mantisse_len;
    int order;
} bigfloat_t;

void print_bigfloat(bigfloat_t *a);
int str_to_bigfloat(bigfloat_t *a, char str[]);
int cmp_bigfloat(bigfloat_t *a, bigfloat_t *b);

#endif
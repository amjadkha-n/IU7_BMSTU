#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "big_int.h"
#include "big_float.h"

#define STR_LEN 256
#define BASE 10
#define MAX_OUTPUT_LEN 30

int read_str(char *s, size_t max_len);
void bigint_to_digit_multiplication(bigint_t *res, bigint_t *a, int b);
void bigint_sum(bigint_t *res, bigint_t *a, bigint_t *b, int extra_zeros_count);
int bigint_to_bigfloat_multiplication(bigfloat_t *res, bigint_t *a, bigfloat_t *b);

#endif
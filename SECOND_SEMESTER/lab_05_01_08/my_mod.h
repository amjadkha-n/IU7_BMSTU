#ifndef MY_MOD_H
#define MY_MOD_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

#define ERROR_FILE -4
#define ERROR_SEEK -3
#define ERROR_NULL_POINTER -2
#define ERROR_NO_LOC_MAX -1
#define SUCCESS 0
#define ERROR_FIND_LOC_MAX 1

int min(int a, int b);
void swap(int *a, int *b);
void swap_min(int *a, int *b);
int process(FILE *f, int *min_dist);
char *my_str_err(int errnum);
void myperror(const char *err);

#endif  // MY_MOD_H

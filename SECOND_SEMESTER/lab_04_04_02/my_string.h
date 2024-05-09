#ifndef MY_STRING_H
#define MY_STRING_H
#include <stddef.h>

#define MAX_STR_SIZE 257

int read_str(char *str, size_t *len_str);
int split_str(char *str, size_t len_str, char arr_words[][MAX_STR_SIZE], size_t *count_words);

#endif

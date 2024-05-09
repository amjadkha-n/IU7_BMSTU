#ifndef MY_STRING_H
#define MY_STRING_H

#include <stddef.h>

#define MAX_STR_SIZE 257
#define MAX_WORD_SIZE 17

int read_str(char *str, size_t *len_str);

int split_str(char *str, size_t len_str, char arr_words[][MAX_WORD_SIZE], size_t *count_words);

int is_repeat(char arr_words[][MAX_WORD_SIZE], size_t index);

void print_occurrences(char arr_words1[][MAX_WORD_SIZE], size_t count_words1, char arr_words2[][MAX_WORD_SIZE], size_t count_words2);

#endif /* MY_STRING_H */

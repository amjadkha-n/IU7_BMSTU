#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 257
#define MAX_WORD_SIZE 17

#define ERR_EMPTY_STR 1
#define ERR_STR_LEN 2
#define ERR_INPUT 3
#define ERR_WORD_LEN 4
#define ERR_NO_WORDS 5
#define ERR_ONE_WORD 6
#define ERR_ONLY_SAME_WORDS 7

#define SEPARATORS " ,;:-.!? "

int read_input(char *str, size_t *len_str);
int split_str(char *str, size_t len_str, char arr_words[][MAX_WORD_SIZE], size_t *count_words);
void del_repeat_first_char(char *word);
int fill_new_str_by_reversed_array(char arr_words[][MAX_WORD_SIZE], size_t count_words, char *new_str);

#endif /* MY_STRING_H */

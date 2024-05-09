#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

#define MAX_STR_SIZE 257

int main(void)
{
    char str[MAX_STR_SIZE];
    size_t len_str = 0;

    char arr_words[MAX_STR_SIZE / 2][MAX_WORD_SIZE];
    size_t count_words = 0;

    char new_str[MAX_STR_SIZE] = "";

    int error;

    error = read_input(str, &len_str);
    if (error != EXIT_SUCCESS)
        return error;

    error = split_str(str, len_str, arr_words, &count_words);
    if (error != EXIT_SUCCESS)
        return error;

    error = fill_new_str_by_reversed_array(arr_words, count_words, new_str);
    if (error != EXIT_SUCCESS)
        return error;
    
    printf("Result: %s\n", new_str);

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(void)
{
    char str1[MAX_STR_SIZE];
    char str2[MAX_STR_SIZE];

    size_t len_str1 = 0, len_str2 = 0;

    char arr_words1[MAX_STR_SIZE / 2][MAX_WORD_SIZE], arr_words2[MAX_STR_SIZE / 2][MAX_WORD_SIZE];

    size_t count_words1 = 0, count_words2 = 0;

    int error = read_str(str1, &len_str1);
    if (error != EXIT_SUCCESS)
        return error;

    error = read_str(str2, &len_str2);
    if (error != EXIT_SUCCESS)
        return error;

    error = split_str(str1, len_str1, arr_words1, &count_words1);
    if (error != EXIT_SUCCESS)
        return error;

    error = split_str(str2, len_str2, arr_words2, &count_words2);
    if (error != EXIT_SUCCESS)
        return error;

    print_occurrences(arr_words1, count_words1, arr_words2, count_words2);

    return EXIT_SUCCESS;
}

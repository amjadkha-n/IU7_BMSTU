#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

int read_str(char *str, size_t *len_str)
{
    char check_str[MAX_STR_SIZE + 1];

    char *p = fgets(check_str, MAX_STR_SIZE + 1, stdin);

    if (p == NULL)
        return 1;

    if (check_str[0] == '\n')
    {
        strcpy(str, check_str);
        *len_str = 1;
        return EXIT_SUCCESS;
    }

    size_t len_check_str = strlen(check_str);

    if ((len_check_str == MAX_STR_SIZE) && (check_str[len_check_str - 1] != '\n'))
        return 2;

    if (check_str[len_check_str - 1] == '\n')
        check_str[len_check_str - 1] = '\0';

    strcpy(str, check_str);
    *len_str = len_check_str - 1;

    return EXIT_SUCCESS;
}

int split_str(char *str, size_t len_str, char arr_words[][MAX_STR_SIZE], size_t *count_words)
{
    char word[MAX_STR_SIZE];
    size_t len_word = 0;

    for (size_t i = 0; i <= len_str; i++)
    {
        if (isspace(str[i]) || str[i] == '\0')
        {
            if (len_word > 0)
            {
                word[len_word] = '\0';
                strcpy(arr_words[(*count_words)++], word);

                len_word = 0;
            }
        }
        else if (len_word < MAX_STR_SIZE - 1)
            word[len_word++] = str[i];
        else
            return 4;
    }

    if (*count_words != 3)
        return 5;

    return EXIT_SUCCESS;
}

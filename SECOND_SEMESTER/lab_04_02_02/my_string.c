# include "my_string.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define EMPTY_STR_ERR 1
# define STR_LEN_ERR 2
# define INPUT_ERR 3

# define WORD_LEN_ERR 4
# define NO_WORDS_ERR 5

# define TRUE 1
# define FALSE 0

# define SEPARATORS " ,;:-.!?"

int read_str(char *str, size_t *len_str)
{
    char check_str[MAX_STR_SIZE + 1];

    char *p = fgets(check_str, MAX_STR_SIZE + 1, stdin);

    if (p == NULL)
        return INPUT_ERR; 

    if (check_str[0] == '\n')
        return EMPTY_STR_ERR;

    size_t len_check_str = strlen(check_str);
    
    if ((len_check_str == MAX_STR_SIZE) && (check_str[len_check_str - 1] != '\n'))
        return STR_LEN_ERR;

    if (check_str[len_check_str - 1] == '\n')
        check_str[len_check_str - 1] = '\0';
    // Copy the input string (without the trailing newline) to the output buffer
    strcpy(str, check_str);
    *len_str = len_check_str - 1;

    return EXIT_SUCCESS;
}

int split_str(char *str, size_t len_str, char arr_words[][MAX_WORD_SIZE], size_t *count_words)
{
    char word[MAX_WORD_SIZE];
    size_t len_word = 0;

    for (size_t i = 0; i <= len_str; i++)
    {
        if (strchr(SEPARATORS, str[i]))
        {
            if (len_word > 0)
            {
                // terminate the word string with a null character
                word[len_word] = '\0';
                // copy the word to the next available slot in the array of words
                strcpy(arr_words[(*count_words)++], word);
                len_word = 0;
            }
        }
        else if (len_word < MAX_WORD_SIZE - 1)
            word[len_word++] = str[i];
        else
            return WORD_LEN_ERR;
    }

    if (*count_words == 0)
        return NO_WORDS_ERR;

    return EXIT_SUCCESS;
}

int is_repeat(char arr_words[][MAX_WORD_SIZE], size_t index)
{
    for (size_t i = 0; i < index; i++)
    {
        // Compare the current word with all previous words
        if (strcmp(arr_words[i], arr_words[index]) == 0)
        {   
            return i != index;
        }
    }

    return FALSE;
}

void print_occurrences(char arr_words1[][MAX_WORD_SIZE], size_t count_words1, char arr_words2[][MAX_WORD_SIZE], size_t count_words2)
{
    printf("Result:\n");
    for (size_t i = 0; i < count_words1; i++)
    {
        if (is_repeat(arr_words1, i) == FALSE)
        {
            int is_occur = FALSE;
            for (size_t j = 0; j < count_words2; j++)
            {
                if (strcmp(arr_words1[i], arr_words2[j]) == 0)
                    is_occur = TRUE;
            }

            printf("%s %s\n", arr_words1[i], is_occur ? "yes" : "no");
        }
    }
} 

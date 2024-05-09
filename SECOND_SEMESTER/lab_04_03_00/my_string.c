# include "my_string.h"
# include <string.h>

# define SEPERATORS " ;:-,.?! "
int read_input(char *str, size_t *len_str)
{
    if (fgets(str, MAX_STR_SIZE, stdin) == NULL)
        return ERR_INPUT;
    
    *len_str = strlen(str);

    if (str[*len_str - 1] == '\n')
        *len_str -= 1;

    if (*len_str == 0)
        return ERR_EMPTY_STR;

    if (*len_str == MAX_STR_SIZE - 1 && str[*len_str - 1] != '\n')
        return ERR_STR_LEN;

    return EXIT_SUCCESS; 
}


int split_str(char *str, size_t len_str, char arr_words[][MAX_WORD_SIZE], size_t *count_words) 
{
    size_t len_word = 0;

    for (size_t i = 0; i < len_str; i++)
    {
        if (strchr(SEPARATORS, str[i]))
        {
            if (len_word > 0)
            {
                arr_words[*count_words][len_word] = '\0';
                (*count_words)++;
                len_word = 0;
            }
        } 
        else if (len_word < MAX_WORD_SIZE - 1)
        {
            arr_words[*count_words][len_word++] = str[i];
        } 
        else
        {
            return ERR_WORD_LEN;
        }
    }

    if (len_word > 0)
    {
        arr_words[*count_words][len_word] = '\0';
        (*count_words)++;
    }

    if (*count_words == 0)
        return ERR_NO_WORDS;

    return EXIT_SUCCESS;
}

void del_repeat_first_char(char *word)
{
    char first_char = word[0];
    size_t len_new_word = 1;

    for (size_t i = 1; word[i] != '\0'; i++)
    {
        if (word[i] != first_char)
        {
            word[len_new_word++] = word[i];
        }
    }

    word[len_new_word] = '\0';
}

int fill_new_str_by_reversed_array(char arr_words[][MAX_WORD_SIZE], size_t count_words, char *new_str)
{
    if (count_words == 1)
        return ERR_ONE_WORD;

    int is_all_words_same = 1;

    char last_word[MAX_WORD_SIZE];
    strcpy(last_word, arr_words[count_words - 1]);

    for (int i = count_words - 2; i >= 0; i--) 
    {
        if (strcmp(arr_words[i], last_word) != 0)
        {
            is_all_words_same = 0;
            del_repeat_first_char(arr_words[i]);
            strcat(new_str, arr_words[i]);
            strcat(new_str, " ");
        }
    }

    if (is_all_words_same)
        return ERR_ONLY_SAME_WORDS;

    // Remove the last space if it exists
    if (new_str[strlen(new_str) - 1] == ' ')
    {
        new_str[strlen(new_str) - 1] = '\0';
    }

    return EXIT_SUCCESS;
}

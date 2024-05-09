#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include <string.h> 

#define WORD_LEN 12
#define LINE_LEN 4

int main(void)
{
    char arr_str1[LINE_LEN][WORD_LEN] = { "Hello World!", "123456789", "", "Program" };
    char arr_str2[LINE_LEN][WORD_LEN] = { "He", "654", "", "Pro" };
    int arr_ch[LINE_LEN] = { 'H', '\0', 'P', 'P' };

    int count_error = 0;

    for (size_t i = 0; i < LINE_LEN; i++)
    {
        if (my_strpbrk(arr_str1[i], arr_str2[i]) != strpbrk(arr_str1[i], arr_str2[i]))
            count_error++;
        if (my_strspn(arr_str1[i], arr_str2[i]) != strspn(arr_str1[i], arr_str2[i]))
            count_error++;
        if (my_strcspn(arr_str1[i], arr_str2[i]) != strcspn(arr_str1[i], arr_str2[i]))
            count_error++;
        if (my_strchr(arr_str1[i], arr_ch[i]) != strchr(arr_str1[i], arr_ch[i]))
            count_error++;
        if (my_strrchr(arr_str1[i], arr_ch[i]) != strrchr(arr_str1[i], arr_ch[i]))
            count_error++;
    }
    printf("Count of errors: %d\n", count_error);

    return 0;
}

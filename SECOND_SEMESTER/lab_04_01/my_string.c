# include <string.h>
# include "my_string.h"
// The strpbrk function searches for the first occurrence in the string
// pointed to by the argument str1 of one of the characters
// included in the string pointed to by the argument str2
char *my_strpbrk(char *str1, char *str2)
{
    size_t i = 0;
    while (str1[i] != '\0')
    {
        size_t j = 0;
        while (str2[j] != '\0')
        {
            if (str1[i] == str2[j])
                return &str1[i];
            j++;
        }
        i++;
    }
    return NULL;
}

// The strspn function determines the maximum length of the initial section of the string
// pointed to by the argument str1, containing only the characters of the string
// pointed to by the argument str2.
// If the first character of string str1 is not included in string str2,
// then the returned length is 0

size_t my_strspn(char *str1, char *str2)
{
    size_t n = 0;
    size_t i = 0;

    while (str1[i] != '\0')
    {
        size_t j = 0;
        while (str2[j] != '\0' && str1[i] != str2[j])
        {
            j++;
        }
        if (str1[i] != str2[j])
        {
            return n;
        }
        n++;
        i++;
    }
    return n;
}

// The strcspn function determines the maximum length of the initial section of the string
// pointed to by the argument str1, which does not contain any of the characters of the string
// pointed to by the argument str2

size_t my_strcspn(char *str1, char *str2)
{
    size_t n = 0;
    size_t i = 0;

    while (str1[i] != '\0')
    {
        size_t j = 0;
        while (str2[j] != '\0')
        {
            if (str1[i] == str2[j])
                return n;
            j++;
        }
        n++;
        i++;
    }
    return n;
}

// The strchr function searches for the first occurrence of the character
// whose code is specified in the ch argument in the string
// pointed to by the str argument

char *my_strchr(char *str, int ch)
{
    size_t i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == ch)
            return &str[i];
        i++;
    }
    if (ch == '\0')
        return &str[i];
    return NULL;
}

// The strrchr function searches for the last occurrence of the character
// whose code is specified in the ch argument in the string
// pointed to by the str argument

char *my_strrchr(char *str, int ch)
{
    size_t i = 0;
    char *p = NULL;

    while (str[i] != '\0')
    {
        if (str[i] == ch)
            p = &str[i];
        i++;
    }

    if (ch == '\0')
        return &str[i];
    return p;
}

#ifndef STRING_H
#define STRING_H

#include <stddef.h>

char *my_strpbrk(char *str1, char *str2);
size_t my_strspn(char *str1, char *str2);
size_t my_strcspn(char *str1, char *str2);
char *my_strchr(char *str, int ch);
char *my_strrchr(char *str, int ch);

#endif

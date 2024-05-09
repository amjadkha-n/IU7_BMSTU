#include <stdio.h>
#include "../inc/check_main.h"
#include "../inc/arguments.h"
#include "../inc/functions.h"

/**
 * @file
 * @brief This file contains functions to check the mysort function with various data types.
 */

/**
 * @brief Compare function for characters.
 *
 * This function is used for comparing characters when sorting.
 *
 * @param p_1 Pointer to the first character to compare.
 * @param p_2 Pointer to the second character to compare.
 * @return Returns a negative value if p_1 is less than p_2, 0 if they are equal,
 * or a positive value if p_1 is greater than p_2.
 */

int compare_char(const void *p_1, const void *p_2)
{
    const char *p_char_1 = p_1;
    const char *p_char_2 = p_2;

    if (*p_char_1 > *p_char_2)
        return 1;
    else if (*p_char_1 < *p_char_2)
        return -1;
    else
        return 0;
}
/**
 * @brief Compare function for short integers.
 *
 * This function is used for comparing short integers when sorting.
 *
 * @param p_1 Pointer to the first short integer to compare.
 * @param p_2 Pointer to the second short integer to compare.
 * @return Returns a negative value if p_1 is less than p_2, 0 if they are equal,
 * or a positive value if p_1 is greater than p_2.
 */
int compare_short(const void *p_1, const void *p_2)
{
    const short int *p_sh_int_1 = p_1;
    const short int *p_sh_int_2 = p_2;

    if (*p_sh_int_1 > *p_sh_int_2)
        return 1;
    else if (*p_sh_int_1 < *p_sh_int_2)
        return -1;
    else
        return 0;
}

/**
 * @brief Compare function for long long integers.
 *
 * This function is used for comparing long long integers when sorting.
 *
 * @param p_1 Pointer to the first long long integer to compare.
 * @param p_2 Pointer to the second long long integer to compare.
 * @return Returns a negative value if p_1 is less than p_2, 0 if they are equal,
 * or a positive value if p_1 is greater than p_2.
 */
int compare_long_long(const void *p_1, const void *p_2)
{
    const long long int *p_ll_int_1 = p_1;
    const long long int *p_ll_int_2 = p_2;

    if (*p_ll_int_1 > *p_ll_int_2)
        return 1;
    else if (*p_ll_int_1 < *p_ll_int_2)
        return -1;
    else
        return 0;
}

/**
 * @brief Check mysort function with characters.
 *
 * This function checks the mysort function with an array of characters.
 *
 * @return Returns 0 if the mysort function works correctly, or 1 if there is an error.
 */
int check_mysort_with_char()
{
    int test_length = 10;
    char ch_arr[] = {'c', 'd', 'a', 'b', 'z', 'y', 'x', 'e', 'f', 'k'};
    char answer[] = {'a', 'b', 'c', 'd', 'e', 'f', 'k', 'x', 'y', 'z'};
    int is_wrong = 0;

    mysort(ch_arr, test_length, sizeof(char), compare_char);

    for (int i = 0; i < test_length; i++)
    {
        if (ch_arr[i] != answer[i])
        {
            is_wrong = 1;
            break;
        }
    }
    return is_wrong;
}
/**
 * @brief Check mysort function with short integers.
 *
 * This function checks the mysort function with an array of short integers.
 *
 * @return Returns 0 if the mysort function works correctly, or 1 if there is an error.
 */
int check_mysort_with_sh_int()
{
    int test_length = 10;
    short sh_int_arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    short answer[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int is_wrong = 0;

    mysort(sh_int_arr, test_length, sizeof(short), compare_short);

    for (int i = 0; i < test_length; i++)
    {
        if (sh_int_arr[i] != answer[i])
        {
            is_wrong = 1;
            break;
        }
    }
    return is_wrong;
}
/**
 * @brief Check mysort function with long long integers.
 *
 * This function checks the mysort function with an array of long long integers.
 *
 * @return Returns 0 if the mysort function works correctly, or 1 if there is an error.
 */
int check_mysort_with_ll_int()
{
    int test_length = 10;
    long long llint_arr[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    long long answer[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int is_wrong = 0;

    mysort(llint_arr, test_length, sizeof(long long int), compare_long_long);

    for (int i = 0; i < test_length; i++)
    {
        if (llint_arr[i] != answer[i])
        {
            is_wrong = 1;
            break;
        }
    }
    return is_wrong;
}
/**
 * @brief Check the mysort function with various data types.
 *
 * This function accumulates error counts from checking mysort with different data types.
 *
 * @return Returns the total error count.
 */
int check_mysort()
{
    int error_amount = 0;
    error_amount += check_mysort_with_char();
    error_amount += check_mysort_with_sh_int();
    error_amount += check_mysort_with_ll_int();
    return error_amount;
}

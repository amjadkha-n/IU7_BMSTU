#include <stdio.h>
#include "../inc/check_main.h"
#include "../inc/arguments.h"
#include "../inc/functions.h"

/**
 * @file
 * @brief This file contains functions to check the key function with various test cases.
 */

/**
 * @brief Check key function without negative values.
 *
 * This function checks the key function when there are no negative values in the input array.
 *
 * @return Returns 0 if the key function works correctly, or 1 if there is an error.
 */
int check_key_without_negative()
{
    int is_wrong = 0;
    int test_length = 10;
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *arr_after_key = NULL;
    int *end_arr_after_key = NULL;

    // Call the key function
    if (key(arr, arr + test_length, &arr_after_key, &end_arr_after_key) != OK)
        return 1;

    // Check the length of the resulting array
    if (end_arr_after_key - arr_after_key != test_length)
        is_wrong = 1;

    // Check if the elements match the original array
    for (int *p_1 = arr_after_key, *p_2 = arr; p_1 != end_arr_after_key; ++p_1, ++p_2)
    {
        if (*p_1 != *p_2)
        {
            is_wrong = 1;
            break;
        }
    }

    free(arr_after_key);
    return is_wrong;
}

/**
 * @brief Check key function with wrong arguments.
 *
 * This function checks the key function with incorrect arguments.
 *
 * @return Returns 0 if the key function works correctly, or 1 if there is an error.
 */
int check_key_with_wrong_arguments()
{
    int is_wrong = 0;

    // Test case 1: Passing NULL arguments
    if (key(NULL, NULL, NULL, NULL) == OK)
        is_wrong = 1;

    // Test case 2: Passing NULL pointers for output arguments
    int check = 0;
    int *p = &check;
    
    if (key(&check, &check, NULL, NULL) == OK)
        is_wrong = 1;

    if (key(&check + 1, &check, &p, NULL) == OK)
        is_wrong = 1;

    if (key(&check + 1, &check, NULL, &p) == OK)
        is_wrong = 1;

    return is_wrong;
}

/**
 * @brief Check key function with one negative value.
 *
 * This function checks the key function when there is one negative value in the input array.
 *
 * @return Returns 0 if the key function works correctly, or 1 if there is an error.
 */
int check_key_with_one_negative()
{
    int is_wrong = 0;
    int test_length = 10;
    int arr[] = {0, 1, 2, 3, 4, -5, 6, 7, 8, 9};
    int *arr_after_key = NULL;
    int *end_arr_after_key = NULL;

    // Call the key function
    if (key(arr, arr + test_length, &arr_after_key, &end_arr_after_key) != OK)
        return 1;

    // Check if the length of the resulting array is 5
    if (end_arr_after_key - arr_after_key != 5)
        is_wrong = 1;

    // Check if the elements match the original array
    for (int *p_1 = arr_after_key, *p_2 = arr; p_1 != end_arr_after_key; ++p_1, ++p_2)
    {
        if (*p_1 != *p_2)
        {
            is_wrong = 1;
            break;
        }
    }

    free(arr_after_key);
    return is_wrong;
}
/**
 * @brief Check key function with multiple negative values.
 *
 * This function checks the key function when there are multiple negative values in the input array.
 *
 * @return Returns 0 if the key function works correctly, or 1 if there is an error.
 */
int check_key_with_multiple_negatives()
{
    int is_wrong = 0;
    int test_length = 10;
    int arr[] = {0, 1, -2, 3, -4, -5, 6, 7, 8, 9};
    int *arr_after_key = NULL;
    int *end_arr_after_key = NULL;

    // Call the key function
    if (key(arr, arr + test_length, &arr_after_key, &end_arr_after_key) != OK)
        return 1;

    // Check if the length of the resulting array is 5
    if (end_arr_after_key - arr_after_key != 5)
        is_wrong = 1;

    // Check if the elements match the original array
    for (int *p_1 = arr_after_key, *p_2 = arr; p_1 != end_arr_after_key; ++p_1, ++p_2)
    {
        if (*p_1 != *p_2)
        {
            is_wrong = 1;
            break;
        }
    }

    free(arr_after_key);
    return is_wrong;
}

/**
 * @brief Check the key function with various test cases.
 *
 * This function accumulates error counts from checking the key function with different test cases.
 *
 * @return Returns the total error count.
 */
int check_key()
{
    int error_amount = 0;
    error_amount += check_key_with_wrong_arguments();
    error_amount += check_key_without_negative();
    error_amount += check_key_with_one_negative();
    error_amount += check_key_with_multiple_negatives();
    return error_amount;
}

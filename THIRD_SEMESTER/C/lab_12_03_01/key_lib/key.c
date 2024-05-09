#include "../inc/main.h"

/**
* @brief Find the last negative element in an array.
*
* This function searches for the last negative element in the given array.
*
* @param arr Pointer to the start of the array.
* @param end_arr Pointer to the end of the array.
* @return Pointer to the last negative element or end_arr if no negative elements are found.
*/
const int *find_last_neg(const int *arr, const int *end_arr)
{
    // Start from the end of the array
    const int *ptr = end_arr - 1;
    // Find the last negative element
    while (ptr >= arr && *ptr >= 0)
    {
        ptr--;
    }
    if (ptr < arr)
    {
        // If no negative elements found, set pointer to end
        ptr = end_arr;
    }
    return ptr;
}   

/**
 * @brief Apply a filtering function to an array.
 *
 * @param pb_src A pointer to the beginning of the source array.
 * @param pe_src A pointer to the end of the source array.
 * @param[out] pb_dst A pointer to the beginning of the filtered destination array.
 * @param[out] pe_dst A pointer to the end of the filtered destination array.
 * @return An error code indicating success or failure.
 */

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || pb_src >= pe_src || pb_dst == NULL || pe_dst == NULL)
    {
        return KEY_ERROR;
    }
    const int *last_neg = find_last_neg(pb_src, pe_src);
    // Calculate the number of non-negative elements
    int n = last_neg - pb_src;

    if (n <= 0)
    {
        free(*pb_dst);
        return KEY_ERROR;
    }
    // Allocate memory for the new array
    *pb_dst = malloc(n * sizeof(int));
    if (*pb_dst == NULL)
    {
        return KEY_ERROR;
    }
    int *current_dst = *pb_dst;
    const int *current_src = pb_src;
    // Calculate a pointer to the end of the source array
    const int *p_end = pb_src + n;    

    while (current_src != p_end)
    {
        // Copy non-negative elements
        *(current_dst++) = *(current_src++);
    }
    *pe_dst = current_dst;

    return OK;
}




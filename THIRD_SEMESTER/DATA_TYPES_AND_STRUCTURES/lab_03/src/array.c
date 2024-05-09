#include <stdio.h>

#include "../inc/array.h"
/**
 * @brief Inserts an integer element into the array at the specified index.
 *
 * @param arr The array of integers.
 * @param len The current length of the array.
 * @param elem The integer element to be inserted.
 * @param ind The index at which the element should be inserted.
 * @return The new length of the array after insertion.
 */
size_t int_array_insert(int arr[], size_t len, int elem, size_t ind)
{
    int temp;
    for (size_t i = ind; i < len; i++)
    {
        temp = arr[i];
        arr[i] = elem;
        elem = temp;
    }
    arr[len] = elem;
    return ++len;
}
/**
 * @brief Inserts a size_t element into the array at the specified index.
 *
 * @param arr The array of size_t values.
 * @param len The current length of the array.
 * @param elem The size_t element to be inserted.
 * @param ind The index at which the element should be inserted.
 * @return The new length of the array after insertion.
 */
size_t size_t_array_insert(size_t arr[], size_t len, size_t elem, size_t ind)
{
    size_t temp;
    for (size_t i = ind; i < len; i++)
    {
        temp = arr[i];
        arr[i] = elem;
        elem = temp;
    }
    arr[len] = elem;
    return ++len;
}
/**
 * @brief Outputs an array of integers to the standard output.
 *
 * @param arr The array of integers to be outputted.
 * @param len The length of the array.
 */
void int_array_output(int arr[], size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
/**
 * @brief Outputs an array of size_t values to the standard output.
 *
 * @param arr The array of size_t values to be outputted.
 * @param len The length of the array.
 */
void size_t_array_output(size_t arr[], size_t len)
{
    for (size_t i = 0; i < len; i++)
        printf("%zu ", arr[i]);
    printf("\n");
}

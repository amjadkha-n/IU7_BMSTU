#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
/**
 * @brief Inserts an integer element into an integer array at a specified index.
 *
 * Inserts the given integer element into the integer array at the specified index.
 * Shifts the existing elements to make room for the new element.
 *
 * @param arr Integer array.
 * @param len Current length of the array.
 * @param elem Integer element to be inserted.
 * @param ind Index at which the element should be inserted.
 * @return The new length of the array after insertion.
 */
size_t int_array_insert(int arr[], size_t len, int elem, size_t ind);

/**
 * @brief Inserts a size_t element into a size_t array at a specified index.
 *
 * Inserts the given size_t element into the size_t array at the specified index.
 * Shifts the existing elements to make room for the new element.
 *
 * @param arr Size_t array.
 * @param len Current length of the array.
 * @param elem Size_t element to be inserted.
 * @param ind Index at which the element should be inserted.
 * @return The new length of the array after insertion.
 */
size_t size_t_array_insert(size_t arr[], size_t len, size_t elem, size_t ind);

/**
 * @brief Outputs the elements of an integer array to the standard output.
 *
 * Outputs the elements of the integer array to the standard output,
 * separated by spaces and followed by a newline character.
 *
 * @param arr Integer array.
 * @param len Length of the array.
 */
void int_array_output(int arr[], size_t len);

/**
 * @brief Outputs the elements of a size_t array to the standard output.
 *
 * Outputs the elements of the size_t array to the standard output,
 * separated by spaces and followed by a newline character.
 *
 * @param arr Size_t array.
 * @param len Length of the array.
 */
void size_t_array_output(size_t arr[], size_t len);

#endif

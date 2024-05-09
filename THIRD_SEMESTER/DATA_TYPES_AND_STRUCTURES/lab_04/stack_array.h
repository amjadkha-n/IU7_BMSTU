#ifndef __STACK_ARRAY_H__
#define __STACK_ARRAY_H__

#include "structures.h"
/**
 * @brief Removes an element from the array stack.
 *
 * @param array Pointer to the array stack structure.
 * @return int Returns OK if successful, STACK_EMPTY if the stack is empty.
 */
int array_pop(stack_array_t *array);
/**
 * @brief Adds an element to the array stack.
 *
 * @param array Pointer to the array stack structure.
 * @param i Row index of the element.
 * @param j Column index of the element.
 * @param direction Direction of the element.
 * @return int Returns OK if successful.
 */
int array_push(stack_array_t *array, const int i, const int j, const int direction);
/**
 * @brief Peeks at the top element of the array stack.
 *
 * @param array Pointer to the array stack structure.
 * @param i Pointer to store the row index.
 * @param j Pointer to store the column index.
 * @param direction Pointer to store the direction.
 * @return int Returns OK if successful, STACK_EMPTY if the stack is empty.
 */
int array_peek(stack_array_t *array, int *i, int *j, int *direction);

#endif

#include <stdlib.h>

#include "stack_array.h"
/**
 * @brief Operation successful.
 */
#define OK 0

/**
 * @brief Stack is empty error.
 */
#define STACK_EMPTY 7

/**
 * @brief Removes an element from the array stack.
 *
 * @param array Pointer to the array stack structure.
 * @return int Returns OK if successful, STACK_EMPTY if the stack is empty.
 */
int array_pop(stack_array_t *array)
{
    if (!array->size)
    {
        return STACK_EMPTY;
    }

    array->size--;

    return OK;
}
/**
 * @brief Adds an element to the array stack.
 *
 * @param array Pointer to the array stack structure.
 * @param i Row index of the element.
 * @param j Column index of the element.
 * @param direction Direction of the element.
 * @return int Returns OK if successful.
 */
int array_push(stack_array_t *array, const int i, const int j, const int direction)
{
    array_element_t new_peek;

    new_peek.i = i;
    new_peek.j = j;
    new_peek.direction = direction;

    *(array->ptr + ++array->size) = new_peek;

    return OK;
}
/**
 * @brief Peeks at the top element of the array stack.
 *
 * @param array Pointer to the array stack structure.
 * @param i Pointer to store the row index.
 * @param j Pointer to store the column index.
 * @param direction Pointer to store the direction.
 * @return int Returns OK if successful, STACK_EMPTY if the stack is empty.
 */
int array_peek(stack_array_t *array, int *i, int *j, int *direction)
{
    if (!array->ptr)
    {
        return STACK_EMPTY;
    }

    array_element_t peek;

    peek = *(array->ptr + array->size);
    *i = peek.i;
    *j = peek.j;
    *direction = peek.direction;

    return OK;
}

#include <stdlib.h>
#include <stdio.h>

#include "stack_list.h"
/**
 * @brief Code indicating successful operation.
 */
#define OK 0
#define MEMORY_ERROR 2
/**
 * @brief Code indicating an empty stack.
 */
#define STACK_EMPTY 7
/**
 * @brief Removes an element from the top of the linked-list stack.
 *
 * @param list Pointer to the linked-list stack.
 * @return OK if successful, STACK_EMPTY if the stack is empty.
 */
int list_pop(stack_list_t *list)
{
    list_element_t *old_peak = NULL;

    if (list->ptr == NULL)
    {
        return STACK_EMPTY;
    }

    old_peak = list->ptr;
    list->ptr = old_peak->next_elem;
    free(old_peak);

    return OK;
}
/**
 * @brief Adds a new element to the top of the linked-list stack.
 *
 * @param list Pointer to the linked-list stack.
 * @param i Row index.
 * @param j Column index.
 * @param direction Movement direction.
 * @return OK if successful, MEMORY_ERROR if memory allocation fails.
 */
int list_push(stack_list_t *list, const int i, const int j, const int direction)
{
    list_element_t *new_peak = NULL;

    if ((new_peak = malloc(sizeof(list_element_t))) == NULL)
    {
        return MEMORY_ERROR;
    }

    new_peak->i = i;
    new_peak->j = j;
    new_peak->direction = direction;
    new_peak->next_elem = list->ptr;
    list->ptr = new_peak;

    return OK;
}
/**
 * @brief Peeks at the top element of the linked-list stack.
 *
 * @param list Pointer to the linked-list stack.
 * @param i Pointer to store the row index.
 * @param j Pointer to store the column index.
 * @param direction Pointer to store the movement direction.
 * @return OK if successful, STACK_EMPTY if the stack is empty.
 */
int list_peek(stack_list_t *list, int *i, int *j, int *direction)
{
    list_element_t *new_peak = NULL;

    if (list->ptr == NULL)
    {
        return STACK_EMPTY;
    }

    new_peak = list->ptr;
    *i = new_peak->i;
    *j = new_peak->j;
    *direction = new_peak->direction;

    return OK;
}

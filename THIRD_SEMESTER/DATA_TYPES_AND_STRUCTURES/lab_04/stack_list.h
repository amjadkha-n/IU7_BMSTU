#ifndef __STACK_LIST_H__
#define __STACK_LIST_H__

#include "structures.h"
/**
 * @brief Removes an element from the top of the linked-list stack.
 *
 * @param list Pointer to the linked-list stack.
 * @return OK if successful, STACK_EMPTY if the stack is empty.
 */
int list_pop(stack_list_t *list);
/**
 * @brief Adds a new element to the top of the linked-list stack.
 *
 * @param list Pointer to the linked-list stack.
 * @param i Row index.
 * @param j Column index.
 * @param direction Movement direction.
 * @return OK if successful, MEMORY_ERROR if memory allocation fails.
 */
int list_push(stack_list_t *list, const int i, const int j, const int direction);
/**
 * @brief Peeks at the top element of the linked-list stack.
 *
 * @param list Pointer to the linked-list stack.
 * @param i Pointer to store the row index.
 * @param j Pointer to store the column index.
 * @param direction Pointer to store the movement direction.
 * @return OK if successful, STACK_EMPTY if the stack is empty.
 */
int list_peek(stack_list_t *list, int *i, int *j, int *direction);

#endif

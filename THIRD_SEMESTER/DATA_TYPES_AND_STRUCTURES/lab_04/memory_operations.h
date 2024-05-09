#ifndef __MEMORY_OPERATIONS_H__
#define __MEMORY_OPERATIONS_H__

#include "structures.h"
/**
 * @brief Allocates memory for the maze matrix.
 *
 * @param maze Pointer to the maze structure.
 * @return An integer code indicating the status of the memory allocation.
 */
int new_matrix(maze_t *const maze);
/**
 * @brief Frees the allocated memory for the maze matrix.
 *
 * @param maze Pointer to the maze structure.
 */
void free_memory(maze_t *const matrix);
/**
 * @brief Initializes stacks, allocating memory for the array-based stack.
 *
 * @param array Pointer to the array-based stack structure.
 * @param list Pointer to the linked list-based stack structure.
 * @param max_stack Maximum size of the stack.
 * @return An integer code indicating the status of the initialization.
 */
int init_stacks(stack_array_t *const array, stack_list_t *const list, const int max_stack);
/**
 * @brief Peeks at the top element of the stack.
 *
 * @param array Pointer to the array-based stack structure.
 * @param list Pointer to the linked list-based stack structure.
 * @param i Pointer to store the row index.
 * @param j Pointer to store the column index.
 * @param direction Pointer to store the direction.
 * @return An integer code indicating the status of the operation.
 */
int peek(stack_array_t *array, stack_list_t *list, int *i, int *j, int *direction);
/**
 * @brief Pops the top element from the stack.
 *
 * @param array Pointer to the array-based stack structure.
 * @param list Pointer to the linked list-based stack structure.
 * @return An integer code indicating the status of the operation.
 */
int pop(stack_array_t *array, stack_list_t *list);

/**
 * @brief Pushes a new element onto the stack.
 *
 * @param array Pointer to the array-based stack structure.
 * @param list Pointer to the linked list-based stack structure.
 * @param i Row index of the element to push.
 * @param j Column index of the element to push.
 * @param direction Direction of the element to push.
 * @return An integer code indicating the status of the operation.
 */
int push(stack_array_t *array, stack_list_t *list, const int i, const int j, const int direction);

/**
 * @brief Frees the memory used by the linked list-based stack.
 *
 * @param list Pointer to the linked list-based stack structure.
 */
void free_list(stack_list_t *list);

#endif

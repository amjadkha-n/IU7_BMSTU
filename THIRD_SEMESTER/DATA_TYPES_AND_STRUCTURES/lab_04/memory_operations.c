#include <stdlib.h>
#include <stdio.h>

#include "memory_operations.h"
#include "stack_list.h"
#include "stack_array.h"

#define ARRAY_STACK 1

#define OK 0
#define MEMORY_ERROR 2
#define STACK_EMPTY 7

extern int __stack_type;
/**
 * @brief Allocates memory for the maze matrix.
 *
 * @param maze Pointer to the maze structure.
 * @return An integer code indicating the status of the memory allocation.
 */
int new_matrix(maze_t *const maze)
{
    maze->matrix = malloc(maze->y * sizeof(char *));

    if (maze->matrix == NULL)
    {
        return MEMORY_ERROR;
    }

    for (int i = 0; i < maze->y; i++)
    {
        maze->matrix[i] = malloc(maze->x * sizeof(char));

        if (maze->matrix[i] == NULL)
        {
            return MEMORY_ERROR;
        }
    }

    return OK;
}
/**
 * @brief Frees the allocated memory for the maze matrix.
 *
 * @param maze Pointer to the maze structure.
 */
void free_memory(maze_t *const maze)
{
    if (maze->matrix == NULL)
    {
        return;
    }

    for (int i = 0; i < maze->y; i++)
    {
        if (maze->matrix[i] != NULL)
        {
            free(maze->matrix[i]);
        }
    }

    free(maze->matrix);
}
/**
 * @brief Initializes stacks, allocating memory for the array-based stack.
 *
 * @param array Pointer to the array-based stack structure.
 * @param list Pointer to the linked list-based stack structure.
 * @param max_stack Maximum size of the stack.
 * @return An integer code indicating the status of the initialization.
 */
int init_stacks(stack_array_t *const array, stack_list_t *const list, const int max_stack)
{
    list->ptr = NULL;
    array->ptr = NULL;
    array->size = 0;

    if ((array->ptr = malloc(max_stack * sizeof(array_element_t))) == NULL)
    {
        return MEMORY_ERROR;
    }

    return OK;
}
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
int peek(stack_array_t *array, stack_list_t *list, int *i, int *j, int *direction)
{
    if (__stack_type == ARRAY_STACK)
    {
        if (array_peek(array, i, j, direction))
        {
            return STACK_EMPTY;
        }
    }
    else
    {
        if (list_peek(list, i, j, direction))
        {
            return STACK_EMPTY;
        }
    }

    return OK;
}

/**
 * @brief Pops the top element from the stack.
 *
 * @param array Pointer to the array-based stack structure.
 * @param list Pointer to the linked list-based stack structure.
 * @return An integer code indicating the status of the operation.
 */
int pop(stack_array_t *array, stack_list_t *list)
{
    if (__stack_type == ARRAY_STACK)
    {
        if (array_pop(array))
        {
            return STACK_EMPTY;
        }
    }
    else
    {
        if (list_pop(list))
        {
            return STACK_EMPTY;
        }
    }

    return OK;
}
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
int push(stack_array_t *array, stack_list_t *list, const int i, const int j, const int direction)
{
    if (__stack_type == ARRAY_STACK)
    {
        if (array_push(array, i, j, direction))
        {
            return MEMORY_ERROR;
        }
    }
    else
    {
        if (list_push(list, i, j, direction))
        {
            return MEMORY_ERROR;
        }
    }

    return OK;
}
/**
 * @brief Frees the memory used by the linked list-based stack.
 *
 * @param list Pointer to the linked list-based stack structure.
 */
void free_list(stack_list_t *list)
{
    list_element_t *curr_element = list->ptr;

    while (curr_element != NULL)
    {
        list->ptr = curr_element->next_elem;
        free(curr_element);
        curr_element = list->ptr;
    }
}

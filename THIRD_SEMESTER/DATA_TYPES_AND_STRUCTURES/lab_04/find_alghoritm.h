#ifndef __FIND_ALGHORITM_H__
#define __FIND_ALGHORITM_H__

#include <stdint.h>
#include "structures.h"
/**
 * @brief Finds a way through the maze using a stack-based algorithm.
 *
 * Finds a way through the maze using a stack-based algorithm. The type of stack (array or list) is determined
 * by the stack_type parameter. The algorithm writes the steps to the log file specified by LOG_FILE.
 *
 * @param stack_type   Type of stack to be used (STACK_ARRAY or STACK_LIST).
 * @param array        Pointer to the array-based stack.
 * @param list         Pointer to the list-based stack.
 * @param maze         Pointer to the maze structure.
 * @param stack_size   Pointer to the variable storing the stack size.
 * @param max_stack    Maximum size of the stack.
 * @return An integer code indicating the operation result.
 */
int find_way(int stack_type, stack_array_t *array, stack_list_t *list, maze_t *maze,
    int *stack_size, const int max_stack);

#endif

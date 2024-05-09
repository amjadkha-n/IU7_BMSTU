#ifndef __READ_H__
#define __READ_H__

#include "structures.h"
/**
 * @brief Reads maze information from a file.
 *
 * @param maze The maze structure to store the matrix.
 * @param f The file pointer to read the maze from.
 * @param max_stack Pointer to the variable storing the maximum stack size.
 * @return int Returns OK if successful, an error code otherwise.
 */
int read_file(maze_t *maze, FILE *f, int *max_stack);
/**
 * @brief Reads the user's choice for stack type (array or list).
 *
 * @param type Pointer to the variable storing the stack type.
 * @return int Returns OK if successful, INVALID_STACK_TYPE if input is invalid.
 */
int read_stack_type(int *type);
/**
 * @brief Reads the user's choice for the main action (find path or manual stack operation).
 *
 * @param action_type Pointer to the variable storing the action type.
 * @return int Returns OK if successful, INVALID_INPUT if input is invalid.
 */
int read_action(int *action_type);
/**
 * @brief Reads the user's choice for stack operations (add, remove, etc.).
 *
 * @param action Pointer to the variable storing the action.
 * @return int Returns OK if successful, INVALID_INPUT if input is invalid.
 */
int read_stack_action(int *stack_action);
/**
 * @brief Reads the user's input for the number of elements to add to the stack.
 *
 * @param count Pointer to the variable storing the count.
 * @param curr_stack Current size of the stack.
 * @return int Returns OK if successful, INVALID_INPUT if input is invalid.
 */
int read_add_info(int *count, int curr_stack);
/**
 * @brief Reads the user's input for the number of elements to delete from the stack.
 *
 * @param count Pointer to the variable storing the count.
 * @param curr_stack Current size of the stack.
 * @return int Returns OK if successful, INVALID_INPUT if input is invalid, STACK_EMPTY if stack is empty.
 */
int read_delete_info(int *count, int curr_stack);
/**
 * @brief Reads the user's input for a stack element.
 *
 * @param i Pointer to the variable storing the stack element.
 * @return int Returns OK if successful, INVALID_INPUT if input is invalid.
 */
int read_struct(int *i);

#endif

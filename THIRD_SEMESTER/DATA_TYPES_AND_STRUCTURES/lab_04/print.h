#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdint.h>
#include "structures.h"
/**
 * @brief Prints the maze matrix with colored formatting for special characters.
 *
 * @param maze The maze structure to print.
 */
void print_maze(const maze_t maze);
/**
 * @brief Prints information about the stack and wayfinding time.
 *
 * @param stack_size Size of the stack.
 */
void print_compare(const int stack_size);
/**
 * @brief Prints the stack information and addresses to a file.
 *
 * @param list The linked list-based stack structure.
 * @param array The array-based stack structure.
 * @param f The file pointer to print to.
 * @param address_array Array of addresses to print.
 * @param size Size of the address array.
 */
void print_stack(const stack_list_t list, const stack_array_t array, FILE *f,
    list_element_t **address_array, const int size);
/**
 * @brief Prints a sample stack to a file.
 *
 * @param list The linked list-based stack structure.
 * @param array The array-based stack structure.
 * @param f The file pointer to print to.
 * @param array_time Time taken for array operations.
 * @param list_time Time taken for list operations.
 */
void print_sample_stack(const stack_list_t list, const stack_array_t array, FILE *f,
    int64_t *array_time, int64_t *list_time);
/**
 * @brief Prints the processing time of array and list-based stacks.
 *
 * @param array_time Time taken for array operations.
 * @param list_time Time taken for list operations.
 */
void print_results(int64_t array_time, int64_t list_time);
/**
 * @brief Prints the memory occupied by array and list-based stacks.
 *
 * @param size Size of the stack.
 */
void print_memory_results(const int size);

#endif

#ifndef __STACK_H__
#define __STACK_H__

#include "defines.h"

typedef struct
{
    char opts[MAX_ARR_LEN];  // Array of operators
    int vals[MAX_ARR_LEN];   // Array of operands
    int length;              // length of the stack
} arr_stack_t;
/**
 * @brief Pop an element from the array stack.
 *
 * This function removes the top element from the array stack and
 * retrieves the operator and value stored in that element.
 *
 * @param stack Pointer to the array stack.
 * @param opt Pointer to store the retrieved operator.
 * @param val Pointer to store the retrieved value.
 * @return EXIT_SUCCESS if the operation is successful, ERR_EMPTY_STACK
 *         if the stack is empty.
 */
int as_pop(arr_stack_t *stack, char *opt, int *val);
/**
 * @brief Push an element onto the array stack.
 *
 * This function adds a new element to the array stack with the specified
 * operator and value.
 *
 * @param stack Pointer to the array stack.
 * @param opt Operator to be pushed onto the stack.
 * @param val Value to be pushed onto the stack.
 * @return EXIT_SUCCESS if the operation is successful, ERR_FULL_STACK
 *         if the stack is full.
 */
int as_push(arr_stack_t *stack, char opt, int val);
/**
 * @brief Print the contents of the array stack.
 *
 * This function prints the contents of the array stack, preserving the
 * order of elements in the stack.
 *
 * @param stack Pointer to the array stack.
 * @return EXIT_SUCCESS if the operation is successful, ERR_EMPTY_STACK
 *         if the stack is empty.
 */
int as_print(arr_stack_t *stack);
/**
 * @brief Evaluate an arithmetic expression using a stack.
 *
 * This function evaluates an arithmetic expression represented by an
 * array of integers using two array stacks (stack and stack_opt) to
 * store operators and values during the calculation.
 *
 * @param arr Array of integers representing the arithmetic expression.
 * @return The result of the expression evaluation.
 */
int stack_res(int arr[NUMS_COUNT]);

#endif

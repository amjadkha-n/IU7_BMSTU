#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../inc/tree.h"
#include "../inc/stack.h"
#include "../inc/defines.h"
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
int as_pop(arr_stack_t *stack, char *opt, int *val)
{
    if (!stack->length)
        return ERR_EMPTY_STACK;

    stack->length--;
    *opt = stack->opts[stack->length];
    *val = stack->vals[stack->length];
    return EXIT_SUCCESS;
}
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
int as_push(arr_stack_t *stack, char opt, int val)
{
    if (stack->length == MAX_ARR_LEN)
        return ERR_FULL_STACK;

    stack->opts[stack->length] = opt;
    stack->vals[stack->length] = val;
    stack->length++;
    return EXIT_SUCCESS;
}

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
int as_print(arr_stack_t *stack)
{
    if (!stack->length)
        return ERR_EMPTY_STACK;

    arr_stack_t tmp = { .length = 0 };
    while (stack->length)
    {
        char opt;
        int val;
        as_pop(stack, &opt, &val);
        as_push(&tmp, opt, val);
        printf("%c | %d\n", opt, val);
    }

    while (tmp.length)
    {
        char opt;
        int val;
        as_pop(&tmp, &opt, &val);
        as_push(stack, opt, val);
    }

    return EXIT_SUCCESS;
}
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
int stack_res(int arr[NUMS_COUNT])
{
    arr_stack_t *stack = malloc(sizeof(arr_stack_t));
    arr_stack_t *stack_opt = malloc(sizeof(arr_stack_t));

    if (stack == NULL || stack_opt == NULL)
        printf("Stack memory allocation error!\n");

    // 2 + (3 - (4 + (5 * 6)))
    // 2 3 4 5 6 * + - +
    // 6 5 4 3 2
    // * + - +
    char opt;
    int val;

    as_push(stack_opt, '*', 0);
    as_push(stack_opt, '+', 0);
    as_push(stack, ' ', arr[0]);
    as_push(stack, ' ', arr[1]);
    as_push(stack, ' ', arr[2]);
    as_push(stack, ' ', arr[3]);
    as_push(stack, ' ', arr[4]);
    as_push(stack, ' ', arr[5]);

    while (stack_opt->length)
    {
        as_pop(stack_opt, &opt, &val);
        char a_opt, b_opt;
        int a_val, b_val;
        as_pop(stack, &a_opt, &a_val);
        as_pop(stack, &b_opt, &b_val);

        if (opt == '+')
            as_push(stack, ' ', a_val + b_val);
        else if (opt == '-')
            as_push(stack, ' ', b_val - a_val);
        else if (opt == '*')
            as_push(stack, ' ', a_val * b_val);
    }

    as_push(stack_opt, '+', 0);
    as_push(stack_opt, '-', 0);
    as_push(stack_opt, '-', 0);
    as_push(stack, ' ', arr[6]);
    as_push(stack, ' ', arr[7]);

    while (stack_opt->length)
    {
        as_pop(stack_opt, &opt, &val);
        char a_opt, b_opt;
        int a_val, b_val;
        as_pop(stack, &a_opt, &a_val);
        as_pop(stack, &b_opt, &b_val);

        if (opt == '+')
            as_push(stack, ' ', a_val + b_val);
        else if (opt == '-')
            as_push(stack, ' ', b_val - a_val);
        else if (opt == '*')
            as_push(stack, ' ', a_val * b_val);
    }

    as_push(stack_opt, '+', 0);
    as_push(stack_opt, '*', 0);
    as_push(stack_opt, '+', 0);
    as_push(stack, ' ', arr[8]);

    while (stack_opt->length)
    {
        as_pop(stack_opt, &opt, &val);
        char a_opt, b_opt;
        int a_val, b_val;
        as_pop(stack, &a_opt, &a_val);
        as_pop(stack, &b_opt, &b_val);

        if (opt == '+')
            as_push(stack, ' ', a_val + b_val);
        else if (opt == '-')
            as_push(stack, ' ', b_val - a_val);
        else if (opt == '*')
            as_push(stack, ' ', a_val * b_val);
    }

    as_pop(stack, &opt, &val);

    return val;
}

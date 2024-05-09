#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>

#include "stack_IO.h"
#include "memory_operations.h"
#include "read.h"
#include "print.h"
#include "timer.h"

/**
 * @brief Code indicating successful operation.
 */
#define OK 0

/**
 * @brief Code indicating an empty stack.
 */
#define STACK_EMPTY 7

/**
 * @brief User action code to add elements to the stack.
 */
#define ADD 1

/**
 * @brief User action code to delete elements from the stack.
 */
#define DELETE 2

/**
 * @brief User action code to add random elements to the stack.
 */
#define RANDOM 3

/**
 * @brief User action code to print the current stack state.
 */
#define PRINT 4

/**
 * @brief Global variable to store the type of stack (array or list).
 */
extern int __stack_type;

/**
 * @brief Adds random elements to the stack and measures the time.
 *
 * @param array Pointer to the array stack structure.
 * @param list Pointer to the list stack structure.
 * @param count Number of elements to add.
 * @param array_time Pointer to accumulate the array stack processing time.
 * @param list_time Pointer to accumulate the list stack processing time.
 * @return int Returns OK if successful, otherwise an error code.
 */
static int random_filling(stack_array_t *array, stack_list_t *list, int count,
    int64_t *array_time, int64_t *list_time)
{
    int64_t start_time;
    int rand_i;

    for (int i = 0; i < 10000; i++)
    {
        printf("You can input  %d  more element(s).\n", 10000 - i);
        if (read_struct(&rand_i))
        {
            return 1;
        }

        if (rand_i == -1)
        {
            return OK;
        }

        __stack_type = 0;

        start_time = tick();
        push(array, list, rand_i, 0, 0);
        *list_time += tick() - start_time;

        __stack_type = 1;

        start_time = tick();
        push(array, list, rand_i, 0, 0);
        *array_time += tick() - start_time;
    }

    return OK;
}
/**
 * @brief Adds elements to the stack based on user input.
 *
 * @param array Pointer to the array stack structure.
 * @param list Pointer to the list stack structure.
 * @return int Returns OK if successful, otherwise an error code.
 */
static int add_to_stack(stack_array_t *array, stack_list_t *list)
{
    int count = 0;
    int64_t array_time = 0, list_time = 0;

    if (random_filling(array, list, count, &array_time, &list_time))
    {
        fprintf(stderr, "Incorrect Input.\n");
        return 1;
    }

    print_results(array_time, list_time);
    print_memory_results(array->size);

    return OK;
}
/**
 * @brief Deletes elements from the stack based on user input.
 *
 * @param array Pointer to the array stack structure.
 * @param list Pointer to the list stack structure.
 * @return int Returns OK if successful, otherwise an error code.
 */
static void delete_elements(stack_array_t *array, stack_list_t *list, int count,
    int64_t *array_time, int64_t *list_time)
{
    int64_t start_time;

    for (int i = 0; i < count; i++)
    {
        __stack_type = 0;

        start_time = tick();
        pop(array, list);
        *list_time += tick() - start_time;

        __stack_type = 1;

        start_time = tick();
        pop(array, list);
        *array_time += tick() - start_time;
    }
}
/**
 * @brief Deletes a specified number of elements from the stack.
 *
 * @param array Pointer to the array stack structure.
 * @param list Pointer to the list stack structure.
 * @param count Number of elements to delete.
 * @param array_time Pointer to accumulate the array stack processing time.
 * @param list_time Pointer to accumulate the list stack processing time.
 */
static int delete_from_stack(stack_array_t *array, stack_list_t *list)
{
    int code_error, count;
    int64_t array_time = 0, list_time = 0;

    if ((code_error = read_delete_info(&count, array->size)))
    {
        if (code_error == STACK_EMPTY)
        {
            return OK;
        }

        return code_error;
    }

    delete_elements(array, list, count, &array_time, &list_time);
    print_results(array_time, list_time);
    print_memory_results(array->size);

    return OK;
}
/**
 * @brief Prints the current state of the stack.
 *
 * @param array Pointer to the array stack structure.
 * @param list Pointer to the list stack structure.
 */
static void __print_stack(stack_array_t *array, stack_list_t *list)
{
    int64_t array_time = 0, list_time = 0;

    print_sample_stack(*list, *array, stdout, &array_time, &list_time);
    //print_results(array_time, list_time);
    print_memory_results(array->size);
}
/**
 * @brief Adds random elements to the stack and measures the time.
 *
 * @param array Pointer to the array stack structure.
 * @param list Pointer to the list stack structure.
 * @return int Returns OK if successful, otherwise an error code.
 */
static int go_random(stack_array_t *array, stack_list_t *list)
{
    srand(time(NULL));
    int64_t start_time, list_time = 0, array_time = 0;
    int rand_i, count = 0;

    if (read_add_info(&count, array->size))
    {
        return 1;
    }

    for (int i = 0; i < count; i++)
    {
        rand_i = rand() % 100;

        __stack_type = 0;

        start_time = tick();
        push(array, list, rand_i, 0, 0);
        list_time += tick() - start_time;

        __stack_type = 1;

        start_time = tick();
        push(array, list, rand_i, 0, 0);
        array_time += tick() - start_time;
    }

    print_results(array_time, list_time);
    print_memory_results(array->size);

    return OK;
}
/**
 * @brief Performs various stack operations based on user input.
 *
 * @param array Pointer to the array stack structure.
 * @param list Pointer to the list stack structure.
 * @return int Returns OK if successful, otherwise an error code.
 */
int stack_samples(stack_array_t *array, stack_list_t *list)
{
    int code_error, action;
    array->size =0;

    while (true)
    {
        if ((code_error = read_stack_action(&action)))
        {
            return code_error;
        }

        switch (action)
        {
            case ADD:

                if ((code_error = add_to_stack(array, list)))
                {
                    return code_error;
                }

                break;
            case DELETE:

                if ((code_error = delete_from_stack(array, list)))
                {
                    return code_error;
                }

                break;
            case RANDOM:

                if ((code_error = go_random(array, list)))
                {
                    return code_error;
                }

                break;
            case PRINT:
                __print_stack(array, list);
                break;
            default:
                free(array->ptr);
                free_list(list);
                exit(0);
        }
    }
}

#ifndef IO_H
#define IO_H

#include "app.h"
/**
 * @brief Prints the main menu for queue handling.
 */
void print_hello();

void printf_input();
/**
 * @brief Clears the input buffer.
 */
void clean_my();
/**
 * @brief Checks and retrieves a floating-point number from the user.
 *
 * @param number Pointer to the variable where the number will be stored.
 * @return int Status code: OK if successful, DONT_INT_NUM_CHOICE if input is not a valid number.
 */
int check_float(double *const number);
/**
 * @brief Checks and retrieves an integer number within a specified range from the user.
 *
 * @param number Pointer to the variable where the number will be stored.
 * @param l Lower bound of the valid range.
 * @param r Upper bound of the valid range.
 * @return int Status code: OK if successful, INV_NUM_CHOICE if input is not a valid number within the range.
 */
int check_number(int *const number, const int l, const int r);
/**
 * @brief Prints the current and average length of a queue.
 *
 * @param queue Pointer to the queue structure.
 */
void len_swow(queue_r *queue);

#endif // IO_H

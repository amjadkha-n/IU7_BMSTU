#include <stdio.h>
#include "../inc/check_key.h"
#include "../inc/check_mysort.h"
/**
 * @file
 * @brief This file contains the main function for checking key and mysort functions.
 */

/**
 * @brief The main function of the program.
 *
 * This function serves as the entry point for the program. It calls the functions
 * `check_key()` and `check_mysort()` to perform checks and accumulate error codes.
 * The total error amount is printed to the standard output.
 *
 * @return Returns the total error amount, which indicates the number of errors encountered.
 */
int main(void)
{
    int error_amount = 0;
    error_amount += check_key();
    error_amount += check_mysort();
    printf("Error amount = %d", error_amount);
    return error_amount;
}

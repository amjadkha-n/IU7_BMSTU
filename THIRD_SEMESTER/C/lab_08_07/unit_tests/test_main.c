#include "../inc/test_operations.h"

/**
 * @brief Main function to execute matrix operation tests.
 *
 * This is the entry point for the program, where a series of matrix operation tests is executed by calling the
 * `test_operations` function. The total number of errors encountered during the tests is returned as the program's exit code.
 *
 * @return The total number of errors encountered during matrix operation tests.
 */
int main(void)
{
    int amount_error = 0;
    amount_error += test_operations();
    return amount_error;
}
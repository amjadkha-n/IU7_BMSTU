#ifndef CHECK_MAIN_H
#define CHECK_MAIN_H

#include <check.h>
#include <assert.h>
#include "my_snprintf.h"

/**
 * @brief Constant indicating mismatch of character arrays.
 *
 * ARRAYS_MISMATCH is used as a return code for the compare_char_arrays function
 * to indicate that two character arrays do not match.
 */
#define ARRAYS_MISMATCH 1

/**
 * @brief Compares two character arrays and checks for equality.
 *
 * This function compares two character arrays of the given size and returns ARRAYS_MISMATCH
 * if they do not match; otherwise, it returns OK.
 *
 * @param first_arr The first character array.
 * @param second_arr The second character array.
 * @param size The size of the arrays to compare.
 * @return Returns ARRAYS_MISMATCH if arrays do not match, OK otherwise.
 */
int compare_char_arrays(char *first_arr, char *second_arr, int size);
/**
 * @brief Creates a test suite for the my_snprintf function.
 *
 * This function adds individual test cases to a suite and returns the suite.
 *
 * @param s The initial suite to which test cases are added.
 * @return Returns the suite with added test cases.
 */
Suite *my_snprintf_suite(Suite *s);

#endif

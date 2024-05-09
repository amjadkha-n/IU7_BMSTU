/// \file
/// \brief Header file for unit tests
#ifndef CHECK_MY_ARRAY_H
#define CHECK_MY_ARRAY_H

#include <check.h>

/**
 * @file check_my_array.h
 * @brief Header file for defining test suites related to associative array functionality.
 */

/**
 * @brief Creates a test suite for the associative array insertion functionality.
 * @return A test suite for insertion functionality.
 */
Suite *assoc_array_insert_suite(void);

/**
 * @brief Creates a test suite for the associative array find functionality.
 * @return A test suite for find functionality.
 */
Suite *assoc_array_find_suite(void);

/**
 * @brief Creates a test suite for the associative array removal functionality.
 * @return A test suite for removal functionality.
 */
Suite *assoc_array_remove_suite(void);

/**
 * @brief Creates a test suite for the associative array minimum value functionality.
 * @return A test suite for minimum value functionality.
 */
Suite *assoc_array_min_suite(void);

/**
 * @brief Creates a test suite for the associative array maximum value functionality.
 * @return A test suite for maximum value functionality.
 */
Suite *assoc_array_max_suite(void);

/**
 * @brief Creates a test suite for the associative array clearing functionality.
 * @return A test suite for clearing functionality.
 */
Suite *assoc_array_clear_suite(void);

/**
 * @brief Creates a test suite for the associative array iteration functionality.
 * @return A test suite for iteration functionality.
 */
Suite *assoc_array_each_suite(void);

#endif

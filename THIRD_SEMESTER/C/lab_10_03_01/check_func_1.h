/// \file
/// \brief Header file for unit tests

#ifndef CHECK_MY_ARRAY_H
#define CHECK_MY_ARRAY_H

#include <check.h>

/**
 * @brief Creates a test suite for assoc_array_insert function.
 *
 * @return A pointer to the test suite.
 */
Suite *assoc_array_insert_suite(void);

/**
 * @brief Creates a test suite for assoc_array_find function.
 *
 * @return A pointer to the test suite.
 */
Suite *assoc_array_find_suite(void);

/**
 * @brief Creates a test suite for assoc_array_remove function.
 *
 * @return A pointer to the test suite.
 */
Suite *assoc_array_remove_suite(void);

/**
 * @brief Creates a test suite for assoc_array_min function.
 *
 * @return A pointer to the test suite.
 */
Suite *assoc_array_min_suite(void);

/**
 * @brief Creates a test suite for assoc_array_max function.
 *
 * @return A pointer to the test suite.
 */
Suite *assoc_array_max_suite(void);

/**
 * @brief Creates a test suite for assoc_array_clear function.
 *
 * @return A pointer to the test suite.
 */
Suite *assoc_array_clear_suite(void);

/**
 * @brief Creates a test suite for assoc_array_each function.
 *
 * @return A pointer to the test suite.
 */
Suite *assoc_array_each_suite(void);

#endif // CHECK_MY_ARRAY_H

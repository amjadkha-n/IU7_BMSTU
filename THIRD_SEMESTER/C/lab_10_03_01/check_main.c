/// \file
/// \brief Main file for unit tests
#include <check.h>
#include <stdio.h>
#include "check_func_1.h"

#include <stdio.h>
#include <check.h>
/**
 * @brief Runs a test suite and prints the results.
 *
 * @param s A pointer to the test suite to be executed.
 * @return The number of test errors.
 */
int run_test_suite(Suite *s)
{
    SRunner *runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    int errors = srunner_ntests_failed(runner);
    srunner_free(runner);
    printf("\n");
    return errors;
}
/**
 * @brief The main function for running unit tests.
 *
 * @return The overall number of test errors.
 */
int main(void)
{
    int errors = 0;

    errors += run_test_suite(assoc_array_insert_suite());
    errors += run_test_suite(assoc_array_find_suite());
    errors += run_test_suite(assoc_array_remove_suite());
    errors += run_test_suite(assoc_array_min_suite());
    errors += run_test_suite(assoc_array_max_suite());

    return errors;
}



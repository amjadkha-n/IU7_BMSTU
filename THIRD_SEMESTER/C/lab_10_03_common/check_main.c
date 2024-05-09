/// \file
/// \brief
#include <check.h>
#include <stdio.h>
#include "check_func_1.h"

/**
 * @brief The main function for running the test suites.
 * @return The number of errors encountered during the test execution.
 */
int main(void)
{
    int errors = 0;

    Suite *s;
    SRunner *runner;

    // Run test suite for associative array insertion functionality
    s = assoc_array_insert_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    errors += srunner_ntests_failed(runner);
    srunner_free(runner);
    printf("\n");

    // Run test suite for associative array find functionality
    s = assoc_array_find_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    errors += srunner_ntests_failed(runner);
    srunner_free(runner);
    printf("\n");

    // Run test suite for associative array removal functionality
    s = assoc_array_remove_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    errors += srunner_ntests_failed(runner);
    srunner_free(runner);
    printf("\n");

    // Run test suite for associative array minimum value functionality
    s = assoc_array_min_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    errors += srunner_ntests_failed(runner);
    srunner_free(runner);
    printf("\n");

    // Run test suite for associative array maximum value functionality
    s = assoc_array_max_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    errors += srunner_ntests_failed(runner);
    srunner_free(runner);
    printf("\n");

    return errors;
}

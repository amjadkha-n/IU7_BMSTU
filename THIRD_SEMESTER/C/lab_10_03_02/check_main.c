/// \file
/// \brief Main file for unit tests
#include <check.h>
#include <stdio.h>
#include "check_func_1.h"

int main(void)
{
    int errors = 0;

    Suite *s;
    SRunner *runner;

    s = assoc_array_insert_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    errors += srunner_ntests_failed(runner);
    srunner_free(runner);
    printf("\n");

    s = assoc_array_find_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    errors += srunner_ntests_failed(runner);
    srunner_free(runner);
    printf("\n");

    s = assoc_array_remove_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    errors += srunner_ntests_failed(runner);
    srunner_free(runner);
    printf("\n");

    s = assoc_array_min_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    errors += srunner_ntests_failed(runner);
    srunner_free(runner);
    printf("\n");

    s = assoc_array_max_suite();
    runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    errors += srunner_ntests_failed(runner);
    srunner_free(runner);
    printf("\n");

    return errors;
}



#ifndef CHECK_MAIN_H
#define CHECK_MAIN_H

#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "main.h"

int compare_list_to_array(node_t *head, int *array[], int size);

Suite *custom_sort_suite(Suite *suite);
Suite *create_pop_front_suite(Suite *unit_tests_suite);
Suite *create_reverse_suite(Suite *unit_tests_suite);
Suite *custom_sort_suite(Suite *suite);


#endif

#include "../inc/check_main.h"

START_TEST(test_list_sort)
{
    salary_t salary_data;

    salary_data.array = malloc(4 * sizeof(int));
    assert(salary_data.array);

    salary_data.size = 4;
    salary_data.array[0] = 5;
    salary_data.array[1] = 2;
    salary_data.array[2] = 6;
    salary_data.array[3] = 0;

    node_t *list_head = NULL;

    int result_code = fill_linked_list(&list_head, &salary_data);
    assert(result_code == OK);

    list_head = sort(list_head, comparator);

    int *pointers_array[] = {salary_data.array + 3, salary_data.array + 1, salary_data.array, salary_data.array + 2};

    result_code = compare_list_to_array(list_head, pointers_array, salary_data.size);

    free_list(list_head);
    free(salary_data.array);

    ck_assert_int_eq(result_code, OK);
}
END_TEST


START_TEST(test_sorted_list)
{
    salary_t salary_data;

    salary_data.array = malloc(4 * sizeof(int));
    assert(salary_data.array);

    salary_data.size = 4;
    salary_data.array[0] = 0;
    salary_data.array[1] = 2;
    salary_data.array[2] = 5;
    salary_data.array[3] = 6;

    node_t *list_head = NULL;

    int result_code = fill_linked_list(&list_head, &salary_data);
    assert(result_code == OK);

    list_head = sort(list_head, comparator);

    int *pointers_array[] = {salary_data.array, salary_data.array + 1, salary_data.array + 2, salary_data.array + 3};

    result_code = compare_list_to_array(list_head, pointers_array, salary_data.size);

    free_list(list_head);
    free(salary_data.array);

    ck_assert_int_eq(result_code, OK);
}
END_TEST


START_TEST(test_one_elem_in_list)
{
    salary_t salary_data;

    salary_data.array = malloc(1 * sizeof(int));
    assert(salary_data.array);

    salary_data.size = 1;
    salary_data.array[0] = 5;

    node_t *list_head = NULL;

    int result_code = fill_linked_list(&list_head, &salary_data);
    assert(result_code == OK);

    list_head = sort(list_head, comparator);

    int *pointers_array[] = {salary_data.array};

    result_code = compare_list_to_array(list_head, pointers_array, salary_data.size);

    free_list(list_head);
    free(salary_data.array);

    ck_assert_int_eq(result_code, OK);
}
END_TEST


Suite *custom_sort_suite(Suite *suite)
{
    TCase *positive_tests;

    positive_tests = tcase_create("positive_tests");

    tcase_add_test(positive_tests, test_list_sort);
    tcase_add_test(positive_tests, test_sorted_list);
    tcase_add_test(positive_tests, test_one_elem_in_list);

    suite_add_tcase(suite, positive_tests);

    return suite;
}

#include "../inc/check_main.h"

START_TEST(test_pop_front)
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

    void *original_data = list_head->data, *removed_data;

    removed_data = remove_first_node(&list_head);
    assert(removed_data == original_data);

    int *pointers_array[] = {salary_data.array + 1, salary_data.array + 2, salary_data.array + 3};

    result_code = compare_list_to_array(list_head, pointers_array, salary_data.size - 1);

    free_list(list_head);
    free(salary_data.array);

    ck_assert_int_eq(result_code, OK);
}
END_TEST


Suite *create_pop_front_suite(Suite *unit_tests_suite)
{
    TCase *positive_tests_case;

    positive_tests_case = tcase_create("positive_cases");

    tcase_add_test(positive_tests_case, test_pop_front);

    suite_add_tcase(unit_tests_suite, positive_tests_case);

    return unit_tests_suite;
}

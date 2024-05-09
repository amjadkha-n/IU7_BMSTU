#include "check_func_1.h"
#include "associative_array.h"
#include <stdio.h>

/**
 * @brief Test case for adding an element with an empty key.
 */
START_TEST(add_element_with_empty_key)
{
    int result_code;
    assoc_array_t array = assoc_array_create();

    // Attempt to insert an element with an empty key
    result_code = assoc_array_insert(array, "", 1);

    // Check that the result code is ASSOC_ARRAY_INVALID_PARAM
    ck_assert_int_eq(result_code, ASSOC_ARRAY_INVALID_PARAM);

    // Clean up: Destroy the associative array
    assoc_array_destroy(&array);
}

/**
 * @brief Test case for adding the first element.
 */
START_TEST(add_first)
{
    int result_code;
    int *found_value = NULL;
    assoc_array_t array = assoc_array_create();

    result_code = assoc_array_insert(array, "a", 1);

    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);

    result_code = assoc_array_find(array, "a", &found_value);

    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);

    ck_assert_int_eq(*found_value, 1);

    assoc_array_destroy(&array);
}

/**
 * @brief Test case for adding two elements.
 */
START_TEST(add_two_elements)
{
    int result_code;
    int *value;
    assoc_array_t arr = assoc_array_create();

    result_code = assoc_array_insert(arr, "a", 1);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);

    result_code = assoc_array_insert(arr, "b", 2);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);

    result_code = assoc_array_find(arr, "a", &value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 1);

    result_code = assoc_array_find(arr, "b", &value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 2);

    assoc_array_destroy(&arr);
}

/**
 * @brief Test suite for insertion into an associative array.
 *
 * This suite contains positive and negative test cases for insertion.
 */
Suite* assoc_array_insert_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("insert");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, add_first);
    tcase_add_test(tc_pos, add_two_elements);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, add_element_with_empty_key);
    suite_add_tcase(s, tc_neg);

    return s;
}

/**
 * @brief Test case for searching an array with one element.
 */
START_TEST(search_array_with_one_element)
{
    int *result_value;
    int result_code;
    assoc_array_t array = assoc_array_create();

    assoc_array_insert(array, "x", 42);

    result_code = assoc_array_find(array, "x", &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);

    ck_assert_int_eq(*result_value, 42);
    assoc_array_destroy(&array);
}

/**
 * @brief Test case for finding elements in an array with two elements.
 */
START_TEST(find_in_arr_with_two_elem)
{
    int *result_value;
    int result_code;
    assoc_array_t array = assoc_array_create();

    assoc_array_insert(array, "x", 42);
    assoc_array_insert(array, "y", 99);

    result_code = assoc_array_find(array, "x", &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*result_value, 42);

    result_code = assoc_array_find(array, "y", &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*result_value, 99);

    assoc_array_destroy(&array);
}

/**
 * @brief Test case for finding a necessary element in an array.
 */
START_TEST(find_necessary_elem)
{
    int *result_value;
    int result_code;
    assoc_array_t array = assoc_array_create();

    assoc_array_insert(array, "x", 42);
    assoc_array_insert(array, "y", 99);

    result_code = assoc_array_find(array, "z", &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}

/**
 * @brief Test suite for finding elements in an associative array.
 *
 * This suite contains positive and negative test cases for finding elements.
 */
Suite* assoc_array_find_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("find");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, search_array_with_one_element);
    tcase_add_test(tc_pos, find_in_arr_with_two_elem);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, find_necessary_elem);
    suite_add_tcase(s, tc_neg);

    return s;
}

/**
 * @brief Test case for removing an array with one element.
 */
START_TEST(remove_array_with_one_element)
{
    int *result_value;
    int result_code;
    assoc_array_t array = assoc_array_create();

    assoc_array_insert(array, "x", 42);

    result_code = assoc_array_remove(array, "x");
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);

    result_code = assoc_array_find(array, "x", &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}

/**
 * @brief Test case for removing an element in an array with two elements.
 */
START_TEST(remove_in_arr_with_two_elem)
{
    int *result_value;
    int result_code;
    assoc_array_t array = assoc_array_create();

    assoc_array_insert(array, "x", 42);
    assoc_array_insert(array, "y", 99);

    result_code = assoc_array_remove(array, "x");
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);

    result_code = assoc_array_find(array, "x", &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_NOT_FOUND);

    result_code = assoc_array_find(array, "y", &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);

    assoc_array_destroy(&array);
}

/**
 * @brief Test case for removing a necessary element from an array.
 */
START_TEST(remove_necessary_elem)
{
    int result_code;
    assoc_array_t array = assoc_array_create();

    assoc_array_insert(array, "x", 42);
    assoc_array_insert(array, "y", 99);

    result_code = assoc_array_remove(array, "z");
    ck_assert_int_eq(result_code, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&array);
}

/**
 * @brief Test suite for removing elements from an associative array.
 *
 * This suite contains positive and negative test cases for removing elements.
 */
Suite* assoc_array_remove_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("remove");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, remove_array_with_one_element);
    tcase_add_test(tc_pos, remove_in_arr_with_two_elem);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, remove_necessary_elem);
    suite_add_tcase(s, tc_neg);

    return s;
}

/**
 * @brief Test case for finding the minimum element in an array with one element.
 */
START_TEST(min_in_arr_with_one_elem)
{
    int *result_value;
    int result_code;
    assoc_array_t array = assoc_array_create();

    assoc_array_insert(array, "x", 42);

    result_code = assoc_array_min(array, &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*result_value, 42);

    assoc_array_destroy(&array);
}

/**
 * @brief Test case for finding the minimum element in an array with elements in the right order.
 */
START_TEST(min_in_arr_with_elem_in_right_order)
{
    int *result_value;
    int result_code;
    assoc_array_t array = assoc_array_create();

    assoc_array_insert(array, "a", 1);
    assoc_array_insert(array, "aa", 2);
    assoc_array_insert(array, "aaa", 3);

    result_code = assoc_array_min(array, &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*result_value, 1);

    assoc_array_destroy(&array);
}

/**
 * @brief Test case for finding the minimum element in an array with elements in reverse order.
 */
START_TEST(min_in_arr_with_elem_in_revers_order)
{
    int *result_value;
    int result_code;
    assoc_array_t array = assoc_array_create();

    assoc_array_insert(array, "aaa", 3);
    assoc_array_insert(array, "aa", 2);
    assoc_array_insert(array, "a", 1);

    result_code = assoc_array_min(array, &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*result_value, 1);

    assoc_array_destroy(&array);
}

/**
 * @brief Test suite for finding the minimum element in an associative array.
 *
 * This suite contains positive test cases for finding the minimum element.
 */
Suite* assoc_array_min_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("min");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, min_in_arr_with_one_elem);
    tcase_add_test(tc_pos, min_in_arr_with_elem_in_right_order);
    tcase_add_test(tc_pos, min_in_arr_with_elem_in_revers_order);
    suite_add_tcase(s, tc_pos);

    return s;
}

/**
 * @brief Test case for finding the maximum value in an associative array with one element.
 */
START_TEST(max_in_arr_with_one_elem)
{
    int *result_value;
    int result_code;
    assoc_array_t array = assoc_array_create();

    assoc_array_insert(array, "x", 42);

    result_code = assoc_array_max(array, &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*result_value, 42);

    assoc_array_destroy(&array);
}
/**
 * @brief Test case for finding the maximum value in an associative array with elements in ascending order.
 */
START_TEST(max_in_arr_with_elem_in_right_order)
{
    int *result_value;
    int result_code;
    assoc_array_t array = assoc_array_create();

    assoc_array_insert(array, "a", 1);
    assoc_array_insert(array, "aa", 2);
    assoc_array_insert(array, "aaa", 3);

    result_code = assoc_array_max(array, &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*result_value, 3);

    assoc_array_destroy(&array);
}
/**
 * @brief Test case for finding the maximum value in an associative array with elements in descending order.
 */
START_TEST(max_in_arr_with_elem_in_revers_order)
{
    int *result_value;
    int result_code;
    assoc_array_t array = assoc_array_create();

    assoc_array_insert(array, "aaa", 3);
    assoc_array_insert(array, "aa", 2);
    assoc_array_insert(array, "a", 1);

    result_code = assoc_array_max(array, &result_value);
    ck_assert_int_eq(result_code, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*result_value, 3);

    assoc_array_destroy(&array);
}
/**
 * @brief Create a test suite for maximum value operations in an associative array.
 *
 * @return Pointer to the test suite.
 */
Suite* assoc_array_max_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("max");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, max_in_arr_with_one_elem);
    tcase_add_test(tc_pos, max_in_arr_with_elem_in_right_order);
    tcase_add_test(tc_pos, max_in_arr_with_elem_in_revers_order);
    suite_add_tcase(s, tc_pos);

    return s;
}

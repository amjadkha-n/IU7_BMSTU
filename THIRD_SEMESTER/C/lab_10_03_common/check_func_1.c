#include "check_func_1.h"
#include "associative_array.h"
#include <stdio.h>
/**
 * @brief Test case for inserting an element with an empty key.
 */
START_TEST(insert_elem_with_empty_key)
{
    int rc;
    assoc_array_t arr = assoc_array_create();
    rc = assoc_array_insert(arr, "", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_INVALID_PARAM);
    assoc_array_destroy(&arr);
}

/**
 * @brief Test case for inserting the first element into the associative array.
 */
START_TEST(insert_first)
{
    int rc;
    int *value = NULL;
    assoc_array_t arr = assoc_array_create();
    rc = assoc_array_insert(arr, "a", 1);

    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(arr, "a", &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    ck_assert_int_eq(*value, 1);
    assoc_array_destroy(&arr);
}

/**
 * @brief Test case for inserting two elements into the associative array.
 */
START_TEST(insert_two_elem)
{
    int rc;
    int *value;
    assoc_array_t arr = assoc_array_create();
    rc = assoc_array_insert(arr, "a", 1);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    rc = assoc_array_insert(arr, "b", 2);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(arr, "a", &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 1);

    rc = assoc_array_find(arr, "b", &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 2);
    assoc_array_destroy(&arr);
}

/**
 * @brief Creates a test suite for the insertion functionality of the associative array.
 * @return A test suite for the insertion functionality.
 */
Suite* assoc_array_insert_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("insert");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, insert_first);
    tcase_add_test(tc_pos, insert_two_elem);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, insert_elem_with_empty_key);
    suite_add_tcase(s, tc_neg);

    return s;
}

/**
 * @brief Test case for finding an element in the associative array with one element.
 */
START_TEST(find_in_arr_with_one_elem)
{
    int *value;
    int rc;
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "a", 1);

    rc = assoc_array_find(arr, "a", &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    ck_assert_int_eq(*value, 1);
    assoc_array_destroy(&arr);
}

/**
 * @brief Test case for finding elements in the associative array with two elements.
 */
START_TEST(find_in_arr_with_two_elem)
{
    int *value;
    int rc;
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "a", 1);
    assoc_array_insert(arr, "b", 2);

    rc = assoc_array_find(arr, "a", &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 1);

    rc = assoc_array_find(arr, "b", &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 2);

    assoc_array_destroy(&arr);
}

/**
 * @brief Test case for finding a necessary element that does not exist in the associative array.
 */
START_TEST(find_necessary_elem)
{
    int *value;
    int rc;
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "a", 1);
    assoc_array_insert(arr, "b", 2);

    rc = assoc_array_find(arr, "c", &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);
    assoc_array_destroy(&arr);
}

/**
 * @brief Creates a test suite for the find functionality of the associative array.
 * @return A test suite for the find functionality.
 */
Suite* assoc_array_find_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("find");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, find_in_arr_with_one_elem);
    tcase_add_test(tc_pos, find_in_arr_with_two_elem);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, find_necessary_elem);
    suite_add_tcase(s, tc_neg);

    return s;
}

/**
 * @brief Test case for removing an element from the associative array with one element.
 */
START_TEST(remove_in_arr_with_one_elem)
{
    int *value;
    int rc;
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "a", 1);

    rc = assoc_array_remove(arr, "a");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(arr, "a", &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}

/**
 * @brief Test case for removing an element from the associative array with two elements.
 */
START_TEST(remove_in_arr_with_two_elem)
{
    int *value;
    int rc;
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "a", 1);
    assoc_array_insert(arr, "b", 2);

    rc = assoc_array_remove(arr, "a");
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    rc = assoc_array_find(arr, "a", &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    rc = assoc_array_find(arr, "b", &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);

    assoc_array_destroy(&arr);
}

/**
 * @brief Test case for attempting to remove a necessary element that does not exist in the associative array.
 */
START_TEST(remove_necessary_elem)
{
    int rc;
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "a", 1);
    assoc_array_insert(arr, "b", 2);

    rc = assoc_array_remove(arr, "z");
    ck_assert_int_eq(rc, ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}

/**
 * @brief Creates a test suite for the removal functionality of the associative array.
 * @return A test suite for the removal functionality.
 */
Suite* assoc_array_remove_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("remove");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, remove_in_arr_with_one_elem);
    tcase_add_test(tc_pos, remove_in_arr_with_two_elem);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, remove_necessary_elem);
    suite_add_tcase(s, tc_neg);

    return s;
}

/**
 * @brief Test case for finding the minimum value in the associative array with one element.
 */
START_TEST(min_in_arr_with_one_elem)
{
    int *value;
    int rc;
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "a", 1);

    rc = assoc_array_min(arr, &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 1);

    assoc_array_destroy(&arr);
}

/**
 * @brief Test case for finding the minimum value in the associative array with elements in ascending order.
 */
START_TEST(min_in_arr_with_elem_in_right_order)
{
    int *value;
    int rc;
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "a", 1);
    assoc_array_insert(arr, "aa", 2);
    assoc_array_insert(arr, "aaa", 3);

    rc = assoc_array_min(arr, &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 1);

    assoc_array_destroy(&arr);
}

/**
 * @brief Test case for finding the minimum value in the associative array with elements in descending order.
 */
START_TEST(min_in_arr_with_elem_in_revers_order)
{
    int *value;
    int rc;
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "aaa", 3);
    assoc_array_insert(arr, "aa", 2);
    assoc_array_insert(arr, "a", 1);

    rc = assoc_array_min(arr, &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 1);

    assoc_array_destroy(&arr);
}

/**
 * @brief Creates a test suite for the minimum value functionality of the associative array.
 * @return A test suite for the minimum value functionality.
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
 * @brief Test case for finding the maximum value in the associative array with one element.
 */
START_TEST(max_in_arr_with_one_elem)
{
    int *value;
    int rc;
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "a", 1);

    rc = assoc_array_max(arr, &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 1);

    assoc_array_destroy(&arr);
}

/**
 * @brief Test case for finding the maximum value in the associative array with elements in ascending order.
 */
START_TEST(max_in_arr_with_elem_in_right_order)
{
    int *value;
    int rc;
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "a", 1);
    assoc_array_insert(arr, "aa", 2);
    assoc_array_insert(arr, "aaa", 3);

    rc = assoc_array_max(arr, &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 3);

    assoc_array_destroy(&arr);
}

/**
 * @brief Test case for finding the maximum value in the associative array with elements in descending order.
 */
START_TEST(max_in_arr_with_elem_in_revers_order)
{
    int *value;
    int rc;
    assoc_array_t arr = assoc_array_create();

    assoc_array_insert(arr, "aaa", 3);
    assoc_array_insert(arr, "aa", 2);
    assoc_array_insert(arr, "a", 1);

    rc = assoc_array_max(arr, &value);
    ck_assert_int_eq(rc, ASSOC_ARRAY_OK);
    ck_assert_int_eq(*value, 3);

    assoc_array_destroy(&arr);
}

/**
 * @brief Creates a test suite for the maximum value functionality of the associative array.
 * @return A test suite for the maximum value functionality.
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

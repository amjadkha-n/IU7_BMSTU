#include "../inc/check_main.h"

int compare_list_to_array(node_t *head, int *array, int size)
{   
    int i = 0;

    while (head && (size-- > 0))
    {
        if (head->power != array[i++])
            return DIFFERENT_ELEMENTS_ERROR;

        head = head->next;
    }

    return (size == 0 && head == NULL) ? OK : DIFFERENT_LISTS_ERROR;
}

START_TEST(norm_div)
{
    int array[] = {1};

    node_t *res_head = NULL;
    int r = 0;

    do {
        int first_numb = 9;
        node_t *first_head = NULL;
        r = fill_the_list(&first_head, first_numb);
        if (r) break;

        int second_numb = 4;
        node_t *second_head = NULL;
        r = fill_the_list(&second_head, second_numb);
        if (r) {
            free_linked_list(first_head);
            break;
        }

        r = division_of_two_numbers(first_head, second_head, &res_head);
        if (r) {
            free_linked_list(first_head);
            free_linked_list(second_head);
            break;
        }

        r = compare_list_to_array(res_head, array, 1);
    } while (0);

    free_linked_list(res_head);
    ck_assert_int_eq(r, OK);
}
END_TEST

START_TEST(unit_div)
{
    int *array = NULL;

    node_t *res_head = NULL;
    int r = 0;

    do {
        int first_numb = 9;
        node_t *first_head = NULL;
        r = fill_the_list(&first_head, first_numb);
        if (r) break;

        int second_numb = 9;
        node_t *second_head = NULL;
        r = fill_the_list(&second_head, second_numb);
        if (r) {
            free_linked_list(first_head);
            break;
        }

        r = division_of_two_numbers(first_head, second_head, &res_head);
        if (r) {
            free_linked_list(first_head);
            free_linked_list(second_head);
            break;
        }

        r = compare_list_to_array(res_head, array, 0);
    } while (0);

    free_linked_list(res_head);
    ck_assert_int_eq(r, OK);
}
END_TEST

START_TEST(zero_result)
{
    node_t *res_head = NULL;
    int r = 0;

    do {
        int first_numb = 4;
        node_t *first_head = NULL;
        r = fill_the_list(&first_head, first_numb);
        if (r) break;

        int second_numb = 9;
        node_t *second_head = NULL;
        r = fill_the_list(&second_head, second_numb);
        if (r) {
            free_linked_list(first_head);
            break;
        }

        r = division_of_two_numbers(first_head, second_head, &res_head);
    } while (0);

    free_linked_list(res_head);
    ck_assert_int_eq(r, EMPTY_LIST_ERROR);
}
END_TEST

Suite *div_suite(Suite *s)
{
    TCase *tcase_pos, *tcase_neg;

    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, norm_div);
    tcase_add_test(tcase_pos, unit_div);

    suite_add_tcase(s, tcase_pos);
    
    tcase_neg = tcase_create("negative");

    tcase_add_test(tcase_pos, zero_result);

    suite_add_tcase(s, tcase_neg);
    
    return s;
}

START_TEST(norm_mul)
{
    int first_numb = 3;

    node_t *first_head = NULL;

    int r = fill_the_list(&first_head, first_numb);
    assert(!r);

    int second_numb = 25;

    node_t *second_head = NULL;

    r = fill_the_list(&second_head, second_numb);
    assert(!r);

    node_t *res_head = multiply_numbers(first_head, second_head);

    int array[] = {0, 1, 2};

    r = compare_list_to_array(res_head, array, 3);

    free_linked_list(first_head);
    free_linked_list(second_head);

    ck_assert_int_eq(r, OK);
}
END_TEST

START_TEST(unit_mul)
{
    int first_numb = 7;

    node_t *first_head = NULL;

    int r = fill_the_list(&first_head, first_numb);
    assert(!r);

    int second_numb = 1;

    node_t *second_head = NULL;

    r = fill_the_list(&second_head, second_numb);
    assert(!r);

    node_t *res_head = multiply_numbers(first_head, second_head);

    int array[] = {0, 0, 0, 1};

    r = compare_list_to_array(res_head, array, 4);

    free_linked_list(first_head);
    free_linked_list(second_head);

    ck_assert_int_eq(r, OK);
}
END_TEST

Suite *mul_suite(Suite *s)
{
    TCase *tcase_pos;

    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, norm_mul);
    tcase_add_test(tcase_pos, unit_mul);

    suite_add_tcase(s, tcase_pos);
    
    return s;
}

START_TEST(norm_sqr)
{
    int number = 21;
    node_t *head = NULL;

    int r;
    if ((r = fill_the_list(&head, number)) == OK)
    {
        int array[] = {0, 2, 0, 2};

        square_the_number(head);

        r = compare_list_to_array(head, array, 4);

        free_linked_list(head);
    }

    ck_assert_int_eq(r, 7);
}
END_TEST

START_TEST(unit_sqr)
{
    int number = 1;
    node_t *head = NULL;

    int r;
    if ((r = fill_the_list(&head, number)) == OK)
    {
        int *array = NULL;

        square_the_number(head);

        r = compare_list_to_array(head, array, 0);

        free_linked_list(head);
    }

    ck_assert_int_eq(r, OK);
}
END_TEST

Suite *sqr_suite(Suite *s)
{
    TCase *tcase_pos = tcase_create("positives");

    do
    {
        tcase_add_test(tcase_pos, norm_sqr);
        tcase_add_test(tcase_pos, unit_sqr);

        suite_add_tcase(s, tcase_pos);
        
        return s;

    } while (0);
    
    return NULL;
}

Suite *tests_suite()
{
    return div_suite(sqr_suite(mul_suite(suite_create("tests"))));
}

int main(void)
{
    Suite *s = tests_suite();
    SRunner *runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    int mistakes = srunner_ntests_failed(runner);
    srunner_free(runner);
    return mistakes;
}

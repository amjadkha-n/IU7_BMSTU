#include "../inc/check_main.h"  

int compare_list_to_array(node_t *list_head, int *array[], int array_size)
{    
    int array_index = 0;

    while (list_head) {
        if (array_size > 0 && list_head->data != array[array_index++]) {
            return DIFFERENT_ELEMENTS;
        }

        list_head = list_head->next;
        array_size--;
    }

    if (array_size > 0) {
        return DIFFERENT_LISTS;
    }

    return OK;
}

Suite *create_tests_suite() {
    Suite *test_suite = suite_create("unit_tests");
    test_suite = custom_sort_suite(test_suite);
    test_suite = create_reverse_suite(test_suite);
    test_suite = create_pop_front_suite(test_suite);
    return test_suite;
}


int main(void)
{
     Suite *test_suite = create_tests_suite();
    SRunner *test_runner = srunner_create(test_suite);
    srunner_run_all(test_runner, CK_VERBOSE);
    int errors_count = srunner_ntests_failed(test_runner);
    srunner_free(test_runner);
    return errors_count;
}
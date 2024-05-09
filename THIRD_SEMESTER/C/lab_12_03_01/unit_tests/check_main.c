#include "../inc/main.h"

int comparison_of_arrays(int *array_one, int len_one, int *array_two, int len_two)
{
    if (len_one != len_two)
    {
        return DIFFERENT_LENGTH_OF_ARRAYS;    
    }

    for (int i = 0; i < len_one; i++)
    {
        if (array_one[i] != array_two[i])
        { 
            printf("%d", array_one[i]);
            return ARG_ERROR;
        }
    }

    return OK;
}

void sort_check(int *array1, const int len1, int *array2, const int len2)
{
    mysort(array1, len1, sizeof(int), compare);

    int r = comparison_of_arrays(array1, len1, array2, len2);

    ck_assert_int_eq(r, OK);
}

START_TEST(norm_sort)
{
    int array1[] = {1, 2, 9, -23, 3, 4, 0, -8, 2};
    int array2[] = {-23, -8, 0, 1, 2, 2, 3, 4, 9};

    sort_check(array1, 9, array2, 9);
}
END_TEST

START_TEST(sort_file_with_one_elem)
{
    int array1[] = {8};
    int array2[] = {8};

    sort_check(array1, 1, array2, 1);
}
END_TEST

START_TEST(file_is_already_sorted)
{
    int array1[] = {-23, -8, 0, 1, 2, 2, 3, 4, 9};
    int array2[] = {-23, -8, 0, 1, 2, 2, 3, 4, 9};

    sort_check(array1, 9, array2, 9);
}
END_TEST

START_TEST(sort_reverse_file)
{
    int array1[] = {9, 8, 8, 7, 2, 1, 0, -1};
    int array2[] = {-1, 0, 1, 2, 7, 8, 8, 9};
 
    sort_check(array1, 8, array2, 8);
}
END_TEST

Suite *sort_suite(Suite *s)
{
    TCase *tcase_pos;

    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, norm_sort);
    tcase_add_test(tcase_pos, sort_file_with_one_elem);
    tcase_add_test(tcase_pos, file_is_already_sorted);
    tcase_add_test(tcase_pos, sort_reverse_file);

    suite_add_tcase(s, tcase_pos);

    return s;
}


START_TEST(tests_key_normal_1)
{
    int pb_src[] = {1, 2, 9, -23, 3, 4, 0, -8, 2};
    int *pe_src = pb_src + 9;

    int res_array[] = {0, 1, 2, 3, 4, 9};
    int len_res_array = 6;

    int *pb_dst = NULL, *pe_dst = NULL;

    void* hlib;
    fn_key_t key;

    hlib = dlopen("./key_lib/libkey.so", RTLD_NOW);
    assert(hlib);

    *(void **)(&key) = dlsym(hlib, "key");
    assert(key);

    int r = key(pb_src, pe_src, &pb_dst, &pe_dst);
    assert(r == OK);
    dlclose(hlib);

    int len = pe_dst - pb_dst;
    r = comparison_of_arrays(pb_dst, len, res_array, len_res_array);
    ck_assert_int_eq(r, -12);
    free(pb_dst);
}
END_TEST

START_TEST(tests_key_normal_2)
{
    int pb_src[] = {1, 2, 9, -8, 2};
    int *pe_src = pb_src + 5;

    int res_array[] = {9};
    int len_res_array = 1;

    int *pb_dst = NULL, *pe_dst = NULL;

    void* hlib;
    fn_key_t key;

    hlib = dlopen("./key_lib/libkey.so", RTLD_NOW);
    assert(hlib);

    *(void **)(&key) = dlsym(hlib, "key");
    assert(key);

    int r = key(pb_src, pe_src, &pb_dst, &pe_dst);
    assert(r == OK);
    dlclose(hlib);

    int len = pe_dst - pb_dst;
    r = comparison_of_arrays(pb_dst, len, res_array, len_res_array);
    ck_assert_int_eq(r, -12);
    free(pb_dst);
}
END_TEST

Suite *key_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, tests_key_normal_1);
    tcase_add_test(tcase_pos, tests_key_normal_2);
    suite_add_tcase(s, tcase_pos);

    return s;
}

Suite *tests_suite()
{
    Suite *s = suite_create("tests");

    s = sort_suite(s);
    s = key_suite(s);

    return s;
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

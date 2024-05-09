#include <check.h>
#include "../inc/check_main.h"

START_TEST(test_read_struct_valid)
{
    product p;
    FILE *file = fopen("unit_tests/one_product.txt", "r");
    ck_assert_ptr_ne(file, NULL);

    int result = read_struct(file, &p);
    fclose(file);

    ck_assert_int_eq(result, OK);
    ck_assert_str_eq(p.name, "apple");
    ck_assert_int_eq(p.price, 80);
    free(p.name);
}
END_TEST

START_TEST(test_read_file_and_process_valid)
{
    product *products = NULL;
    int num_products = 0;
    FILE *file = fopen("unit_tests/input.txt", "r");
    ck_assert_ptr_ne(file, NULL);

    int result = read_file_and_process(file, &products, &num_products);
    fclose(file);

    ck_assert_int_eq(result, OK_NUM_PRODUCTS);
    ck_assert_int_eq(num_products, 3);
    ck_assert_str_eq(products[0].name, "apple");
    ck_assert_int_eq(products[0].price, 80);
    ck_assert_str_eq(products[1].name, "mango");
    ck_assert_int_eq(products[1].price, 140);
    free_products(products, num_products);
}
END_TEST

START_TEST(test_display_low_price_valid)
{
    product products[3];
    products[0].name = "apple";
    products[0].price = 80;
    products[1].name = "mango";
    products[1].price = 140;
    products[2].name = "orange";
    products[2].price = 30;

    int result = display_low_price(products, 3, 250);
    ck_assert_int_eq(result, OK);
}
END_TEST

Suite *my_func_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("My_mod");

    tc_core = tcase_create("Read_struct");
    tcase_add_test(tc_core, test_read_struct_valid);
    suite_add_tcase(s, tc_core);

    tc_core = tcase_create("Read_file_and_process");
    tcase_add_test(tc_core, test_read_file_and_process_valid);
    suite_add_tcase(s, tc_core);

    tc_core = tcase_create("Display_low_price");
    tcase_add_test(tc_core, test_display_low_price_valid);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = my_func_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
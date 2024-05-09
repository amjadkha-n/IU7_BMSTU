#include "../inc/check_main.h"

/**
 * @brief Test case for the '%hd' specifier.
 *
 * This test case checks the behavior of the my_snprintf function when formatting
 * a short integer using the '%hd' specifier and compares it with the standard
 * snprintf function.
 */
START_TEST(hd_specifier)
{
    char first_buffer[BUFFER_SIZE + 1];
    char second_buffer[BUFFER_SIZE + 1];

    short int number = 12345;

    int number_ch_one = my_snprintf(first_buffer, BUFFER_SIZE, "%hd", number);
    int number_ch_two = snprintf(second_buffer, BUFFER_SIZE, "%hd", number);

    assert(number_ch_one == number_ch_two);

    int r = compare_char_arrays(first_buffer, second_buffer, number_ch_one);

    ck_assert_int_eq(r, OK);
}
END_TEST

/**
 * @brief Test case for the '%c' specifier.
 *
 * This test case checks the behavior of the my_snprintf function when formatting
 * a character using the '%c' specifier and compares it with the standard
 * snprintf function.
 */
START_TEST(c_specifier)
{
    char first_buffer[BUFFER_SIZE + 1];
    char second_buffer[BUFFER_SIZE + 1];

    char ch = 'k';

    int number_ch_one = my_snprintf(first_buffer, BUFFER_SIZE, "%c", ch);
    int number_ch_two = snprintf(second_buffer, BUFFER_SIZE, "%c", ch);

    assert(number_ch_one == number_ch_two);

    int r = compare_char_arrays(first_buffer, second_buffer, number_ch_one);

    ck_assert_int_eq(r, OK);
}
END_TEST

/**
 * @brief Test case for the '%s' specifier.
 *
 * This test case checks the behavior of the my_snprintf function when formatting
 * a string using the '%s' specifier and compares it with the standard
 * snprintf function.
 */
START_TEST(s_specifier)
{
    char first_buffer[BUFFER_SIZE + 1];
    char second_buffer[BUFFER_SIZE + 1];

    char str[] = "check";

    int number_ch_one = my_snprintf(first_buffer, BUFFER_SIZE, "%s", str);
    int number_ch_two = snprintf(second_buffer, BUFFER_SIZE, "%s", str);

    assert(number_ch_one == number_ch_two);

    int r = compare_char_arrays(first_buffer, second_buffer, number_ch_one);

    ck_assert_int_eq(r, OK);
}
END_TEST

/**
 * @brief Test case with no format specifiers.
 *
 * This test case checks the behavior of the my_snprintf function when no
 * format specifiers are present, and compares it with the standard
 * snprintf function.
 */
START_TEST(no_specifiers)
{    
    char first_buffer[BUFFER_SIZE + 1];
    char second_buffer[BUFFER_SIZE + 1];

    int number_ch_one = my_snprintf(first_buffer, BUFFER_SIZE, "check");
    int number_ch_two = snprintf(second_buffer, BUFFER_SIZE, "check");

    assert(number_ch_one == number_ch_two);

    int r = compare_char_arrays(first_buffer, second_buffer, number_ch_one);

    ck_assert_int_eq(r, OK);
}
END_TEST

/**
 * @brief Creates a test suite for the my_snprintf function.
 *
 * This function adds individual test cases to a suite and returns the suite.
 *
 * @param s The initial suite to which test cases are added.
 * @return Returns the suite with added test cases.
 */
Suite *my_snprintf_suite(Suite *s)
{
    TCase *tcase_pos;

    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, hd_specifier);
    tcase_add_test(tcase_pos, c_specifier);
    tcase_add_test(tcase_pos, s_specifier);
    tcase_add_test(tcase_pos, no_specifiers);

    suite_add_tcase(s, tcase_pos);

    return s;
}

/**
 * @brief Compares two character arrays and checks for equality.
 *
 * This function compares two character arrays of the given size and returns OK
 * if they match, otherwise, it returns ARRAYS_MISMATCH.
 *
 * @param first_arr The first character array.
 * @param second_arr The second character array.
 * @param size The size of the arrays to compare.
 * @return Returns OK if arrays match, ARRAYS_MISMATCH otherwise.
 */
int compare_char_arrays(char *first_arr, char *second_arr, int size)
{
    int result = OK;

    for (int i = 0; i < size; i++)
    {
        if (first_arr[i] != second_arr[i])
        {
            result = ARRAYS_MISMATCH;
            break;
        }
    }

    return result;
}

/**
 * @brief Creates the main test suite containing all test cases.
 *
 * This function creates the main test suite and adds the suite for the
 * my_snprintf function. It returns the complete suite.
 *
 * @return Returns the main test suite.
 */
Suite *tests_suite()
{
    Suite *s = suite_create("tests");
    s = my_snprintf_suite(s);

    return s;
}
/**
 * @brief Main function to run the unit tests.
 *
 * This function creates the main test suite, runs all the tests, and
 * prints the results.
 *
 * @return Returns the number of failed tests.
 */
int main(void)
{
    Suite *s = tests_suite();
    SRunner *runner = srunner_create(s);
    srunner_run_all(runner, CK_VERBOSE);
    int mistakes = srunner_ntests_failed(runner);
    srunner_free(runner);
    return mistakes;
}

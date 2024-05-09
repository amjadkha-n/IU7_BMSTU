#include <check.h>
#include "../inc/process.h"
#include "../inc/film_in_out.h"
#include "../inc/check_binary_search.h"

START_TEST(test_search_title_begin)
{
    struct film *films = create_film_array(4);
    int ind;

    initialize_film(&films[0], "Gladiator", "Scott", 2000, 1, 1);
    initialize_film(&films[1], "Whispers in the Wind", "Anderson", 2005, 1, 1);
    initialize_film(&films[2], "Lost in the Echo", "Martinez", 2010, 1, 1);
    initialize_film(&films[3], "The dictator", "Charles", 2012, 1, 1);

    ind = binary_search_title("Gladiator", films, 4);

    release_film_array_memory(films, 4);

    ck_assert_int_eq(ind, 0);
}
END_TEST

START_TEST(test_search_title_end)
{
    struct film *films = create_film_array(4);
    int ind;

    initialize_film(&films[0], "Gladiator", "Scott", 2000, 1, 1);
    initialize_film(&films[1], "Whispers in the Wind", "Anderson", 2005, 1, 1);
    initialize_film(&films[2], "Lost in the Echo", "Martinez", 2010, 1, 1);
    initialize_film(&films[3], "The dictator", "Charles", 2012, 1, 1);

    ind = binary_search_title("The dictator", films, 4);

    release_film_array_memory(films, 4);

    ck_assert_int_eq(ind, -1);
}
END_TEST

START_TEST(test_search_title_mid)
{
    struct film *films = create_film_array(4);
    initialize_film(&films[0], "The Dark Knight", "Nolan", 2008, 1, 1);
    initialize_film(&films[1], "Inception", "Nolan", 2010, 1, 1);
    initialize_film(&films[2], "Interstellar", "Nolan", 2014, 1, 1);
    initialize_film(&films[3], "Dunkirk", "Nolan", 2017, 1, 1);

    int ind = binary_search_title("Interstellar", films, 4);

    ck_assert_int_eq(ind, 2);

    release_film_array_memory(films, 4);
}
END_TEST

START_TEST(test_search_title_neg)
{
    struct film *films = create_film_array(4);
    initialize_film(&films[0], "The Dark Knight", "Nolan", 2008, 1, 1);
    initialize_film(&films[1], "Inception", "Nolan", 2010, 1, 1);
    initialize_film(&films[2], "Interstellar", "Nolan", 2014, 1, 1);
    initialize_film(&films[3], "Dunkirk", "Nolan", 2017, 1, 1);

    int ind = binary_search_title("Memento", films, 4);

    ck_assert_int_eq(ind, -1);

    release_film_array_memory(films, 4);
}
END_TEST

// Тесты функции binary_search_name
START_TEST(test_search_name_begin)
{
    struct film *films = create_film_array(4);
    initialize_film(&films[0], "Nolan's Film 1", "Nolan", 2000, 1, 1);
    initialize_film(&films[1], "Smith's Movie", "Smith", 1995, 1, 1);
    initialize_film(&films[2], "Johnson's Flick", "Johnson", 2010, 1, 1);
    initialize_film(&films[3], "Rob's Feature", "Rob", 2006, 1, 1);

    int ind = binary_search_name("Nolan", films, 4);

    ck_assert_int_eq(ind, 0);

    release_film_array_memory(films, 4);
}
END_TEST


START_TEST(test_search_name_end)
{
    struct film *films = create_film_array(4);
    initialize_film(&films[0], "Nolan's Film 1", "Nolan", 2000, 1, 1);
    initialize_film(&films[1], "Smith's Movie", "Smith", 1995, 1, 1);
    initialize_film(&films[2], "Johnson's Flick", "Johnson", 2010, 1, 1);
    initialize_film(&films[3], "Rob's Feature", "Rob", 2006, 1, 1);

    int ind = binary_search_name("Nolan", films, 4);

    ck_assert_int_eq(ind, 0);

    release_film_array_memory(films, 4);
}
END_TEST


START_TEST(test_search_name_mid)
{
    struct film *films = create_film_array(4);
    initialize_film(&films[0], "Alex's Film", "Alex", 2002, 1, 1);
    initialize_film(&films[1], "Home Sweet Home", "Home", 1995, 1, 1);
    initialize_film(&films[2], "Nolan's Creation", "Nolan", 2010, 1, 1);
    initialize_film(&films[3], "Rob's Directorial Debut", "Rob", 2006, 1, 1);

    int ind = binary_search_name("Home", films, 4);

    ck_assert_int_eq(ind, 1);

    release_film_array_memory(films, 4);
}
END_TEST

START_TEST(test_search_name_neg)
{
    struct film *films = create_film_array(4);
    initialize_film(&films[0], "Alex's Movie", "Alex", 2002, 1, 1);
    initialize_film(&films[1], "Home Alone", "Home", 1992, 1, 1);
    initialize_film(&films[2], "Smith's Production", "Smith", 2005, 1, 1);
    initialize_film(&films[3], "Rob's Cinematic Work", "Rob", 2010, 1, 1);

    int ind = binary_search_name("Nolan", films, 4);

    ck_assert_int_eq(ind, -1);

    release_film_array_memory(films, 4);
}
END_TEST

// Тесты функции binary_search_year
START_TEST(test_search_year_begin)
{
    struct film *films = create_film_array(4);
    initialize_film(&films[0], "Film A", "Director A", 2000, 1, 1);
    initialize_film(&films[1], "Film B", "Director B", 2005, 1, 1);
    initialize_film(&films[2], "Film C", "Director C", 2010, 1, 1);
    initialize_film(&films[3], "Film D", "Director D", 2015, 1, 1);

    int ind = binary_search_year(2000, films, 4);

    ck_assert_int_eq(ind, 0);

    release_film_array_memory(films, 4);
}
END_TEST
START_TEST(test_search_year_end)
{
    struct film *films = create_film_array(4);
    initialize_film(&films[0], "Film A", "Director A", 2000, 1, 1);
    initialize_film(&films[1], "Film B", "Director B", 2005, 1, 1);
    initialize_film(&films[2], "Film C", "Director C", 2010, 1, 1);
    initialize_film(&films[3], "Film D", "Director D", 2015, 1, 1);

    int ind = binary_search_year(2015, films, 4);

    ck_assert_int_eq(ind, 3);

    release_film_array_memory(films, 4);
}
END_TEST

START_TEST(test_search_year_mid)
{
    struct film *films = create_film_array(4);
    initialize_film(&films[0], "Film A", "Director A", 2000, 1, 1);
    initialize_film(&films[1], "Film B", "Director B", 2005, 1, 1);
    initialize_film(&films[2], "Film C", "Director C", 2010, 1, 1);
    initialize_film(&films[3], "Film D", "Director D", 2015, 1, 1);

    int ind = binary_search_year(2005, films, 4);

    ck_assert_int_eq(ind, 1);

    release_film_array_memory(films, 4);
}
END_TEST

START_TEST(test_search_year_neg)
{
    struct film *films = create_film_array(4);
    initialize_film(&films[0], "Film A", "Director A", 2000, 1, 1);
    initialize_film(&films[1], "Film B", "Director B", 2005, 1, 1);
    initialize_film(&films[2], "Film C", "Director C", 2010, 1, 1);
    initialize_film(&films[3], "Film D", "Director D", 2015, 1, 1);

    int ind = binary_search_year(1995, films, 4);

    ck_assert_int_eq(ind, -1);

    release_film_array_memory(films, 4);
}
END_TEST

Suite* binary_search_title_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("binary_search_title:");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_search_title_begin);
    tcase_add_test(tc_pos, test_search_title_end);
    tcase_add_test(tc_pos, test_search_title_mid);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_search_title_neg);
    suite_add_tcase(s, tc_neg);

    return s;
}


Suite* binary_search_name_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("binary_search_name:");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_search_name_begin);
    tcase_add_test(tc_pos, test_search_name_end);
    tcase_add_test(tc_pos, test_search_name_mid);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_search_name_neg);
    suite_add_tcase(s, tc_neg);

    return s;
}

Suite* binary_search_year_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("binary_search_year:");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_search_year_begin);
    tcase_add_test(tc_pos, test_search_year_end);
    tcase_add_test(tc_pos, test_search_year_mid);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_search_year_neg);
    suite_add_tcase(s, tc_neg);

    return s;
}
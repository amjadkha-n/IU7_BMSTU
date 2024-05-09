#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/film_in_out.h"
#include "../inc/struct.h"
#include "../inc/constant.h"

int film_copy(struct film *dst, struct film *src, int index, int len)
{
    return initialize_film(dst, src->title, src->name, src->year, index, len);
}

void sort_films_by_title(struct film *films, struct film *new_film, int num)
{
    int index = 0;

    while (index < num && strcmp(new_film->title, films[index].title) >= 0)
        index++;

    for (int i = num; i > index; i--)
        film_copy(&films[i], &films[i - 1], i, num);

    film_copy(&films[index], new_film, index, num);
}


void sort_films_by_name(struct film *films, struct film *new_film, int num)
{
    int index = 0;

    while (index < num && strcmp(new_film->name, films[index].name) >= 0)
        index++;

    for (int i = num; i > index; i--)
        film_copy(&films[i], &films[i - 1], i, num);

    film_copy(&films[index], new_film, index, num);
}

void sort_films_by_year(struct film *films, struct film *new_film, int num)
{
    int index = 0;

    while (index < num && new_film->year >= films[index].year)
        index++;

    for (int i = num; i > index; i--)
        film_copy(&films[i], &films[i - 1], i, num);

    film_copy(&films[index], new_film, index, num);
}


int add_sorted_to_array(char **argv, struct film *films, int *films_number)
{
    FILE *f = fopen(argv[1], "r");
    char title[MAX_BUF + 1], name[MAX_BUF + 1];
    int ch, num, index = 0;

    ch = read_film_struct_from_file(f, title, name, &num);

    if (ch == 0)
    {
        fclose(f);
        return EMPTY_FILE;
    }

    if (ch != 3)
    {
        fclose(f);
        return INCORRECT_INPUT;
    }

    while (ch == 3)
    {
        struct film new_film;
        int add_result;

        add_result = initialize_film(&new_film, title, name, num, index, *films_number);

        if (add_result != OK)
        {
            fclose(f);
            return add_result;
        }

        if (strcmp(argv[2], "title") == 0)
            sort_films_by_title(films, &new_film, index);
        else if (strcmp(argv[2], "name") == 0)
            sort_films_by_name(films, &new_film, index);
        else
            sort_films_by_year(films, &new_film, index);

        index += 1;
        ch = read_film_struct_from_file(f, title, name, &num);
    }

    if (ch > 0)
    {
        fclose(f);
        return INCORRECT_INPUT;
    }

    *films_number = index;

    if (*films_number == 0)
    {
        fclose(f);
        return EMPTY_FILE;
    }

    fclose(f);

    return OK;
}

int binary_search_title(char *key, struct film *films, int films_number)
{
    int left = 0, right = films_number - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int comparison = strcmp(key, films[mid].title);

        if (comparison == 0)
            return mid;
        else if (comparison < 0)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;
}


int binary_search_name(char *key, struct film *films, int films_number)
{
    int left = 0, right = films_number - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int comparison = strcmp(key, films[mid].name);

        if (comparison == 0)
            return mid;
        else if (comparison < 0)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;
}

int binary_search_year(int key, struct film *films, int films_number)
{
    int left = 0, right = films_number - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (films[mid].year == key)
            return mid;
        else if (films[mid].year < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}


int find_film_by_key(char **argv, struct film *films, int films_number)
{
    int index = -1;

    if (strcmp(argv[2], "title") == 0)
    {
        index = binary_search_title(argv[3], films, films_number);
    }
    else if (strcmp(argv[2], "name") == 0)
    {
        index = binary_search_name(argv[3], films, films_number);
    }
    else
    {
        int number = atoi(argv[3]);

        if (number <= 0)
            return INCORRECT_ARGS;

        index = binary_search_year(number, films, films_number);
    }

    if (index == -1)
        return NOT_FOUND;

    print_single_film(films[index]);

    return OK;
}

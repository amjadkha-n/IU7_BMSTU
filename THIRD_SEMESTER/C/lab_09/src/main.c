#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/constant.h"
#include "../inc/f_process.h"
#include "../inc/process.h"
#include "../inc/film_in_out.h"
#include "../inc/struct.h"

int main(int argc, char **argv)
{
    int ch, films_number = 0, amount;
    struct film *films;

    if (argc != 3 && argc != 4)
    {
        print_error_messages(INCORRECT_ARGS);
        return INCORRECT_ARGS;
    }

    if ((strcmp(argv[2], "title") != 0) &&
        (strcmp(argv[2], "name") != 0) &&
        (strcmp(argv[2], "year") != 0))
    {
        print_error_messages(INCORRECT_ARGS);
        return INCORRECT_ARGS;
    }

    ch = file_check(argv);

    if (ch != OK)
    {
        print_error_messages(ch);
        return ch;
    }

    amount = struct_count(argv[1]);

    if (amount == 0)
    {
        print_error_messages(EMPTY_FILE);
        return EMPTY_FILE;
    }

    if (amount == INCORRECT_INPUT)
    {
        print_error_messages(INCORRECT_INPUT);
        return INCORRECT_INPUT;
    }

    films = create_film_array(amount);

    if (films == NULL)
    {
        print_error_messages(MEMORY_ERROR);
        return MEMORY_ERROR;
    }

    ch = add_sorted_to_array(argv, films, &films_number);

    if (ch != OK)
    {
        print_error_messages(ch);
        release_film_array_memory(films, amount);
        return ch;
    }

    if (argc == 3)
    {
        print_all_films(films, films_number);
    }

    if (argc == 4)
    {
        ch = find_film_by_key(argv, films, films_number);

        if (ch == INCORRECT_ARGS)
        {
            print_error_messages(INCORRECT_ARGS);
            release_film_array_memory(films, amount);
            return INCORRECT_ARGS;
        }

        if (ch == NOT_FOUND)
        {
            printf("Not found\n");
            release_film_array_memory(films, amount);
            return OK;
        }
    }

    release_film_array_memory(films, amount);

    return OK;
}

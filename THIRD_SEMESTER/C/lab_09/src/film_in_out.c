#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/constant.h"
#include "../inc/struct.h"
#include <ctype.h>


struct film *create_film_array(int number)
{
    struct film *films = calloc(number, sizeof(struct film));
    if (films == NULL)
        return NULL;

    return films;
}

void release_film_array_memory(struct film *films, int amount)
{
    if (films == NULL) {
        return;
    }

    for (int i = 0; i < amount; i++)
    {
        free(films[i].title);
        free(films[i].name);
    }

    free(films);
}

int read_line_from_file(FILE *f, char *string)
{
    if (fgets(string, 100, f) == NULL)
        return INCORRECT_INPUT;

    size_t length = strlen(string);

    if (length > 0) {
        if (string[length - 1] == '\n') {
            string[length - 1] = '\0';
            length--;
        }

        for (size_t i = 0; i < length; i++) {
            if (!isspace(string[i])) {
                return OK;
            }
        }
    }

    return EMPTY_STRING;
}


int read_integer_from_file(FILE *f, int *number)
{
    char buffer[32];
    
    if (fgets(buffer, sizeof(buffer), f) != NULL)
    {
        if (sscanf(buffer, "%d", number) == 1)
        {
            if (*number > 0)
            {
                return OK;
            }
        }
    }
    
    return INCORRECT_INPUT;
}


int read_film_struct_from_file(FILE *f, char *title, char *name, int *num)
{
    int ch = 0, number = 0;

    ch = read_line_from_file(f, title);

    if (ch == OK)
    {
        number += 1;
        ch = read_line_from_file(f, name);

        if (ch == OK)
        {
            number += 1;

            ch = read_integer_from_file(f, num);

            if (ch == OK && *num > 0)
                number += 1;
            else
                return INCORRECT_INPUT;
        }
    }

    return number;
}

int initialize_film(struct film *new_film, char *title, char *name, int year, int index, int len)
{
    char *ptitle = strdup(title);
    char *pname = strdup(name);

    if (!ptitle || !pname)
    {
        free(ptitle);

        return MEMORY_ERROR;
    }

    if (len != 0 && index != len)
    {
        free(new_film->title);
        free(new_film->name);
    }

    new_film->title = ptitle;
    new_film->name = pname;
    new_film->year = year;

    return OK;
}


struct film *allocate_and_create_file(char *title, char *name, int year)
{
    struct film *film = malloc(sizeof(struct film));

    if (!film)
        return NULL;

    film->title = strdup(title);

    if (!film->title) {
        free(film);
        return NULL;
    }

    film->name = strdup(name);

    if (!film->name) {
        free(film->title);
        free(film);
        return NULL;
    }

    film->year = year;

    return film;
}


void release_film_memory(struct film *film)
{
    if (film == NULL)
        return;

    free(film->title);
    free(film->name);
    free(film);
}


int print_all_films(struct film *films, int num)
{
    if (films == NULL)
        return INCORRECT_INPUT;

    for (int i = 0; i < num; i++) {
        if (films[i].title && films[i].name) {
            printf("%s\n%s\n%d\n", films[i].title, films[i].name, films[i].year);
        }
    }

    return OK;
}

void print_single_film(struct film film)
{
    printf("%s\n%s\n%d\n", film.title, film.name, film.year);
}

void print_error_messages(int ch)
{
    switch (ch) {
        case INCORRECT_ARGS:
            printf("INCORRECT_ARGS\n");
            break;
        case FILE_OPEN_ERROR:
            printf("FILE_OPEN_ERR\n");
            break;
        case FILE_CLOSE_ERROR:
            printf("FILE_CLOSE_ERR\n");
            break;
        case FILE_ERROR:
            printf("FILE_ERR\n");
            break;
        case EMPTY_FILE:
            printf("EMPTY_FILE\n");
            break;
        case INCORRECT_INPUT:
            printf("INCORRECT_INPUT\n");
            break;
        case EMPTY_STRING:
            printf("EMPTY_STR\n");
            break;
        default:
            break;
    }
}

#ifndef CDIO_H
#define CDIO_H

#include <stdio.h>
#include "constant.h"
#include "struct.h"

struct film *create_film_array(int number);
void release_film_array_memory(struct film *films, int amount);
int read_line_from_file(FILE *f, char *string);
int read_integer_from_file(FILE *f, int *number);
int read_film_struct_from_file(FILE *f, char *title, char *name, int *num);
int initialize_film(struct film *new_film, char *title, char *name, int year, int index, int len);
struct film *allocate_and_create_file(char *title, char *name, int year);
void release_film_memory(struct film *film);
int print_all_films(struct film *films, int num);
void print_single_film(struct film film);
void print_error_messages(int ch);

#endif

#ifndef PROCESS_H
#define PROCESS_H

#include "../inc/constant.h"
#include "../inc/struct.h"

int film_copy(struct film *dst, struct film *src, int index, int len);
void sort_films_by_title(struct film *films, struct film *new_film, int num);
void sort_films_by_name(struct film *films, struct film *new_film, int num);
void sort_films_by_year(struct film *films, struct film *new_film, int num);
int add_sorted_to_array(char **argv, struct film *films, int *films_number);
int binary_search_title(char *key, struct film *films, int films_number);
int binary_search_name(char *key, struct film *films, int films_number);
int binary_search_year(int key, struct film *films, int films_number);
int find_film_by_key(char **argv, struct film *films, int films_number);
#endif

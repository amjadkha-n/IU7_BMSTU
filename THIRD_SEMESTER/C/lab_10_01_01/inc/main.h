#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ARGUMENT_ERROR 1
#define MISSING_FILE 2
#define FILE_CLOSE_ERROR 3
#define MEMORY_ALLOCATION_FAILURE 4
#define EMPTY_LIST 6
#define DIFFERENT_ELEMENTS 7
#define DIFFERENT_LISTS 8


typedef struct node
{
    void *data;
    struct node *next;
} node_t;

typedef struct salary
{
    int *array;
    int size;
} salary_t;

int read_salary_array(salary_t *array, FILE *f);
int fill_linked_list(node_t **head, salary_t *array);
void print_linked_list(node_t *head, FILE *f);

node_t *sort(node_t *head, int (*comparator)(const void*, const void*));
void sorted_insert(node_t **head, node_t *element,
int (*comparator)(const void*, const void*));
void add_new_elem(node_t *prev_elem, node_t *next_elem, node_t *element, node_t **head);

int comparator(const void *element_1, const void *element_2);
node_t *search_list(node_t *head, const void *data, int (*comparator)(const void*, const void*));
void *remove_first_node(node_t **head);
node_t *reverse_list(node_t *head);
void free_list(node_t *head);
int custom_list_operation(node_t **head, salary_t *array); 

#endif

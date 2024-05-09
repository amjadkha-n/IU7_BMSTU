#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define OK 0
#define CUSTOM_ERROR -1
#define ALIGNMENT_ERROR 1
#define READ_ACTION_ERROR 2
#define INVALID_ACTION_ERROR 3
#define READ_NUMBER_ERROR 4
#define NEGATIVE_VALUE_ERROR 5
#define EMPTY_LIST_ERROR 6
#define DIFFERENT_ELEMENTS_ERROR 7
#define DIFFERENT_LISTS_ERROR 8


#define LEN_ACTION 3

typedef struct node
{
    int power;
    struct node *next;
} node_t;

void print_linked_list(node_t *head);
void free_linked_list(node_t *head);
void square_the_number(node_t *head);

node_t *insert_item_to_list(node_t **head);
node_t *multiply_numbers(node_t *first_head, node_t *second_head);

int display_number_as_list(void);
int multiplication_of_two_numbers(void);
int squaring_the_number(void);
int dividing_number_without_rem(void);
int read_number(int *number);
int check_if_prime(int number);
int fill_the_list(node_t **head, int number);
int length_list(node_t *head);
int division_of_two_numbers(node_t *first_head, node_t *second_head, node_t **res_head);
int extract_number_from_list(node_t *head);

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MY_FUNC_H_INCLUDED
#define MY_FUNC_H_INCLUDED

#define OK 0
#define FILE_OPEN_ERR 1
#define INVALID_PRICE_ERR 2
#define OK_NUM_PRODUCTS 3
#define INVALID_NUM_PRODUCTS_ERR 4
#define END_OF_FILE_ERR 5
#define INVALID_NAME_ERR 6
#define INCORRECT_ARGS_ERR 7
#define NO_PRODUCTS_FOUND 8
#define MAX_NAME_LENGTH 25
#define MAX_PRODUCTS 15
typedef struct
{
    char *name;
    int price;
} product;

int read_struct(FILE *file, product *products);
int read_file_and_process(FILE *file, product **products, int *num_products);
int display_low_price(product *products, int num_products, int max_price);
void free_products(product *products, int num_products);

#endif


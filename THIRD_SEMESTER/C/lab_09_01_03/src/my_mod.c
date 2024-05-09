#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../inc/my_mod.h"

int read_struct(FILE *file, product *products)
{
    size_t len = 0;
    products->name = NULL;

    if (getline(&(products->name), &len, file) == -1)
    {
        free(products->name);
        return END_OF_FILE_ERR;
    }

    products->name[strcspn(products->name, "\n")] = '\0';

    if (fscanf(file, "%d\n", &products->price) == 1 && products->price >= 0)
    {
        return OK;
    }

    free(products->name);
    return INVALID_NAME_ERR;
}


int read_file_and_process(FILE *file, product **products, int *num_products)
{
    int num;
    if (fscanf(file, "%d\n", &num) != 1 || num <= 0 || num > MAX_PRODUCTS)
    {
        return INVALID_NUM_PRODUCTS_ERR;
    }

    *num_products = num;
    *products = (product *)malloc(num * sizeof(product));
    if (*products == NULL)
    {
        return INVALID_NUM_PRODUCTS_ERR;
    }

    for (int i = 0; i < num; i++)
    {
        int result = read_struct(file, &(*products)[i]);
        if (result != OK)
        {
            free_products(*products, i);
            return result;
        }
    }

    return OK_NUM_PRODUCTS;
}

int display_low_price(product *products, int num_products, int max_price)
{
    if (max_price <= 0)
    {
        return INVALID_PRICE_ERR;
    }

    int i;
    int no_products_found = 1;

    for (i = 0; i < num_products; i++)
    {
        if (products[i].price < max_price)
        {
            printf("%s\n", products[i].name);
            printf("%d\n", products[i].price);
            no_products_found = 0;
        }
    }

    if (no_products_found)
    {
        return OK;
    }

    return OK;
}
void free_products(product *products, int num_products)
{
    for (int i = 0; i < num_products; i++)
    {
        if (products[i].name != NULL)
        {
            free(products[i].name);
            products[i].name = NULL;
        }
    }
    
    free(products);
}

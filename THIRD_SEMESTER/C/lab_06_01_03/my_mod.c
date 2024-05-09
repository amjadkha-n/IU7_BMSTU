#include <stdio.h>
#include <string.h>
#include "my_mod.h"

/**
 * @brief Reads a product structure from a file.
 *
 * This function attempts to read a product's name and price from the given file
 * and populates the provided 'product' structure with the data.
 *
 * @param file The file pointer to read from.
 * @param products The product structure to populate.
 * @return Returns an error code if any issues occur during reading:
 *         - ERR_END_OF_FILE if end of file is reached prematurely.
 *         - ERR_INVALID_NAME if the read name is too long or the price is non-positive.
 *         - OK if reading is successful.
 */
int read_struct(FILE *file, product *products)
{
    if (fscanf(file, "%s %d", products->name, &products->price) != 2)
    {
        return ERR_END_OF_FILE;
    }

    if (strlen(products->name) > MAX_NAME_LEN || products->price <= 0)
    {
        return ERR_INVALID_NAME;
    }

    return OK;
}

/**
 * @brief Reads a file and processes its contents to populate an array of products.
 *
 * This function reads the number of products from the file, stores it in 'num_products',
 * and then reads and validates each product's details using 'read_struct'.
 *
 * @param file The file pointer to read from.
 * @param products An array of products to populate.
 * @param num_products A pointer to an integer to store the number of products read.
 * @return Returns an error code if any issues occur during processing:
 *         - ERR_INVALID_NUM_PRODUCTS if the number of products is invalid.
 *         - Any error code returned by 'read_struct' if a product read fails.
 *         - OK_NUM_PRODUCTS if processing is successful.
 */
int read_file_and_process(FILE *file, product *products, int *num_products)
{
    int num;
    if (fscanf(file, "%d", &num) != 1 || num <= 0 || num > MAX_PRODUCTS)
    {
        return ERR_INVALID_NUM_PRODUCTS;
    }

    *num_products = num;

    for (int i = 0; i < num; i++)
    {
        int result = read_struct(file, &products[i]);
        if (result != OK)
        {
            return result;
        }
    }

    return OK_NUM_PRODUCTS;
}

/**
 * @brief Displays products with prices lower than a specified maximum price.
 *
 * This function iterates through each product and prints the name and price
 * of products with prices lower than the specified 'max_price'.
 *
 * @param products An array of products to search.
 * @param num_products The number of products in the array.
 * @param max_price The maximum price for filtering products.
 * @return Returns an error code if 'max_price' is non-positive.
 *         Returns the number of products with prices lower than 'max_price' otherwise.
 */
int display_low_price(product *products, int num_products, int max_price)
{
    if (max_price <= 0)
    {
        return ERR_INVALID_PRICE;
    }

    int i = 0;

    while (i < num_products)
    {
        if (products[i].price < max_price)
        {
            printf("%s\n", products[i].name);
            printf("%d\n", products[i].price);
        }
        i++;
    }

    return OK;
}

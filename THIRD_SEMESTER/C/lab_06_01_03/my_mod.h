#ifndef MY_MOD_H_INCLUDED
#define MY_MOD_H_INCLUDED

/**
 * @file my_mod.h
 * @brief Header file for My Module.
 */

/**
 * @brief Enumeration of error codes and special values used in My Module.
 */
enum 
{
    OK = 0, /**< Operation successful. */
    ERR_FILE_OPEN = 1, /**< Error: Unable to open a file. */
    ERR_INVALID_PRICE = 2, /**< Error: Invalid price encountered. */
    OK_NUM_PRODUCTS = 3, /**< Operation successful, number of products within limits. */
    ERR_INVALID_NUM_PRODUCTS = 4, /**< Error: Invalid number of products. */
    ERR_END_OF_FILE = 5, /**< Error: End of file reached prematurely. */
    ERR_INVALID_NAME = 6, /**< Error: Invalid product name. */
    ERR_INCORRECT_ARGS = 7, /**< Error: Incorrect function arguments. */
    ERR_NO_PRODUCTS_FOUND = 8, /**< Error: No products found. */
    MAX_NAME_LEN = 25, /**< Maximum length for a product name. */
    MAX_PRODUCTS = 15 /**< Maximum number of products allowed. */
};

/**
 * @brief Define a structure to represent a product with a name and price.
 */
typedef struct
{
    char name[MAX_NAME_LEN + 1]; /**< The name of the product. */
    int price; /**< The price of the product. */
} product;

/**
 * @brief Reads a product structure from a file.
 *
 * @param file The file pointer to read from.
 * @param products The product structure to populate.
 * @return Returns an error code if any issues occur during reading.
 */
int read_struct(FILE *file, product *products);

/**
 * @brief Reads a file and processes its contents to populate an array of products.
 *
 * @param file The file pointer to read from.
 * @param products An array of products to populate.
 * @param num_products A pointer to an integer to store the number of products read.
 * @return Returns an error code if any issues occur during processing.
 */
int read_file_and_process(FILE *file, product *products, int *num_products);

/**
 * @brief Displays products with prices lower than a specified maximum price.
 *
 * @param products An array of products to search.
 * @param num_products The number of products in the array.
 * @param max_price The maximum price for filtering products.
 * @return Returns the number of products with prices lower than max_price.
 */
int display_low_price(product *products, int num_products, int max_price);

#endif

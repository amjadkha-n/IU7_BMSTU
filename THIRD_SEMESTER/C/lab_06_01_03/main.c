#include <stdio.h>
#include "my_mod.h"

/**
 * @brief The main function of the program.
 *
 * This function is the entry point for the program. It processes command-line
 * arguments, opens a file, reads and processes its content, and displays
 * products with prices lower than a specified maximum price.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing command-line arguments.
 * @return Returns an error code:
 *         - OK if the program runs successfully.
 *         - ERR_INCORRECT_ARGS if an incorrect number of command-line arguments is provided.
 *         - ERR_FILE_OPEN if the specified input file cannot be opened.
 *         - ERR_INVALID_PRICE if the specified maximum price is invalid.
 *         - Any error code returned by 'read_file_and_process' or 'display_low_price'.
 */
int main(int argc, char *argv[])
{
    int result = OK;

    if (argc != 3)
    {
        result = ERR_INCORRECT_ARGS;
    }
    else
    {
        FILE *file = fopen(argv[1], "r");
        if (!file)
        {
            result = ERR_FILE_OPEN;
        }
        else
        {
            int max_price;
            if (sscanf(argv[2], "%d", &max_price) != 1 || max_price <= 0)
            {
                fclose(file);
                result = ERR_INVALID_PRICE;
            }
            else
            {
                product products[MAX_PRODUCTS];
                int num_products = 0;
                result = read_file_and_process(file, products, &num_products);
                fclose(file);

                if (result == OK_NUM_PRODUCTS)
                {
                    result = display_low_price(products, num_products, max_price);
                }
            }
        }
    }

    return (result == OK) ? OK : result;
}

#include "../inc/my_mod.h"

#include "../inc/my_mod.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return INCORRECT_ARGS_ERR;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return FILE_OPEN_ERR;
    }

    int max_price;
    if (sscanf(argv[2], "%d", &max_price) != 1 || max_price <= 0)
    {
        fclose(file);
        return INVALID_PRICE_ERR;
    }

    product *products = NULL;
    int num_products = 0;

    int result = read_file_and_process(file, &products, &num_products);
    fclose(file);

    if (result != OK_NUM_PRODUCTS)
    {
        return result;
    }

    result = display_low_price(products, num_products, max_price);
    free_products(products, num_products);

    return (result == OK) ? OK : result;
}

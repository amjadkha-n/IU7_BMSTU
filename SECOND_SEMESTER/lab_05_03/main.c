#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# include "my_mod.h"

#define FILE_OPEN_ERROR 1
#define CNUMBER_ERROR 2
#define INCORRECT_ARGS 3
#define NOT_A_TYPED_FILE_ERROR 4
#define EMPTY_FILE 5 

int main(int argc, char **argv)
{
    if (argc == 3 && strcmp(argv[1], "p") == 0)
    { 
        int rc = print_numbers(argv[2]);
        if (rc == 1)
            return FILE_OPEN_ERROR;
        if (rc == 2)
            return NOT_A_TYPED_FILE_ERROR;
        if (rc == 3)
            return EMPTY_FILE;
    }
    else if (argc == 3 && strcmp(argv[1], "s") == 0)
    {
        int rc = sort_numbers(argv[2]);
        if (rc == 1)
            return FILE_OPEN_ERROR;
        if (rc == 2)
            return NOT_A_TYPED_FILE_ERROR;
        if (rc == 3)
            return EMPTY_FILE;
    }
    else if (argc == 4 && strcmp(argv[1], "c") == 0)
    {
        int cnumber = atoi(argv[2]);
        if (cnumber <= 0)
            return CNUMBER_ERROR;
        if (gen_rand_num(argv[3], cnumber) == 1)
            return FILE_OPEN_ERROR;
    }
    else if (argc == 3 && strcmp(argv[1], "t2b") == 0)
    {
        int rc = text_to_bin(argv[2]);
        if (rc == 1)
            return FILE_OPEN_ERROR;
    }
    else if (argc == 3 && strcmp(argv[1], "b2t") == 0)
    {
        int rc = bin_to_text(argv[2]);
        if (rc == 1)
            return FILE_OPEN_ERROR;
        if (rc == 2)
            return NOT_A_TYPED_FILE_ERROR;
    }
    else
        return INCORRECT_ARGS;

    return EXIT_SUCCESS;
}

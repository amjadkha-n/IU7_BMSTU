#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "my_mod.h"

int main(void) 
{
    int min_dist = 0;

    int status = process(stdin, &min_dist);

    if (status < 0) 
    {
        myperror(my_str_err(status));
        return ERROR_FIND_LOC_MAX;
    }

    printf("Smallest distance between local maxima: %d\n", min_dist);

    return SUCCESS;
}

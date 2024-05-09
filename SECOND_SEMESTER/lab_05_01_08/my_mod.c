#include "my_mod.h"

int min(int a, int b) 
{
    return (a < b) ? a : b;
}

void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_min(int *a, int *b) 
{
    if (*a > *b) 
    {
        swap(a, b);
    }
}

int process(FILE *f, int *min_dist) 
{
    *min_dist = INT_MAX;

    int local_max1 = -1;
    int local_max2 = -1;

    if (f == NULL || min_dist == NULL)
        return ERROR_NULL_POINTER;

    if (ferror(f))
        return ERROR_FILE;

    int curr_ind = 0;

    int last;
    int curr = -1;

    if (scanf("%d", &last) != 1)
        return ERROR_NO_LOC_MAX;

    bool is_last_less_curr = false;

    while (scanf("%d", &curr) == 1) 
    {
        if (is_last_less_curr && last > curr) 
        {
            local_max1 = curr_ind;
            swap_min(&local_max1, &local_max2);
        }

        is_last_less_curr = last < curr;

        if (local_max1 != -1 && local_max2 != -1)
            *min_dist = min(abs(*min_dist), local_max2 - local_max1);

        last = curr;
        curr_ind++;
    }

    // return (local_max1 == -1 || local_max2 == -1) ? -1 : 0;
     
    if (local_max1 == -1 || local_max2 == -1)
        return ERROR_NO_LOC_MAX;

    return SUCCESS;
}

char *my_str_err(int errnum) 
{
    switch (errnum) 
    {
        case ERROR_NO_LOC_MAX:
            return "No more than two local maxima found";
        case ERROR_NULL_POINTER:
            return "Invalid pointer given. Exiting";
        case ERROR_FILE:
            return "File error";
        case ERROR_SEEK:
            return "Seek failed";
    }

    return "No such process";
}

void myperror(const char *err)
{
    printf("%s\n", err);
}

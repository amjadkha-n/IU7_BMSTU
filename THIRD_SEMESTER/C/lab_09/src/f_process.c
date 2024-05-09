#include <stdio.h>
#include <string.h>
#include "../inc/constant.h"
#include "../inc/f_process.h"
#include "../inc/film_in_out.h"

int file_check(char **argv)
{
    FILE *f = fopen(argv[1], "r");

    if (f == NULL)
        return FILE_OPEN_ERROR;

    if (fseek(f, 0, SEEK_END) != 0)
    {
        fclose(f);
        return FILE_ERROR;
    }

    long fileSize = ftell(f);

    if (fileSize == -1)
    {
        fclose(f);
        return FILE_ERROR;
    }

    if (fclose(f) != 0)
        return FILE_CLOSE_ERROR;

    return OK;
}
int struct_count(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    int count = 0;
    char title[MAX_BUF + 1], name[MAX_BUF + 1];
    int ch, num;

    while ((ch = read_film_struct_from_file(f, title, name, &num)) == 3)
    {
        count += 1;
    }

    if (ch > 0)
    {
        fclose(f);
        return INCORRECT_INPUT;
    }

    fclose(f);

    return count;
}

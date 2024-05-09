#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "my_mod.h"

size_t get_file_size(FILE *file)
{
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return file_size;
}


int gen_rand_num(char *filename, int cnumber)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
        return 1;

    srand(time(NULL));

    for (int i = 0; i < cnumber; i++)
    {
        int random_number = rand();
        size_t elements_written = fwrite(&random_number, sizeof(int), 1, file);
        if (elements_written != 1)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}


int print_numbers(char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
        return 1;

    size_t file_size = get_file_size(file) / sizeof(int);

    if (get_file_size(file) % sizeof(int) != 0)
    {
        fclose(file);
        return 2;
    }

    if (file_size == 0)
    {
        fclose(file);
        return 3;
    }

    fseek(file, 0, SEEK_SET);

    for (size_t i = 0; i < file_size; i++)
    {
        int number;
        size_t elements_read = fread(&number, sizeof(int), 1, file);
        if (elements_read != 1)
        {
            fclose(file);
            return 1;
        }
        printf("%d ", number);
    }
    printf("\n");

    fclose(file);

    return 0;
}

int get_number_by_position(FILE *file, size_t position)
{
    int number;

    fseek(file, position * sizeof(int), SEEK_SET);
    size_t elements_read = fread(&number, sizeof(int), 1, file);
    if (elements_read != 1)
        return 0;

    return number;
}


void put_number_by_position(FILE *file, size_t position, int number)
{
    fseek(file, position * sizeof(int), SEEK_SET);
    fwrite(&number, sizeof(int), 1, file);
}

void swap_numbers(FILE *file, size_t position1, size_t position2)
{
    int temporary = get_number_by_position(file, position1);
    put_number_by_position(file, position1, get_number_by_position(file, position2));
    put_number_by_position(file, position2, temporary);
}

int sort_numbers(char *filename)
{
    FILE *file = fopen(filename, "r+b");
    if (file == NULL)
        return 1;

    size_t file_size = get_file_size(file) / sizeof(int);
    if (get_file_size(file) % sizeof(int) != 0)
    {
        fclose(file);
        return 2;
    }
    if (file_size == 0)
    {
        fclose(file);
        return 3;
    }

    for (size_t i = file_size - 1; i > 0; i--)
    {
        for (size_t j = 0; j < i; j++)
        {
            int number1 = get_number_by_position(file, j);
            int number2 = get_number_by_position(file, j + 1);
            if (number1 > number2)
            {
                swap_numbers(file, j, j + 1);
            }
        }
    }

    fclose(file);

    return 0;
}

int text_to_bin(char *filename)
{
    FILE *src = fopen(filename, "r");
    if (src == NULL)
        return 1;

    FILE *dst = fopen("temp.tmp", "wb");
    if (dst == NULL)
    {
        fclose(src);
        return 1;
    }

    int number;

    while (fscanf(src, "%d", &number) == 1)
    {
        if (fwrite(&number, sizeof(int), 1, dst) != 1)
        {
            fclose(src);
            fclose(dst);
            return 1;
        }
    }

    fclose(dst);
    fclose(src);

    if (rename("temp.tmp", filename) != 0)
        return 1;

    return 0;
}

int bin_to_text(char *filename)
{
    FILE *src = fopen(filename, "rb");
    if (src == NULL)
        return 1;

    FILE *dst = fopen("temp.tmp", "w");
    if (dst == NULL)
    {
        fclose(src);
        return 1;
    }

    if (get_file_size(src) % sizeof(int) != 0)
    {
        fclose(src);
        fclose(dst);
        return 2;
    }

    size_t size = get_file_size(src) / sizeof(int);

    int number;

    for (size_t i = 0; i < size; i++)
    {
        if (fread(&number, sizeof(int), 1, src) != 1)
        {
            fclose(src);
            fclose(dst);
            return 1;
        }
        fprintf(dst, "%d\n", number);
    }

    fclose(dst);
    fclose(src);

    if (rename("temp.tmp", filename) != 0)
        return 1;

    return 0;
}

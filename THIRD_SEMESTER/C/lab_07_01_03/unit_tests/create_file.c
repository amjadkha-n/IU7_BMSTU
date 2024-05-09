#include <stdio.h>
#include <stdlib.h>

/**
 * @file random_number_generator.c
 *
 * @brief Generates a file containing random numbers within a specified range.
 *
 * This program generates a file with a specified number of random integers within
 * the range [-5000, 4999] and saves them to the specified output file.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments where argv[0] is the program name
 *             and argv[1] is the output file name.
 *
 * @return 0 if the file is successfully created and numbers are written, 1 if the
 *         command-line arguments are incorrect, 2 if there is an error opening the
 *         output file.
 */
int main(int argc, char **argv)
{
    int check = 0;
    int length = 0;
    
    if (argc != 2)
    {
        printf("Usage: %s <output_file>\n", argv[0]);
        return 1;
    }

    scanf("%d", &length);
    FILE *f = fopen(argv[1], "w");
    
    if (f == NULL)
    {
        perror("Error opening file");
        return 2;
    }

    for (int i = 0; i < length; i++)
    {
        fprintf(f, "%d ", rand() % 10000 - 5000);
    }

    fclose(f);
    
    return check;
}

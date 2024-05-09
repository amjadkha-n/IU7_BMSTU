#include "../inc/main.h"
/**
* @brief Count the number of elements in a file.
*
* This function counts the number of integer elements in the given file.
*
* @param src The input file.
* @return The number of elements if successful, OK if the file is empty, or READ_ERROR on failure.
*/

/**
* @brief Check if command-line arguments are valid.
*
* This function checks if the number of command-line arguments is either 3 or 4 with a specific filter option.
*
* @param argc The number of command-line arguments.
* @param argv An array of strings containing the command-line arguments.
* @return OK if the arguments are valid, or ARG_ERROR if they are not.
*/
int are_arguments_valid(int argc, char **argv)
{
    int check = ARG_ERROR;

    // Check if the number of command-line arguments is either 3 or 4 with specific filter option
    if (argc == 3 || (argc == 4 && argv[3][0] == 'f' && argv[3][1] == 0))
    {
        check = OK;
    }
    // Return the result (OK or ARG_ERROR)
    return check;
}

/**
* @brief Check if command-line arguments indicate filtering.
*
* This function checks if the number of command-line arguments is 4 and if the filter option is specified.
*
* @param argc The number of command-line arguments.
* @param argv An array of strings containing the command-line arguments.
* @return 1 if filtering is indicated, 0 if not.
*/
int are_arguments_for_filter(int argc, char **argv)
{
    // Check if the number of command-line arguments is 4 and if the filter option is specified
    return (argc == 4 && argv[3][0] == 'f' && argv[3][1] == 0);  // Return true or false
}
int amount_of_elements(FILE *src)
{
    int n = 0;
    int element;
    // Read integers from the file
    while (fscanf(src, "%d", &element) == 1)
    {
        n++;
    }
    if (n > 0)
    {
        return n;
    }
    // if end of file is reached with no elements
    else if (feof(src))
    {
        return OK;
    }
    else
    {
        return READ_ERROR;
    }   
}


/**
* @brief Read an array of integers from a file.
*
* This function reads an array of integers from the specified file and allocates memory for it.
*
* @param filename The name of the input file.
* @param arr Pointer to the array.
* @param end_arr Pointer to the end of the array.
* @return OK if successful, or an error code (INPUT_FILE_ERROR, MEMORY_ERROR, or READ_ERROR) on failure.
*/
int read_array(char *filename, int **arr, int **end_arr)
{
    FILE *src = fopen(filename, "r");
    if (src == NULL)
    {
        return INPUT_FILE_ERROR;
    }
    int n = amount_of_elements(src);
    // Rewind the file pointer to read again
    rewind(src);
    
    if (n <= 0)
    {
        fclose(src);
        return READ_ERROR;
    }
    // Allocate memory for the array
    *arr = malloc(n * sizeof(int));
    if (*arr == NULL)
    {
        fclose(src);
        return MEMORY_ERROR;
    }
    // Set the end pointer of the array
    *end_arr = *arr + n;
    for (int *ptr = *arr; ptr != *end_arr; ptr++)
    {
        // Read elements into the array
        if (fscanf(src, "%d", ptr) != 1)
        {
            fclose(src);
            free(*arr);
            return READ_ERROR;
        }
    }

    fclose(src);
    return OK;
}

/**
* @brief Print an array of integers to a file.
*
* This function prints an array of integers to the specified output file.
*
* @param filename The name of the output file.
* @param arr Pointer to the start of the array.
* @param arr_end Pointer to the end of the array.
* @return OK if successful, or OUTPUT_FILE_ERROR on failure.
*/
int file_print_array(char *filename, int *arr, int *arr_end)
{
    int check = OK;
    FILE *f_dst = fopen(filename, "w");
    
    if (f_dst == NULL)
    {
        return OUTPUT_FILE_ERROR;
    }
    for (int *p = arr; p < arr_end; p++)
    {
        if (p != arr)
        {    
            fprintf(f_dst, " ");
        }
        // Print each element to the file
        fprintf(f_dst, "%d", *p);
    }
    // Print a newline character
    fprintf(f_dst, "\n");
    fclose(f_dst);
    
    return check;
}
/**
* @brief Free dynamically allocated memory for an array.
*
* This function frees the memory allocated for an array and sets the pointers to NULL.
*
* @param arr Pointer to the start of the array.
* @param end_arr Pointer to the end of the array.
*/
void free_array(int *arr, int *end_arr)
{
    free(arr);
    arr = NULL;
    end_arr++;
    end_arr = NULL;
}


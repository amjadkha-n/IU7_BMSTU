#include <stdio.h>
#include <stdlib.h>
#include "../inc/check_main.h"

/**
* @brief Count the number of elements in a file.
*
* This function counts the number of integer elements in the given file.
*
* @param src The input file.
* @return The number of elements if successful, OK if the file is empty, or READ_ERROR on failure.
*/
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
* @brief Find the last negative element in an array.
*
* This function searches for the last negative element in the given array.
*
* @param arr Pointer to the start of the array.
* @param end_arr Pointer to the end of the array.
* @return Pointer to the last negative element or end_arr if no negative elements are found.
*/
const int *find_last_neg(const int *arr, const int *end_arr)
{
    // Start from the end of the array
    const int *ptr = end_arr - 1;
    // Find the last negative element
    while (ptr >= arr && *ptr >= 0)
    {
        ptr--;
    }
    if (ptr < arr)
    {
        // If no negative elements found, set pointer to end
        ptr = end_arr;
    }
    return ptr;
}
/**
* @brief Filter out non-negative elements from an array.
*
* This function creates a new array containing only the non-negative elements from the input array.
*
* @param pb_src Pointer to the start of the source array.
* @param pe_src Pointer to the end of the source array.
* @param pb_dst Pointer to the start of the destination array.
* @param pe_dst Pointer to the end of the destination array.
* @return OK if successful or KEY_ERROR on failure.
*/
int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || pb_src >= pe_src || pb_dst == NULL || pe_dst == NULL)
    {
        return KEY_ERROR;
    }
    const int *last_neg = find_last_neg(pb_src, pe_src);
    // Calculate the number of non-negative elements
    int n = last_neg - pb_src;

    if (n <= 0)
    {
        return KEY_ERROR;
    }
    // Allocate memory for the new array
    *pb_dst = malloc(n * sizeof(int));
    if (*pb_dst == NULL)
    {
        return KEY_ERROR;
    }
    int *current_dst = *pb_dst;
    const int *current_src = pb_src;
    // Calculate a pointer to the end of the source array
    const int *p_end = pb_src + n;    

    while (current_src != p_end)
    {
        // Copy non-negative elements
        *(current_dst++) = *(current_src++);
    }
    *pe_dst = current_dst;

    return OK;
}
/**
* @brief Compare two integers.
*
* This function compares two integers and returns 1 if the first is greater, -1 if the second is greater, or 0 if they are equal.
*
* @param p_1 Pointer to the first integer.
* @param p_2 Pointer to the second integer.
* @return 1 if the first integer is greater, -1 if the second is greater, or 0 if they are equal.
*/
int compare(const void *p_1, const void *p_2)
{
    int check;
    const int *p_int_1 = p_1;
    const int *p_int_2 = p_2;
    if (*p_int_1 > *p_int_2)
    {
        check = 1;
    }
    else if (*p_int_1 < *p_int_2)
    {
        check = -1;
    }
    else
    {
        check = 0;
    }
    return check;
}
/**
* @brief Swap two memory regions.
*
* This function swaps the contents of two memory regions of the specified size.
*
* @param a Pointer to the first memory region.
* @param b Pointer to the second memory region.
* @param size Size of each element in the memory regions.
*/
void swap(void *a, void *b, size_t size)
{
    char *a_ptr = a;
    char *b_ptr = b;
    char t;
    // Initialize a counter for bytes swapped
    size_t i = 0;

    while (i < size)
    {
        t = *a_ptr;
        // Swap the bytes at a and b
        *a_ptr = *b_ptr;
        *b_ptr = t;
        // Move to the next byte in a
        a_ptr++;
        // Move to the next byte in b
        b_ptr++;
        // Increment the byte counter
        i++;
    }
}

/**
* @brief Sort an array using the bubble sort algorithm.
*
* This function sorts an array using the bubble sort algorithm with the provided comparison function.
*
* @param base Pointer to the start of the array.
* @param nmemb Number of elements in the array.
* @param size Size of each element in the array.
* @param compar Comparison function for elements.
*/
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*))
{
    // Create a pointer to the beginning of the array
    char *base_beg = base;
    // Create a pointer to the end of the array
    char *base_end = base_beg + nmemb * size;
    
    for (char *ptr_i = base_beg; ptr_i < base_end - size; ptr_i += size)
    {
        for (char *ptr_j = base_beg; ptr_j < base_end - size; ptr_j += size)
        {
            // Compare adjacent elements using compar function
            if (compar(ptr_j, ptr_j + size) > 0)
            {
                // Swap elements if out of order
                swap(ptr_j, ptr_j + size, size); 
            }
        }
    }
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

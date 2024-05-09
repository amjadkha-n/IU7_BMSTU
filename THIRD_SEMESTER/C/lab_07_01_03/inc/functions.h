#include <stdlib.h>

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
int read_array(char *filename, int **arr, int **end_arr);

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
int key(const int *pb_src, const int *pe_arr, int **pb_dst, int **pe_dst);

/**
* @brief Compare two integers.
*
* This function compares two integers and returns 1 if the first is greater, -1 if the second is greater, or 0 if they are equal.
*
* @param p_1 Pointer to the first integer.
* @param p_2 Pointer to the second integer.
* @return 1 if the first integer is greater, -1 if the second is greater, or 0 if they are equal.
*/
int compare(const void *p_1, const void *p_2);

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
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

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
int file_print_array(char *filename, int *arr, int *arr_end);

/**
* @brief Free dynamically allocated memory for an array.
*
* This function frees the memory allocated for an array and sets the pointers to NULL.
*
* @param arr Pointer to the start of the array.
* @param end_arr Pointer to the end of the array.
*/
void free_array(int *arr, int *end_arr);


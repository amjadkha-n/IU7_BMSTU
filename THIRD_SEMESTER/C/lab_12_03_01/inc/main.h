#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <dlfcn.h>
/**
 * @def OK
 * @brief The operation was successful.
 */
#define OK 0

/**
 * @def ARG_ERROR
 * @brief An error occurred due to invalid function arguments.
 */
#define ARG_ERROR -1

/**
 * @def INPUT_FILE_ERROR
 * @brief An error occurred while opening or accessing an input file.
 */
#define INPUT_FILE_ERROR -2

/**
 * @def READ_ERROR
 * @brief An error occurred while reading data.
 */
#define READ_ERROR -3

/**
 * @def MEMORY_ERROR
 * @brief An error occurred due to memory allocation failure.
 */
#define MEMORY_ERROR -4

/**
 * @def KEY_ERROR
 * @brief An error occurred during a key operation.
 */
#define KEY_ERROR -5

/**
 * @def OUTPUT_FILE_ERROR
 * @brief An error occurred while opening or accessing an output file.
 */
#define OUTPUT_FILE_ERROR -6

#define CAN_NOT_OPEN_LIBRARY -10
#define CAN_NOT_LOAD_FUNCTION -11
#define DIFFERENT_LENGTH_OF_ARRAYS -12

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
int amount_of_elements(FILE *src);
int are_arguments_valid(int argc, char **argv);
int are_arguments_for_filter(int argc, char **argv);

int read_array(char *filename, int **arr, int **end_arr);
const int *find_last_neg(const int *arr, const int *end_arr);
int file_print_array(char *filename, int *arr, int *arr_end);
void free_array(int *arr, int *end_arr);

int compare(const void *p_1, const void *p_2);
void swap(void *a, void *b, size_t size);
void mysort(void *base, size_t nmemb, size_t size, int (*compar)(const void*, const void*));

typedef int (*fn_key_t)(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif

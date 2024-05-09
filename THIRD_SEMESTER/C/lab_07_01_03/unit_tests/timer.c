#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "../inc/check_main.h"
#include "../inc/arguments.h"
#include "../inc/functions.h"

/**
 * @file
 * @brief This file contains the main function for measuring the execution time of mysort and qsort functions.
 */

/**
 * @brief Measure the execution time of a sorting function.
 *
 * This function measures the execution time of a sorting function and prints the result in microseconds.
 *
 * @param arr Pointer to the beginning of the array to be sorted.
 * @param end_arr Pointer to the end (exclusive) of the array to be sorted.
 * @param mysort Pointer to the sorting function to be measured.
 */
void measure_time(int *arr, int *end_arr, \
void (*mysort)(void *, size_t, size_t, int (*compar)(const void*, const void*)))
{
    int64_t time;
    struct timeval tv_start, tv_stop;
    gettimeofday(&tv_start, NULL);
    mysort(arr, end_arr - arr, sizeof(int), compare);
    gettimeofday(&tv_stop, NULL);
    time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("time = %ld mcs\n", time);
}
/**
 * @brief The main function of the program.
 *
 * This function serves as the entry point for the program. It reads an array of integers from a file,
 * measures the execution time of both the custom 'mysort' function and the standard 'qsort' function,
 * and prints the execution times to the standard output.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return Returns OK (0) if the program executes successfully, or ARG_ERROR (-1) if there is an error.
 */
int main(int argc, char **argv)
{
    int *arr_1 = NULL, *end_arr_1 = NULL;
    int *arr_2 = NULL, *end_arr_2 = NULL;
    int check = (argc != 2 || read_array(argv[1], &arr_1, &end_arr_1) || read_array(argv[1], &arr_2, &end_arr_2));
    if (check == OK)
    {
        printf("mysort: ");
        measure_time(arr_1, end_arr_1, mysort);
        printf("qsort: ");
        measure_time(arr_2, end_arr_2, qsort); 
    }
    else
        check = ARG_ERROR;
    free_array(arr_1, end_arr_1);
    free_array(arr_2, end_arr_2);
    return check;
}



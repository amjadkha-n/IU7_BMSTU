/**
 * @file matrix_in_out.h
 * @brief Matrix input/output functions and related declarations.
 *
 * This header file provides function declarations for matrix input/output and related operations.
 */

#ifndef MATRIX_IN_OUT_H_
#define MATRIX_IN_OUT_H_

#include "matrix.h"

/**
 * @brief Read and load matrices from standard input.
 *
 * This function reads and loads two matrices from standard input into the provided matrix structures.
 * It returns an error code if any issues occur during input.
 *
 * @param a Pointer to the first matrix structure.
 * @param b Pointer to the second matrix structure.
 * @return An error code indicating the success or failure of the operation.
 */
int read_and_load_matrices(matrix_t *a, matrix_t *b);

/**
 * @brief Allocate a two-dimensional matrix.
 *
 * This function allocates memory for a two-dimensional matrix with the given number of rows and columns.
 *
 * @param n The number of rows.
 * @param m The number of columns.
 * @return A pointer to the allocated matrix, or NULL in case of memory allocation failure.
 */
long long int **allocate_matrix(int n, int m);

/**
 * @brief Display the contents of a matrix.
 *
 * This function prints the elements of a matrix to the standard output.
 *
 * @param matrix The matrix to be displayed.
 */
void display_result(matrix_t matrix);

/**
 * @brief Free memory associated with matrix structures.
 *
 * This function frees the memory associated with one or more matrix structures.
 *
 * @param a Pointer to the first matrix structure.
 * @param b Pointer to the second matrix structure.
 * @param c Pointer to an additional matrix structure.
 */
void free_all_matrixes(matrix_t *a, matrix_t *b, matrix_t *c);

#endif

#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>
#include "my_time.h"

#define ALLOC_ERROR 2
#define DIFFERENT_SIZE 5

typedef struct
{
    int **data;   /**< 2D array to store matrix elements. */
    size_t nrows;  /**< Number of rows in the matrix. */
    size_t ncols;  /**< Number of columns in the matrix. */
} matrix_t;

/**
 * @brief Frees the memory allocated for a matrix.
 *
 * Frees the memory allocated for the 2D array storing matrix elements.
 *
 * @param matrix Pointer to the matrix to be freed.
 */
void matrix_free(matrix_t *matrix);

/**
 * @brief Outputs the elements of a matrix to the standard output.
 *
 * Outputs the elements of the matrix to the standard output,
 * separated by spaces and organized in rows and columns.
 *
 * @param matrix Pointer to the matrix to be output.
 */
void matrix_output(matrix_t *matrix);

/**
 * @brief Adds two matrices and stores the result in another matrix.
 *
 * Adds two matrices and stores the result in the matrix_res.
 * Returns ALLOC_ERROR if memory allocation fails, DIFFERENT_SIZE if
 * the matrices have different dimensions, and EXIT_SUCCESS otherwise.
 *
 * @param matrix_res Pointer to the result matrix.
 * @param matrix_1   Pointer to the first matrix.
 * @param matrix_2   Pointer to the second matrix.
 * @return An integer code indicating the operation result.
 */
int matrices_add(matrix_t *matrix_res, matrix_t *matrix_1, matrix_t *matrix_2);

/**
 * @brief Allocates memory for a matrix.
 *
 * Allocates memory for the 2D array storing matrix elements based on the
 * specified number of rows and columns.
 *
 * @param matrix Pointer to the matrix structure.
 * @return An integer code indicating the operation result.
 */
int matrix_alloc(matrix_t *matrix);

/**
 * @brief Measures the time taken to add two matrices.
 *
 * Measures the time taken to add two matrices (matrix_1 and matrix_2)
 * and stores the result in matrix_res. The time is returned in the 'time' parameter.
 *
 * @param time       Pointer to store the time taken for the operation.
 * @param matrix_res Pointer to the result matrix.
 * @param matrix_1   Pointer to the first matrix.
 * @param matrix_2   Pointer to the second matrix.
 * @return An integer code indicating the operation result.
 */
int time_matrices_add(microsecond_t *time, matrix_t *matrix_res, matrix_t *matrix_1, matrix_t *matrix_2);

/**
 * @brief Calculates the size of a matrix in bytes.
 *
 * Calculates the size of a matrix in bytes based on the number of rows and columns
 * and the size of the data type (int) used to store matrix elements.
 *
 * @param matrix Pointer to the matrix structure.
 * @return The size of the matrix in bytes.
 */
size_t matrix_size(matrix_t *matrix);

#endif  // MATRIX_OPERATIONS_H
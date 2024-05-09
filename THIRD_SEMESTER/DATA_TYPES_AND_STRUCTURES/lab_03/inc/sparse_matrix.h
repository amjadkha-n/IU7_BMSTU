/**
 * @file sparse_matrix.h
 * @brief Sparse matrix operations and related definitions.
 */
#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <stdio.h>

#include "matrix.h"
#include "my_time.h"

#define INCORRECT_INPUT 1

#define EXISTING_ELEMENT_ERROR 3
#define INVALID_FILE 4
#ifndef MATRIX_H
#define DIFFERENT_SIZE 5
#define ALLOC_ERROR 2
#endif

/**
 * @struct sparse_matrix_t
 * @brief Structure to represent a sparse matrix.
 */
typedef struct
{
    size_t nrows;   /**< Number of rows in the matrix. */
    size_t ncols;   /**< Number of columns in the matrix. */
    size_t nelems;  /**< Number of non-zero elements in the matrix. */
    
    int *A;         /**< Array to store non-zero elements. */
    size_t *IA;     /**< Array to store row indices of non-zero elements. */
    size_t *JA;     /**< Array to store column indices of non-zero elements. */
} sparse_matrix_t;

/**
 * @brief Reads a sparse matrix from the standard input.
 *
 * Reads the number of rows, columns, and non-zero elements of a sparse matrix
 * from the standard input, and allocates memory for the sparse matrix.
 *
 * @param sparse_matrix Pointer to the sparse matrix structure.
 * @return An integer code indicating the operation result.
 */
int sparse_matrix_input(sparse_matrix_t *sparse_matrix);

/**
 * @brief Allocates memory for a sparse matrix.
 *
 * Allocates memory for the arrays used to store non-zero elements, row indices,
 * and column indices of a sparse matrix based on the number of non-zero elements.
 *
 * @param sparse_matrix Pointer to the sparse matrix structure.
 * @return An integer code indicating the operation result.
 */
int sparse_matrix_alloc(sparse_matrix_t *sparse_matrix);

/**
 * @brief Frees the memory allocated for a sparse matrix.
 *
 * Frees the memory allocated for the arrays used to store non-zero elements, row indices,
 * and column indices of a sparse matrix.
 *
 * @param sparse_matrix Pointer to the sparse matrix structure.
 */
void sparse_matrix_free(sparse_matrix_t *sparse_matrix);

/**
 * @brief Converts a sparse matrix to a dense matrix.
 *
 * Converts a sparse matrix to a dense matrix and stores the result in the matrix structure.
 *
 * @param matrix        Pointer to the result matrix.
 * @param sparse_matrix Pointer to the sparse matrix to be converted.
 * @return An integer code indicating the operation result.
 */
int sparse_matrix_to_matrix(matrix_t *matrix, sparse_matrix_t *sparse_matrix);

/**
 * @brief Reads a sparse matrix from a file.
 *
 * Reads the number of rows, columns, and non-zero elements of a sparse matrix
 * from a file, and allocates memory for the sparse matrix.
 *
 * @param sparse_matrix Pointer to the sparse matrix structure.
 * @param f             Pointer to the file from which to read the matrix.
 * @return An integer code indicating the operation result.
 */
int sparse_matrix_fscan(sparse_matrix_t *sparse_matrix, FILE *f);

/**
 * @brief Adds two sparse matrices and stores the result in another sparse matrix.
 *
 * Adds two sparse matrices and stores the result in the matrix_res.
 * Returns DIFFERENT_SIZE if the matrices have different dimensions, ALLOC_ERROR if
 * memory allocation fails, and EXIT_SUCCESS otherwise.
 *
 * @param matrix_res Pointer to the result sparse matrix.
 * @param matrix_1   Pointer to the first sparse matrix.
 * @param matrix_2   Pointer to the second sparse matrix.
 * @return An integer code indicating the operation result.
 */
int sparse_matrices_add(sparse_matrix_t *matrix_res, sparse_matrix_t *matrix_1, sparse_matrix_t *matrix_2);

/**
 * @brief Measures the time taken to add two sparse matrices.
 *
 * Measures the time taken to add two sparse matrices (matrix_1 and matrix_2)
 * and stores the result in matrix_res. The time is returned in the 'time' parameter.
 *
 * @param time       Pointer to store the time taken for the operation.
 * @param matrix_res Pointer to the result sparse matrix.
 * @param matrix_1   Pointer to the first sparse matrix.
 * @param matrix_2   Pointer to the second sparse matrix.
 * @return An integer code indicating the operation result.
 */
int time_sparse_matrices_add(microsecond_t *time, sparse_matrix_t *matrix_res, sparse_matrix_t *matrix_1, sparse_matrix_t *matrix_2);

/**
 * @brief Outputs the elements of a sparse matrix to the standard output.
 *
 * Outputs the non-zero elements, row indices, and column indices of a sparse matrix
 * to the standard output.
 *
 * @param sparse_matrix Pointer to the sparse matrix to be output.
 */
void sparse_matrix_output(sparse_matrix_t *sparse_matrix);

/**
 * @brief Calculates the size of a sparse matrix in bytes.
 *
 * Calculates the size of a sparse matrix in bytes based on the number of non-zero elements,
 * the size of the data type (int), and the sizes of the arrays used to store row and column indices.
 *
 * @param sparse_matrix Pointer to the sparse matrix structure.
 * @return The size of the sparse matrix in bytes.
 */
size_t sparse_matrix_size(sparse_matrix_t *sparse_matrix);

#endif  // SPARSE_MATRIX_H
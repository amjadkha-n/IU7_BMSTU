/**
 * @file operations.h
 * @brief Matrix operations and related function declarations.
 *
 * This header file provides function declarations for various matrix operations and manipulations.
 */

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include "matrix.h"

/**
 * @brief Trim both matrices to square shape.
 *
 * This function trims both matrices to a square shape if they have different numbers of rows and columns.
 * It returns an error code if any issues occur during the operation.
 *
 * @param a Pointer to the first matrix structure.
 * @param b Pointer to the second matrix structure.
 * @return An error code indicating the success or failure of the operation.
 */
int trim_matrices(matrix_t *a, matrix_t *b);

/**
 * @brief Make matrices even-sized squares.
 *
 * This function ensures that both matrices are even-sized squares by padding them with zeros.
 * It returns an error code if any issues occur during the operation.
 *
 * @param a Pointer to the first matrix structure.
 * @param b Pointer to the second matrix structure.
 * @return An error code indicating the success or failure of the operation.
 */
int make_matrices_even(matrix_t *a, matrix_t *b);

/**
 * @brief Multiply two matrices and store the result.
 *
 * This function multiplies two input matrices 'a' and 'b' and stores the result in the provided matrix 'c'.
 * It returns an error code if any issues occur during the operation.
 *
 * @param a First matrix to be multiplied.
 * @param b Second matrix to be multiplied.
 * @param c Pointer to the resulting matrix structure.
 * @return An error code indicating the success or failure of the operation.
 */

int multiply_and_store_matrices(matrix_t a, matrix_t b, matrix_t *c);

/**
 * @brief Trim a matrix to square shape.
 *
 * This function trims a matrix to a square shape by removing rows or columns as needed.
 * It returns an error code if any issues occur during the operation.
 *
 * @param matrix Pointer to the matrix structure to be trimmed.
 * @return An error code indicating the success or failure of the operation.
 */

int trim_matrix(matrix_t *matrix);

/**
 * @brief Trim a matrix by removing rows to make it square.
 *
 * This function removes rows from a matrix to make it square.
 * It returns an error code if any issues occur during the operation.
 *
 * @param matrix Pointer to the matrix structure to be trimmed.
 * @return An error code indicating the success or failure of the operation.
 */

int trim_matrix_by_rows(matrix_t *matrix);

/**
 * @brief Trim a matrix by removing columns to make it square.
 *
 * This function removes columns from a matrix to make it square.
 * It returns an error code if any issues occur during the operation.
 *
 * @param matrix Pointer to the matrix structure to be trimmed.
 * @return An error code indicating the success or failure of the operation.
 */

int trim_matrix_by_columns(matrix_t *matrix);

/**
 * @brief Find the row with the minimum sum in a matrix.
 *
 * This function finds the row in a matrix with the minimum sum of its elements.
 * It returns the index of the row with the minimum sum.
 *
 * @param matrix Pointer to the matrix structure to search.
 * @return The index of the row with the minimum sum.
 */

int find_row_with_minimum(matrix_t *matrix);

/**
 * @brief Shift matrix rows, removing a specific row.
 *
 * This function shifts matrix rows and removes a specific row indicated by the 'shift_index'.
 * The last row is filled with zeros after the shift.
 *
 * @param matrix Pointer to the matrix structure to be modified.
 * @param shift_index Index of the row to be removed.
 */

void shift_matrix_rows(matrix_t *matrix, int shift_index);

/**
 * @brief Convert a matrix to a square shape.
 *
 * This function converts a rectangular matrix to a square matrix by adding or removing rows or columns as needed.
 * It returns an error code if any issues occur during the operation.
 *
 * @param matrix Pointer to the matrix structure to be converted to a square shape.
 * @return An error code indicating the success or failure of the operation.
 */

int convert_matrix_to_square(matrix_t *matrix);

/**
 * @brief Find the column with the minimum sum in a matrix.
 *
 * This function finds the column in a matrix with the minimum sum of its elements.
 * It returns the index of the column with the minimum sum.
 *
 * @param matrix Pointer to the matrix structure to search.
 * @return The index of the column with the minimum sum.
 */

int find_column_with_minimum(matrix_t *matrix);

/**
 * @brief Shift matrix columns, removing a specific column.
 *
 * This function shifts matrix columns and removes a specific column indicated by the 'shift_index'.
 * The last column is filled with zeros after the shift.
 *
 * @param matrix Pointer to the matrix structure to be modified.
 * @param shift_index Index of the column to be removed.
 */

void shift_matrix_columns(matrix_t *matrix, int shift_index);

/**
 * @brief Expand a matrix to a specified size.
 *
 * This function expands a matrix to the specified size by adding rows and columns as needed.
 * It returns an error code if any issues occur during the operation.
 *
 * @param matrix Pointer to the matrix structure to be expanded.
 * @param size The desired size for the matrix.
 * @return An error code indicating the success or failure of the operation.
 */

int expand_to_size(matrix_t *matrix, int size);

/**
 * @brief Duplicate the contents of a square matrix.
 *
 * This function duplicates the contents of a square matrix from 'src' to 'dst'.
 *
 * @param dst Pointer to the destination matrix.
 * @param src Pointer to the source matrix to be duplicated.
 * @param size The size of the square matrix.
 */

void duplicate_square_matrix(long long int **dst, long long int **src, int size);

/**
 * @brief Fill matrix rows with computed values.
 *
 * This function fills additional rows of a matrix with computed values based on existing rows.
 * It calculates the column product and applies a mathematical operation to fill the new rows.
 *
 * @param matrix Pointer to the matrix structure to be modified.
 * @param old_size The original size of the matrix.
 * @param size The desired size of the matrix.
 */

void fill_matrix_rows(long long int **matrix, int old_size, int size);

/**
 * @brief Get the product of elements in a matrix column up to a specified row.
 *
 * This function calculates the product of elements in a matrix column up to a specified row index 'i'.
 *
 * @param matrix Pointer to the matrix structure.
 * @param i The row index up to which the product should be calculated.
 * @param j The column index for which the product should be calculated.
 * @return The product of elements in the column up to row 'i'.
 */

long long int get_column_product(long long int **matrix, int i, int j);

/**
 * @brief Fill matrix columns with computed values.
 *
 * This function fills additional columns of a matrix with computed values based on existing columns.
 * It calculates the maximum element of a row and replicates it to fill the new columns.
 *
 * @param matrix Pointer to the matrix structure to be modified.
 * @param old_size The original size of the matrix.
 * @param size The desired size of the matrix.
 */

void fill_matrix_columns(long long int **matrix, int old_size, int size);

/**
 * @brief Find the maximum element in a matrix row.
 *
 * This function finds the maximum element in a specified row of a matrix.
 *
 * @param matrix Pointer to the matrix structure.
 * @param i The row index in which to find the maximum element.
 * @param j The column up to which the maximum element should be found.
 * @return The maximum element in the row up to column 'j'.
 */

long long int find_max_of_row(long long int **matrix, int i, int j);

/**
 * @brief Multiply two square matrices and store the result.
 *
 * This function multiplies two square matrices 'first_matrix' and 'second_matrix' and stores the result in 'result'.
 *
 * @param first_matrix The first square matrix to be multiplied.
 * @param second_matrix The second square matrix to be multiplied.
 * @param result The resulting square matrix where the product is stored.
 * @param size The size of the square matrices.
 */

void matrix_multiply(long long int **first_matrix, long long int **second_matrix, long long int **result, int size);

#endif

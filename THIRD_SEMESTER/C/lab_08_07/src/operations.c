#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/matrix.h"
#include "../inc/constants.h"
#include "../inc/matrix_in_out.h"
#include "../inc/operations.h"
/**
 * @brief Trim two matrices to even dimensions.
 * 
 * This function trims two input matrices, removing excess rows and columns to ensure
 * that both matrices have the same even number of rows and columns. If both matrices
 * are successfully trimmed, it returns OK; otherwise, it returns an error code.
 * 
 * @param a A pointer to the first matrix structure to be trimmed.
 * @param b A pointer to the second matrix structure to be trimmed.
 * @return OK if both matrices are successfully trimmed, an error code otherwise.
 */
int trim_matrices(matrix_t *a, matrix_t *b)
{
    int check_a = trim_matrix(a);
    int check_b = trim_matrix(b);
    
    if (check_a == OK && check_b == OK)
    {
        return OK;
    } 
    else
    {
        return (check_a != OK) ? check_a : check_b;
    }
}

/**
 * @brief Trim a matrix to square dimensions.
 * 
 * This function trims the input matrix to square dimensions by either removing excess rows or
 * columns, ensuring that it has the same number of rows and columns. If the matrix is already
 * square, it returns OK; otherwise, it trims it and returns an error code.
 * 
 * @param matrix A pointer to the matrix structure to be trimmed.
 * @return OK if the matrix is successfully trimmed to square dimensions, an error code otherwise.
 */
int trim_matrix(matrix_t *matrix)
{
    if (matrix->n > matrix->m)
    {
        return trim_matrix_by_rows(matrix);
    } 
    else if (matrix->n < matrix->m) 
    {
        return trim_matrix_by_columns(matrix);
    } 
    else
    {
        return OK;  // Matrix is already square
    }
}

/**
 * @brief Trim a matrix by removing rows to make it square.
 * 
 * This function trims the input matrix by removing rows to make it square. If the matrix is already
 * square, it returns OK; otherwise, it removes rows, ensuring that it has the same number of rows
 * and columns. It finds and removes rows to achieve squareness while minimizing row removals.
 * 
 * @param matrix A pointer to the matrix structure to be trimmed by rows.
 * @return OK if the matrix is successfully trimmed to square dimensions, an error code otherwise.
 */
int trim_matrix_by_rows(matrix_t *matrix)
{
    if (matrix->n == matrix->m)
    {
        return OK;  // Matrix is already square
    }

    int removable_index = 0;
    while (matrix->n != matrix->m)
    {
        removable_index = find_row_with_minimum(matrix);
        shift_matrix_rows(matrix, removable_index);
        matrix->n -= 1;
    }
    
    return convert_matrix_to_square(matrix);
}

/**
 * @brief Find the row in the matrix with the minimum value sum.
 * 
 * This function iterates through the rows and columns of the input matrix to find the row
 * that has the minimum sum of values. It returns the index of the row with the minimum sum.
 * 
 * @param matrix A pointer to the matrix structure to search for the row with the minimum sum.
 * @return The index of the row with the minimum sum.
 */
int find_row_with_minimum(matrix_t *matrix)
{
    int result = 0;
    long long min = matrix->matrix[0][0];
    
    for (int i = 0; i < matrix->m; i++)
    {
        for (int j = 0; j < matrix->n; j++)
        {
            if (matrix->matrix[j][i] < min)
            {
                min = matrix->matrix[j][i];
                result = j;
            }
        }
    }
    
    return result;
}
/**
 * @brief Shift rows in a matrix to remove the row at a specific index.
 * 
 * This function shifts the rows in the matrix to remove the row at the specified index. 
 * It moves the rows below the specified index upwards to fill the gap, effectively removing 
 * the row at the given index.
 * 
 * @param matrix A pointer to the matrix structure to modify by shifting rows.
 * @param shift_index The index of the row to be removed by shifting rows.
 */
void shift_matrix_rows(matrix_t *matrix, int shift_index)
{
    for (int i = shift_index; i < matrix->n - 1; i++)
    {
        for (int j = 0; j < matrix->m; j++)
        {
            matrix->matrix[i][j] = matrix->matrix[i + 1][j];
        }
    }
    
    for (int j = 0; j < matrix->m; j++)
    {
        matrix->matrix[matrix->n - 1][j] = 0;
    }
}
/**
 * @brief Convert a matrix to a square matrix.
 * 
 * This function converts a non-square matrix to a square matrix by allocating new memory
 * for the square matrix and copying the elements from the original matrix.
 * 
 * @param matrix A pointer to the matrix structure to be converted to a square matrix.
 * 
 * @return An integer indicating the status of the conversion.
 * - OK: The matrix was successfully converted to a square matrix.
 * - MEMORY_ERROR: Memory allocation for the square matrix failed.
 */

int convert_matrix_to_square(matrix_t *matrix)
{
    if (matrix->n == matrix->m) 
    {
        return OK;  // Matrix is already square
    }

    int check = OK;
    long long int **square_matrix = allocate_matrix(matrix->n, matrix->n);
    
    if (square_matrix)
    {
        for (int i = 0; i < matrix->n; i++)
        {
            for (int j = 0; j < matrix->m; j++)
            {
                square_matrix[i][j] = matrix->matrix[i][j];
            }
        }

        free(matrix->matrix[0]);
        free(matrix->matrix);
        matrix->matrix = square_matrix;
    }
    else
    {
        check = MEMORY_ERROR;
    }

    return check;
}
/**
 * @brief Trim a matrix to a square shape by removing columns.
 * 
 * This function trims a matrix by removing columns to make it square.
 * It finds the column with the minimum sum of elements and removes it iteratively 
 * until the matrix becomes square.
 * 
 * @param matrix A pointer to the matrix structure to be trimmed by columns.
 * 
 * @return An integer indicating the status of the trimming operation.
 * - OK: The matrix was successfully trimmed to a square shape.
 * - MEMORY_ERROR: Memory allocation for the square matrix failed during the conversion.
 */
int trim_matrix_by_columns(matrix_t *matrix)
{
    if (matrix->n == matrix->m)
    {
        return OK;  // Matrix is already square
    }

    int removable_index = 0;
    while (matrix->n != matrix->m)
    {
        removable_index = find_column_with_minimum(matrix);
        shift_matrix_columns(matrix, removable_index);
        matrix->m -= 1;
    }
    
    return convert_matrix_to_square(matrix);
}
/**
 * @brief Find the column with the minimum sum of elements in a matrix.
 * 
 * This function identifies the column in the given matrix with the minimum sum of
 * elements. It iterates through the columns and calculates the sum for each, 
 * returning the index of the column with the smallest sum.
 * 
 * @param matrix A pointer to the matrix structure to search for the column.
 * 
 * @return An integer representing the index of the column with the minimum sum.
 */
int find_column_with_minimum(matrix_t *matrix)
{
    int result = 0;
    long long min = matrix->matrix[0][0];
    
    for (int i = 0; i < matrix->m; i++)
    {
        for (int j = 0; j < matrix->n; j++)
        {
            if (matrix->matrix[j][i] < min)
            {
                min = matrix->matrix[j][i];
                result = i;
            }
        }
    }
    
    return result;
}
/**
 * @brief Shift the columns in a matrix to remove the specified column.
 * 
 * This function shifts the columns of a matrix to remove the column at the specified
 * index. It shifts the elements to the left to close the gap created by removing the
 * specified column.
 * 
 * @param matrix A pointer to the matrix structure to perform column shifting.
 * @param shift_index The index of the column to be removed by shifting.
 */
void shift_matrix_columns(matrix_t *matrix, int shift_index)
{
    for (int i = 0; i < matrix->n; i++)
    {
        for (int j = shift_index; j < matrix->m - 1; j++)
        {
            matrix->matrix[i][j] = matrix->matrix[i][j + 1];
        }
    }
    
    for (int i = 0; i < matrix->n; i++)
    {
        matrix->matrix[i][matrix->m - 1] = 0;
    }
}
/**
 * @brief Make two matrices compatible in size.
 * 
 * This function ensures that two matrices are compatible in size by expanding one or both
 * matrices if needed. If one matrix is larger than the other, it is expanded to match the size
 * of the larger matrix.
 * 
 * @param a A pointer to the first matrix structure.
 * @param b A pointer to the second matrix structure.
 * @return Returns OK if the matrices are made compatible; otherwise, an error code.
 */
int make_matrices_even(matrix_t *a, matrix_t *b)
{
    int check_a = OK;
    int check_b = OK;

    if (a->n > b->n)
    {
        check_b = expand_to_size(b, a->n);
    }
    else if (a->n < b->m)
    {
        check_a = expand_to_size(a, b->n);
    }

    return (check_a != OK) ? check_a : check_b;
}
/**
 * @brief Expand a matrix to the specified size.
 * 
 * This function expands a given matrix to the specified size. If the matrix is already of the
 * desired size, no changes are made.
 * 
 * @param matrix A pointer to the matrix structure to expand.
 * @param size The target size to which the matrix should be expanded.
 * @return Returns OK if the matrix is successfully expanded; otherwise, an error code.
 */
int expand_to_size(matrix_t *matrix, int size)
{
    if (matrix->n == size)
    {
        return OK;
    }

    int check = OK;
    long long int **expanded_matrix = allocate_matrix(size, size);

    if (expanded_matrix)
    {
        duplicate_square_matrix(expanded_matrix, matrix->matrix, matrix->n);
        fill_matrix_rows(expanded_matrix, matrix->n, size);
        fill_matrix_columns(expanded_matrix, matrix->m, size);
        
        free(matrix->matrix[0]);
        free(matrix->matrix);
        
        matrix->n = size;
        matrix->m = size;
        matrix->matrix = expanded_matrix;
    }
    else
    {
        check = MEMORY_ERROR;
    }
    
    return check;
}

/**
 * @brief Duplicate the content of a square matrix.
 * 
 * This function duplicates the content of a source square matrix into a destination square matrix.
 * The source and destination matrices should have the same size.
 * 
 * @param dst A pointer to the destination square matrix.
 * @param src A pointer to the source square matrix.
 * @param size The size of the square matrices.
 */
void duplicate_square_matrix(long long int **dst, long long int **src, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            dst[i][j] = src[i][j];
        }
    }
}
/**
 * @brief Fill additional rows in a square matrix.
 * 
 * This function fills additional rows in a square matrix with calculated elements.
 * It calculates elements based on the product of columns and applies a mathematical formula.
 * 
 * @param matrix A pointer to the square matrix to be filled.
 * @param old_size The size of the original square matrix before filling.
 * @param size The size of the square matrix after filling.
 */
void fill_matrix_rows(long long int **matrix, int old_size, int size)
{
    for (int i = old_size; i < size; i++)
    {
        for (int j = 0; j < old_size; j++)
        {
            long long int element = get_column_product(matrix, i, j);
            element = (element < 0) ? -element : element;
            element = (long long int)floor(pow(element, 1.0 / i));
            matrix[i][j] = element;
        }
    }
}
/**
 * @brief Calculate the product of elements in a matrix column.
 * 
 * This function calculates the product of elements in a specific column of a matrix up to a specified row.
 * 
 * @param matrix A pointer to the matrix.
 * @param i The row up to which the column product is calculated.
 * @param j The column for which the product is calculated.
 * @return The product of elements in the specified column up to row `i`.
 */
long long int get_column_product(long long int **matrix, int i, int j)
{
    long long int result = 1;
    
    for (int index = 0; index < i; index++)
    {
        result *= matrix[index][j];
    }
    
    return result;
}
/**
 * @brief Fill matrix columns with maximum values from respective rows.
 * 
 * This function fills the columns of a matrix with the maximum values found in their respective rows.
 * It calculates the maximum value from row `i` and assigns it to column `j`.
 * 
 * @param matrix A pointer to the matrix.
 * @param old_size The original size of the matrix.
 * @param size The new size of the matrix.
 */
void fill_matrix_columns(long long int **matrix, int old_size, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = old_size; j < size; j++)
        {
            matrix[i][j] = find_max_of_row(matrix, i, j);
        }
    }
}
/**
 * @brief Find the maximum value in a specific row of the matrix.
 * 
 * This function searches for the maximum value in row `i` of the matrix.
 * It returns the maximum value found within the specified range of columns.
 * 
 * @param matrix A pointer to the matrix.
 * @param i The row index to search for the maximum value.
 * @param j The column index to specify the range for the maximum search.
 * @return The maximum value found within the specified range of columns in row `i`.
 */
long long int find_max_of_row(long long int **matrix, int i, int j)
{
    long long int max = matrix[i][0];
    
    for (int index = 0; index < j; index++)
    {
        if (matrix[i][index] > max)
        {
            max = matrix[i][index];
        }
    }
    
    return max;
}
/**
 * @brief Multiply matrices A and B and store the result in matrix C.
 * 
 * This function multiplies matrices A and B to produce a result matrix C,
 * which is stored in the provided matrix_t structure. The function also takes
 * parameters `p` and `y` to specify the number of power and multiplication operations.
 * 
 * @param a The first matrix to multiply (matrix A).
 * @param b The second matrix to multiply (matrix B).
 * @param c A pointer to the matrix_t structure to store the result (matrix C).
 * @return An integer representing the operation status:
 *         - OK if the operation succeeds.
 *         - POWER_ERROR if `p` or `y` are negative.
 *         - MEMORY_ERROR if memory allocation fails for intermediate matrices.
 */
int multiply_and_store_matrices(matrix_t a, matrix_t b, matrix_t *c)
{
    int p = 0, y = 0;
    int check = 0;
    check = scanf("%d%d", &p, &y);
    
    if (check != 2 || p < 0 || y < 0)
    {
        return POWER_ERROR;
    }

    long long int **result = allocate_matrix(a.n, a.n);
    long long int **tmp = allocate_matrix(a.n, a.n);

    if (!result || !tmp)
    {
        if (result)
        {
            free(result[0]);
            free(result);
        }
        if (tmp)
        {
            free(tmp[0]);
            free(tmp);
        }
        return MEMORY_ERROR;
    }

    for (int i = 0; i < a.n; i++)
    {
        result[i][i] = 1;
    }

    for (int i = 0; i < p; i++)
    {
        memset(tmp[0], 0, a.n * a.n * sizeof(int));
        duplicate_square_matrix(tmp, result, a.n);
        matrix_multiply(tmp, a.matrix, result, a.n);
    }

    for (int i = 0; i < y; i++)
    {
        memset(tmp[0], 0, a.n * a.n * sizeof(int));
        duplicate_square_matrix(tmp, result, a.n);
        matrix_multiply(tmp, b.matrix, result, a.n);
    }

    free(tmp[0]);
    free(tmp);
    tmp = NULL;
    c->n = a.n;
    c->m = a.n;
    c->matrix = result;
    
    return OK;
}
/**
 * @brief Multiply two square matrices and store the result in another matrix.
 * 
 * This function multiplies two square matrices, `first_matrix` and `second_matrix`,
 * to produce a result matrix, which is stored in the provided `result` matrix.
 * All matrices are assumed to be of the same square size specified by the `size` parameter.
 * 
 * @param first_matrix The first square matrix to be multiplied.
 * @param second_matrix The second square matrix to be multiplied.
 * @param result The matrix to store the result of the multiplication.
 * @param size The size (number of rows and columns) of the square matrices.
 */
void matrix_multiply(long long int **first_matrix, long long int **second_matrix, long long int **result, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            long long int sum = 0;
            
            for (int k = 0; k < size; k++)
            {
                sum += first_matrix[i][k] * second_matrix[k][j];
            }
            
            result[i][j] = sum;
        }
    }
}

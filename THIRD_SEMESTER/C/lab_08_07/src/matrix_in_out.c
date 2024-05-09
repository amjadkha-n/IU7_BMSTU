#include <stdio.h>
#include <stdlib.h>
#include "../inc/constants.h"
#include "../inc/matrix.h"
#include "../inc/matrix_in_out.h"

int scan_matrix(matrix_t *matrix);
int scan_elements(matrix_t *matrix);
void free_matrix(matrix_t *matrix);

/**
 * @brief Read and load matrices from input sources.
 * 
 * This function reads and loads two matrices, a and b, from input sources.
 * It calls the `scan_matrix` function to populate the matrices.
 * 
 * @param a Pointer to the matrix_t structure for matrix 'a'.
 * @param b Pointer to the matrix_t structure for matrix 'b'.
 * @return An error code indicating the success or failure of the operation.
 *         Returns OK if both matrices are successfully loaded; otherwise, an error code is returned.
 */
int read_and_load_matrices(matrix_t *a, matrix_t *b)
{
    int check_a = scan_matrix(a);
    int check_b = scan_matrix(b);

    return (check_a != OK) ? check_a : check_b;
}

/**
 * @brief Scan and load elements into a matrix from input source.
 * 
 * This function reads matrix dimensions and elements from the input source
 * and populates the provided matrix structure. It also checks for errors
 * related to size and memory allocation.
 * 
 * @param matrix Pointer to the matrix_t structure to store the scanned matrix.
 * @return An error code indicating the success or failure of the operation.
 *         Returns SIZE_ERROR if there are issues with size (dimensions),
 *         MEMORY_ERROR if memory allocation fails, or OK if the operation is successful.
 */
int scan_matrix(matrix_t *matrix)
{
    int n = 0, m = 0;
    int check = scanf("%d%d", &n, &m);

    if (check != 2 || n <= 0 || m <= 0)
    {
        return SIZE_ERROR;
    }

    matrix->n = n;
    matrix->m = m;
    matrix->matrix = allocate_matrix(matrix->n, matrix->m);

    if (!matrix->matrix) 
    {
        return MEMORY_ERROR;
    }

    check = scan_elements(matrix);

    if (check != OK)
    {
        free_matrix(matrix);
    }

    return check;
}
/**
 * @brief Scan and load elements into a matrix from input source.
 * 
 * This function reads and populates the elements of a matrix from the input source.
 * It checks for errors during element scanning and returns an error code if needed.
 * 
 * @param matrix Pointer to the matrix_t structure where elements will be stored.
 * @return An error code indicating the success or failure of the operation.
 *         Returns ELEMENTS_ERROR if there is an issue scanning matrix elements,
 *         or OK if the operation is successful.
 */
int scan_elements(matrix_t *matrix)
{
    int check = OK;
    int i, j;

    for (i = 0; i < matrix->n && check == OK; i++)
    {
        for (j = 0; j < matrix->m && check == OK; j++)
        {
            if (scanf("%lld", &(matrix->matrix[i][j])) != 1)
            {
                check = ELEMENTS_ERROR;
                break;
            }
        }
    }

    return check;
}

/**
 * @brief Allocate memory for a two-dimensional matrix.
 * 
 * This function allocates memory for a two-dimensional matrix of the specified
 * dimensions (rows and columns) and initializes the matrix elements to zero.
 * 
 * @param n Number of rows in the matrix.
 * @param m Number of columns in the matrix.
 * @return A pointer to the allocated matrix if successful, or NULL if memory
 *         allocation fails.
 */
long long int **allocate_matrix(int n, int m)
{
    long long int **ptrs = malloc(n * sizeof(long long int *));
    
    if (!ptrs)
    {
        return NULL;  // Return NULL if memory allocation fails.
    }

    long long int *data = calloc(n * m, sizeof(long long int));

    if (!data)
    {
        free(ptrs);
        return NULL;  // Clean up and return NULL if memory allocation fails.
    }

    for (int i = 0; i < n; i++)
    {
        ptrs[i] = data + i * m;
    }

    return ptrs;
}

/**
 * @brief Deallocate memory for a matrix and reset matrix structure.
 * 
 * This function deallocates the memory associated with a matrix and resets the
 * matrix structure, setting the number of rows and columns to zero and the matrix
 * pointer to NULL.
 * 
 * @param matrix A pointer to the matrix structure to be freed.
 */
void free_matrix(matrix_t *matrix)
{
    if (matrix->matrix != NULL)
    {
        free(matrix->matrix[0]);
        free(matrix->matrix);
    }
    matrix->n = 0;
    matrix->m = 0;
    matrix->matrix = NULL;
}
/**
 * @brief Display the contents of a matrix to the standard output.
 * 
 * This function prints the elements of a matrix to the standard output. It
 * formats the matrix with each row on a separate line, and elements within a row
 * are separated by space.
 * 
 * @param matrix The matrix to be displayed.
 */
void display_result(matrix_t matrix)
{
    for (int i = 0; i < matrix.n; i++)
    {
        printf("%lld", matrix.matrix[i][0]);

        for (int j = 1; j < matrix.m; j++)
        {
            printf(" %lld", matrix.matrix[i][j]);
        }

        printf("\n");
    }
}
/**
 * @brief Deallocate memory for all matrices and reset matrix structures.
 * 
 * This function deallocates the memory associated with multiple matrices and resets
 * their respective matrix structures, setting the number of rows and columns to zero
 * and the matrix pointers to NULL.
 * 
 * @param a A pointer to the first matrix structure to be freed.
 * @param b A pointer to the second matrix structure to be freed.
 * @param c A pointer to the third matrix structure to be freed.
 */
void free_all_matrixes(matrix_t *a, matrix_t *b, matrix_t *c)
{
    free_matrix(a);
    free_matrix(b);
    free_matrix(c);
}
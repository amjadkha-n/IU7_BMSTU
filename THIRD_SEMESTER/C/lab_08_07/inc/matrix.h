/**
 * @file matrix.h
 * @brief Define a matrix structure for the program.
 *
 * This header file defines a structure named "matrix_t" to represent matrices in the program.
 * The structure contains a two-dimensional matrix, the number of rows (n), and the number of columns (m).
 */

#ifndef MATRIX_H_
#define MATRIX_H_

/**
 * @brief Structure to represent a matrix.
 */
typedef struct
{
    /**
     * @brief A two-dimensional matrix represented as a pointer to an array of long long integers.
     */
    long long int **matrix;

    /**
     * @brief The number of rows in the matrix.
     */
    int n;

    /**
     * @brief The number of columns in the matrix.
     */
    int m;
} matrix_t;

#endif

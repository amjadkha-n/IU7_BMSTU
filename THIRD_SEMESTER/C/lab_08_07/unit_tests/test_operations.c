#include <stdio.h>
#include "../inc/matrix_in_out.h"
#include "../inc/operations.h"
#include "../inc/matrix.h"
/**
 * @brief Test function to check the trimming of square matrices.
 * 
 * This function tests the `trim_matrices` function by trimming the matrices `mat_1`
 * and `mat_2` and comparing the results with the expected matrices `matrix_1` and `matrix_2`.
 * It returns the number of errors found during the test.
 * 
 * @return The number of errors encountered during the test (0 if successful).
 */
int test_trim_matrices_squared()
{
    int error_amount = 0;
    long long matrix_1[3][3] = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 } };
    long long *m_1[3] = { matrix_1[0], matrix_1[1], matrix_1[2] };
    long long matrix_2[2][2] = { { 1, 2 }, { 3, 4 } };
    long long *m_2[2] = { matrix_2[0], matrix_2[1] };
    matrix_t mat_1 = { m_1, 3, 3 };
    matrix_t mat_2 = { m_2, 2, 2 };
    trim_matrices(&mat_1, &mat_2);

    // Check matrix_1 against mat_1
    for (int i = 0; i < mat_1.n; i++)
    {
        for (int j = 0; j < mat_1.m; j++)
        {
            if (mat_1.matrix[i][j] != matrix_1[i][j])
            {
                error_amount++;
            }
        }
    }

    // Check matrix_2 against mat_2
    for (int i = 0; i < mat_2.n; i++)
    {
        for (int j = 0; j < mat_2.m; j++)
        {
            if (mat_2.matrix[i][j] != matrix_2[i][j])
            {
                error_amount++;
            }
        }
    }

    if (error_amount != 0)
    {
        printf("cut_squared test failed!\n");
    }

    return error_amount;
}
/**
 * @brief Test function to check the trimming of non-square matrices.
 * 
 * This function tests the `trim_matrices` function by trimming the matrices `mat_1`
 * and `mat_2`, which are non-square matrices, and comparing the results with the expected
 * trimmed matrices. It returns the number of errors found during the test.
 * 
 * @return The number of errors encountered during the test (0 if successful).
 */
int test_trim_matrices_usual()
{
    int error_amount = 0;

    // Create and populate matrix m_1
    long long **m_1 = allocate_matrix(1, 3);
    m_1[0][0] = 0;
    m_1[0][1] = 1;
    m_1[0][2] = 2;

    // Create and populate matrix m_2
    long long **m_2 = allocate_matrix(3, 1);
    m_2[0][0] = 1;
    m_2[1][0] = 2;
    m_2[2][0] = 3;

    // Create matrix_t instances
    matrix_t mat_1 = { m_1, 1, 3 };
    matrix_t mat_2 = { m_2, 3, 1 };
    matrix_t mat = { NULL, 0, 0 };

    // Trim matrices
    trim_matrices(&mat_1, &mat_2);

    // Check mat_1
    if (mat_1.n != 1 || mat_1.m != 1 || mat_1.matrix[0][0] != 2)
    {
        error_amount++;
    }

    // Check mat_2
    if (mat_2.n != 1 || mat_2.m != 1 || mat_2.matrix[0][0] != 3)
    {
        error_amount++;
    }

    // Print a single error message if there are mismatches
    if (error_amount != 0)
    {
        printf("Error in cut_usual!\n");
    }

    // Free matrices
    free_all_matrixes(&mat_1, &mat_2, &mat);

    return error_amount;
}
/**
 * @brief Test function to check making matrices even (test case 1).
 * 
 * This function tests the `make_matrices_even` function by applying it to two matrices, `mat_1`
 * and `mat_2`, and checking if `mat_1` is expanded to match the dimensions of `mat_2`. It returns
 * the number of errors found during the test.
 * 
 * @return The number of errors encountered during the test (0 if successful).
 */
int test_even_matrices_usual_1()
{
    int error_amount = 0;

    // Create and populate matrix m_1
    long long **m_1 = allocate_matrix(1, 1);
    m_1[0][0] = 5;

    // Create and populate matrix m_2
    long long **m_2 = allocate_matrix(2, 2);
    m_2[0][0] = 1;
    m_2[0][1] = 2;
    m_2[1][0] = 3;
    m_2[1][1] = 4;

    // Create matrix_t instances
    matrix_t mat_1 = { m_1, 1, 1 };
    matrix_t mat_2 = { m_2, 2, 2 };
    matrix_t mat = { NULL, 0, 0 };

    // Make matrices even
    make_matrices_even(&mat_1, &mat_2);

    // Check mat_1
    if (mat_1.n != 2 || mat_1.m != 2 || mat_1.matrix[0][0] != 5 || mat_1.matrix[0][1] != 5 || mat_1.matrix[1][0] != 5 || mat_1.matrix[1][1] != 5)
    {
        error_amount++;
        printf("Error in even_usual_1!\n");
    }

    // Free matrices
    free_all_matrixes(&mat_1, &mat_2, &mat);

    return error_amount;
}
/**
 * @brief Test function to check making matrices even (test case 2).
 * 
 * This function tests the `make_matrices_even` function by applying it to two matrices, `mat_1`
 * and `mat_2`, and checking if `mat_2` is expanded to match the dimensions of `mat_1`. It returns
 * the number of errors found during the test.
 * 
 * @return The number of errors encountered during the test (0 if successful).
 */
int test_even_matrices_usual_2()
{
    int error_amount = 0;

    // Create and populate matrix m_2
    long long **m_2 = allocate_matrix(1, 1);
    m_2[0][0] = 5;

    // Create and populate matrix m_1
    long long **m_1 = allocate_matrix(2, 2);
    m_1[0][0] = 1;
    m_1[0][1] = 2;
    m_1[1][0] = 3;
    m_1[1][1] = 4;

    // Create matrix_t instances
    matrix_t mat_1 = { m_1, 2, 2 };
    matrix_t mat_2 = { m_2, 1, 1 };
    matrix_t mat = { NULL, 0, 0 };

    // Make matrices even
    make_matrices_even(&mat_1, &mat_2);

    // Check mat_2
    if (mat_2.n != 2 || mat_2.m != 2 || mat_2.matrix[0][0] != 5 || mat_2.matrix[0][1] != 5 || mat_2.matrix[1][0] != 5 || mat_2.matrix[1][1] != 5)
    {
        error_amount++;
        printf("Error in even_usual_2!\n");
    }

    // Free matrices
    free_all_matrixes(&mat_1, &mat_2, &mat);

    return error_amount;
}

/**
 * @brief Test function to check making matrices even (complex test case 1).
 * 
 * This function tests the `make_matrices_even` function in a complex scenario by applying it to
 * two matrices, `mat_1` and `mat_2`. It checks if `mat_2` is expanded to match the dimensions of `mat_1`
 * and that elements of `mat_2` are filled according to the specified rules. It returns the number of
 * errors found during the test.
 * 
 * @return The number of errors encountered during the test (0 if successful).
 */
int test_even_matrices_complex_1()
{
    int error_amount = 0;

    // Create and populate matrix m_1
    long long **m_1 = allocate_matrix(3, 3);

    // Create and populate matrix m_2
    long long **m_2 = allocate_matrix(2, 2);
    m_2[0][0] = 1;
    m_2[0][1] = 2;
    m_2[1][0] = 3;
    m_2[1][1] = 4;

    // Create matrix_t instances
    matrix_t mat_1 = { m_1, 3, 3 };
    matrix_t mat_2 = { m_2, 2, 2 };
    matrix_t mat = { NULL, 0, 0 };

    // Make matrices even
    make_matrices_even(&mat_1, &mat_2);

    // Check mat_2
    if (mat_2.n != 3 || mat_2.m != 3 || mat_2.matrix[0][0] != 1 || mat_2.matrix[0][1] != 2 || mat_2.matrix[0][2] != 2 || 
        mat_2.matrix[1][0] != 3 || mat_2.matrix[1][1] != 4 || mat_2.matrix[1][2] != 4 || 
        mat_2.matrix[2][0] != 1 || mat_2.matrix[2][1] != 2 || mat_2.matrix[2][2] != 2)
    {
        error_amount++;
        printf("Error in even_complex_1!\n");
    }

    // Free matrices
    free_all_matrixes(&mat_1, &mat_2, &mat);

    return error_amount;
}
/**
 * @brief Test function to check making matrices even (complex test case 2).
 * 
 * This function tests the `make_matrices_even` function in a complex scenario by applying it to
 * two matrices, `mat_1` and `mat_2`. It checks if `mat_1` is expanded to match the dimensions of `mat_2`
 * and that elements of `mat_1` are filled according to the specified rules. It returns the number of
 * errors found during the test.
 * 
 * @return The number of errors encountered during the test (0 if successful).
 */
int test_even_matrices_complex_2()
{
    int error_amount = 0;

    // Create and populate matrix m_2
    long long **m_2 = allocate_matrix(3, 3);

    // Create and populate matrix m_1
    long long **m_1 = allocate_matrix(2, 2);
    m_1[0][0] = 1;
    m_1[0][1] = 2;
    m_1[1][0] = 3;
    m_1[1][1] = 4;

    // Create matrix_t instances
    matrix_t mat_2 = { m_2, 3, 3 };
    matrix_t mat_1 = { m_1, 2, 2 };
    matrix_t mat = { NULL, 0, 0 };

    // Make matrices even
    make_matrices_even(&mat_1, &mat_2);

    // Check mat_1
    if (mat_1.n != 3 || mat_1.m != 3 || mat_1.matrix[0][0] != 1 || mat_1.matrix[0][1] != 2 || mat_1.matrix[0][2] != 2 || 
        mat_1.matrix[1][0] != 3 || mat_1.matrix[1][1] != 4 || mat_1.matrix[1][2] != 4 || 
        mat_1.matrix[2][0] != 1 || mat_1.matrix[2][1] != 2 || mat_1.matrix[2][2] != 2)
    {
        error_amount++;
        printf("Error in even_complex_2!\n");
    }

    // Free matrices
    free_all_matrixes(&mat_1, &mat_2, &mat);

    return error_amount;
}
/**
 * @brief Test function to perform a series of matrix operations tests.
 * 
 * This function executes a series of tests on matrix operations, including trimming matrices, making matrices even,
 * and more. It accumulates the total number of errors encountered in these tests and returns the count.
 * 
 * @return The total number of errors encountered during the matrix operations tests.
 */
int test_operations(void)
{
    int error_amount = 0;
    error_amount += test_trim_matrices_squared();
    error_amount += test_trim_matrices_usual();
    error_amount += test_even_matrices_usual_1();
    error_amount += test_even_matrices_usual_2();
    error_amount += test_even_matrices_complex_1();
    error_amount += test_even_matrices_complex_2();
    return error_amount;
}
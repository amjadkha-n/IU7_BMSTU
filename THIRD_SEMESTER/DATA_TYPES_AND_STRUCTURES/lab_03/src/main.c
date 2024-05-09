
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/sparse_matrix.h"
#include "../inc/array.h"
#include "../inc/matrix.h"

#define FILE_OPEN_ERROR -1
/**
 * @brief Main function to perform operations on sparse matrices.
 *
 * This function allows users to input sparse matrices, perform various operations,
 * and display the results. It supports matrix input from both the keyboard and files.
 * Users can choose from options such as adding matrices, displaying the result,
 * measuring addition time, and analyzing memory usage.
 *
 * @return EXIT_SUCCESS on successful execution, error codes on failure.
 */
int main(void)
{
    sparse_matrix_t sparse_matrix_1, sparse_matrix_2;
    sparse_matrix_t sparse_matrix_res;
    matrix_t matrix_1, matrix_2;
    matrix_t matrix_res;

    sparse_matrix_t *sparse_matrix = &sparse_matrix_1;

    int choice;
    int rc;
    for (int i = 1; i <= 2; i++)
    {
        printf("Select the matrix input method №%d\n", i);
        printf("1. Reading from the keyboard.\n");
        printf("2. Reading from a file.\n");

        if (scanf("%d", &choice) != 1)
        {
            if (i == 2)
                sparse_matrix_free(&sparse_matrix_1);
            return INCORRECT_INPUT;
        }

        switch (choice)
        {
            case 1:
                rc = sparse_matrix_input(sparse_matrix);

                if (rc == INCORRECT_INPUT)
                {
                    printf("Incorrect input.\n");
                    if (i == 2)
                        sparse_matrix_free(&sparse_matrix_1);
                    return rc;
                }

                if (rc == ALLOC_ERROR)
                {
                    printf("Memory allocation error.\n");
                    if (i == 2)
                        sparse_matrix_free(&sparse_matrix_1);
                    return rc;
                }

                if (rc == EXISTING_ELEMENT_ERROR)
                {
                    printf("Error: an already entered element has been entered.\n");
                    if (i == 2)
                        sparse_matrix_free(&sparse_matrix_1);
                    return rc;
                }
                printf("Successfully!\n");
                break;

            case 2: // Чтение из файла
                printf("Enter the path to the file:\n");
                char filename[PATH_MAX];
                if (fgets(filename, sizeof(filename), stdin) == NULL)
                    ;
                if (fgets(filename, sizeof(filename), stdin) == NULL)
                {
                    printf("Input error.\n");
                    if (i == 2)
                        sparse_matrix_free(&sparse_matrix_1);
                    return INCORRECT_INPUT;
                }
                if (filename[strlen(filename) - 1] == '\n')
                    filename[strlen(filename) - 1] = '\0';
                
                FILE *f = fopen(filename, "r");
                if (f == NULL)
                {
                    printf("File opening error.\n");
                    if (i == 2)
                        sparse_matrix_free(&sparse_matrix_1);
                    return FILE_OPEN_ERROR;
                }

                rc = sparse_matrix_fscan(sparse_matrix, f);

                if (rc == INVALID_FILE)
                {
                    printf("The file is corrupted or empty.\n");
                    if (i == 2)
                        sparse_matrix_free(&sparse_matrix_1);
                    fclose(f);
                    return rc;
                }

                if (rc == ALLOC_ERROR)
                {
                    printf("Memory allocation error.\n");
                    if (i == 2)
                        sparse_matrix_free(&sparse_matrix_1);
                    fclose(f);
                    return rc;
                }
                
                if (rc == EXISTING_ELEMENT_ERROR)
                {
                    printf("Error: the same element is specified in the file several times.\n");
                    if (i == 2)
                        sparse_matrix_free(&sparse_matrix_1);
                    fclose(f);
                    return rc;
                }

                fclose(f);

                printf("Successfully!\n");

                #ifdef DEBUG
                sparse_matrix_output(sparse_matrix);
                #endif
                
                break;

            default:
                printf("Wrong choice.\n");
                if (i == 2)
                    sparse_matrix_free(&sparse_matrix_1);
                return INCORRECT_INPUT;
        }

    sparse_matrix = &sparse_matrix_2;
    }

    printf("Select an action:\n");
    printf("1. Add up the matrices and output as CSC.\n");
    printf("2. Add up the matrices and output in the form of CSC and in the form of a matrix.\n");
    printf("3. Output the matrix addition time in the form of CSC and in the form of a matrix.\n");
    printf("4. Output the amount of memory occupied by the matrices and their sum.\n");

    if (scanf("%d", &choice) != 1)
    {
        printf("Incorrect input.\n");
        return INCORRECT_INPUT;
    }

    switch (choice)
    {
        case 1:
            rc = sparse_matrices_add(&sparse_matrix_res, &sparse_matrix_1, &sparse_matrix_2);

            if (rc == DIFFERENT_SIZE)
            {
                sparse_matrix_free(&sparse_matrix_1);
                sparse_matrix_free(&sparse_matrix_2);
                printf("Error: the dimensions of the matrices do not match.\n");
                return rc;
            }

            if (rc == ALLOC_ERROR)
            {
                printf("Memory allocation error.\n");
                sparse_matrix_free(&sparse_matrix_1);
                sparse_matrix_free(&sparse_matrix_2);
                return rc;
            }

            printf("The result of addition:\n");
            sparse_matrix_output(&sparse_matrix_res);

            break;

        case 2:
            rc = sparse_matrices_add(&sparse_matrix_res, &sparse_matrix_1, &sparse_matrix_2);

            if (rc == DIFFERENT_SIZE)
            {
                sparse_matrix_free(&sparse_matrix_1);
                sparse_matrix_free(&sparse_matrix_2);
                printf("Error: the dimensions of the matrices do not match.\n");
                return rc;
            }

            if (rc == ALLOC_ERROR)
            {
                printf("Memory allocation error.\n");
                sparse_matrix_free(&sparse_matrix_1);
                sparse_matrix_free(&sparse_matrix_2);
                return rc;
            }

            rc = sparse_matrix_to_matrix(&matrix_res, &sparse_matrix_res);

            if (rc == ALLOC_ERROR)
            {
                printf("Memory allocation error.\n");
                sparse_matrix_free(&sparse_matrix_1);
                sparse_matrix_free(&sparse_matrix_2);
                sparse_matrix_free(&sparse_matrix_res);
                return rc;
            }

            printf("The result of addition:\n");
            sparse_matrix_output(&sparse_matrix_res);
            printf("\n");
            matrix_output(&matrix_res);

            matrix_free(&matrix_res);

            break;

        case 3:;
            microsecond_t time_cur;
            microsecond_t time_total_sparse = 0;
            microsecond_t time_total_std = 0;

            int count;
            printf("Enter the number of measurements: \n");
            if (scanf("%d", &count) != 1)
            {
                sparse_matrix_free(&sparse_matrix_1);
                sparse_matrix_free(&sparse_matrix_2);
                printf("Incorrect input.\n");
                return rc;
            }
            
            for (int i = 0; i < count; i++)
            {
                rc = time_sparse_matrices_add(&time_cur, &sparse_matrix_res, &sparse_matrix_1, &sparse_matrix_2);
                time_total_sparse += time_cur;

                if (rc == DIFFERENT_SIZE)
                {
                    sparse_matrix_free(&sparse_matrix_1);
                    sparse_matrix_free(&sparse_matrix_2);
                    printf("Error: the dimensions of the matrices do not match.\n");
                    return rc;
                }

                if (rc == ALLOC_ERROR)
                {
                    printf("Memory allocation error.\n");
                    sparse_matrix_free(&sparse_matrix_1);
                    sparse_matrix_free(&sparse_matrix_2);
                    return rc;
                }

                rc = sparse_matrix_to_matrix(&matrix_1, &sparse_matrix_1);
                if (rc == ALLOC_ERROR)
                {
                    printf("Memory allocation error.\n");
                    sparse_matrix_free(&sparse_matrix_1);
                    sparse_matrix_free(&sparse_matrix_2);
                    sparse_matrix_free(&sparse_matrix_res);
                    return rc;
                }

                rc = sparse_matrix_to_matrix(&matrix_2, &sparse_matrix_2);
                if (rc == ALLOC_ERROR)
                {
                    printf("Memory allocation error.\n");
                    sparse_matrix_free(&sparse_matrix_1);
                    sparse_matrix_free(&sparse_matrix_2);
                    sparse_matrix_free(&sparse_matrix_res);
                    matrix_free(&matrix_1);
                    return rc;
                }

                rc = time_matrices_add(&time_cur, &matrix_res, &matrix_1, &matrix_2);
                time_total_std += time_cur;
                if (rc == DIFFERENT_SIZE)
                {
                    printf("Error: the dimensions of the matrices do not match.\n");
                    sparse_matrix_free(&sparse_matrix_1);
                    sparse_matrix_free(&sparse_matrix_2);
                    sparse_matrix_free(&sparse_matrix_res);
                    matrix_free(&matrix_1);
                    matrix_free(&matrix_2);
                    return rc;
                }

                if (rc == ALLOC_ERROR)
                {
                    printf("Memory allocation error.\n");
                    sparse_matrix_free(&sparse_matrix_1);
                    sparse_matrix_free(&sparse_matrix_2);
                    sparse_matrix_free(&sparse_matrix_res);
                    matrix_free(&matrix_1);
                    matrix_free(&matrix_2);
                    return rc;
                }
            }

            printf("Addition time of sparse matrices: %"MSC" MKS.\n", time_total_sparse / count);
            printf("Addition time of standard matrices: %"MSC" MKS.\n", time_total_std / count);

            matrix_free(&matrix_1);
            matrix_free(&matrix_2);
            matrix_free(&matrix_res);

            break;

        case 4:
            rc = sparse_matrices_add(&sparse_matrix_res, &sparse_matrix_1, &sparse_matrix_2);

            if (rc == DIFFERENT_SIZE)
            {
                sparse_matrix_free(&sparse_matrix_1);
                sparse_matrix_free(&sparse_matrix_2);
                printf("Error: the dimensions of the matrices do not match.\n");
                return rc;
            }

            if (rc == ALLOC_ERROR)
            {
                printf("Memory allocation error.\n");
                sparse_matrix_free(&sparse_matrix_1);
                sparse_matrix_free(&sparse_matrix_2);
                return rc;
            }
            
            rc = sparse_matrix_to_matrix(&matrix_1, &sparse_matrix_1);
            if (rc == ALLOC_ERROR)
            {
                printf("Memory allocation error\n");
                sparse_matrix_free(&sparse_matrix_1);
                sparse_matrix_free(&sparse_matrix_2);
                sparse_matrix_free(&sparse_matrix_res);
                return rc;
            }

            rc = sparse_matrix_to_matrix(&matrix_2, &sparse_matrix_2);
            if (rc == ALLOC_ERROR)
            {
                printf("Memory allocation error.\n");
                sparse_matrix_free(&sparse_matrix_1);
                sparse_matrix_free(&sparse_matrix_2);
                sparse_matrix_free(&sparse_matrix_res);
                matrix_free(&matrix_1);
                return rc;
            }

            rc = matrices_add(&matrix_res, &matrix_1, &matrix_2);
            if (rc == DIFFERENT_SIZE)
            {
                printf("Error: the dimensions of the matrices do not match.\n");
                sparse_matrix_free(&sparse_matrix_1);
                sparse_matrix_free(&sparse_matrix_2);
                sparse_matrix_free(&sparse_matrix_res);
                matrix_free(&matrix_1);
                matrix_free(&matrix_2);
                return rc;
            }

            if (rc == ALLOC_ERROR)
            {
                printf("Memory allocation error.\n");
                sparse_matrix_free(&sparse_matrix_1);
                sparse_matrix_free(&sparse_matrix_2);
                sparse_matrix_free(&sparse_matrix_res);
                matrix_free(&matrix_1);
                matrix_free(&matrix_2);
                return rc;
            }

            printf("Memory occupied by the 1st matrix in sparse form: %zu bytes.\n", sparse_matrix_size(&sparse_matrix_1));;
            printf("The memory occupied by the 2nd matrix in sparse form: %zu bytes.\n", sparse_matrix_size(&sparse_matrix_2));
            printf("Memory occupied by the sum of matrices in sparse form: %zu bytes.\n", sparse_matrix_size(&sparse_matrix_res));
            printf("The memory occupied by the 1st and 2nd matrix and their sum in standard form: %zu bytes.\n", matrix_size(&matrix_res));

            matrix_free(&matrix_1);
            matrix_free(&matrix_2);
            matrix_free(&matrix_res);

            break;

        default:
            printf("Incorrect choice.\n");
            sparse_matrix_free(&sparse_matrix_1);
            sparse_matrix_free(&sparse_matrix_2);
            return INCORRECT_INPUT;
    }

    sparse_matrix_free(&sparse_matrix_1);
    sparse_matrix_free(&sparse_matrix_2);
    sparse_matrix_free(&sparse_matrix_res);

    return EXIT_SUCCESS;
}

# include <stdio.h>
# include <stdlib.h>

# define MAX_ROWS 10
# define MAX_COLS 10

int input_matrix(int mat[][MAX_COLS], int rows, int cols)
{
    //printf("Please enter the elements of the matrix: ");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (scanf("%d", &mat[i][j]) != 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

void matrix_sort_mult(int mat[][MAX_COLS], int rows, int cols)
{
    int min;
    for (int i = 0; i < rows; i++)
    {
        min = i;
        for (int j = i + 1; j < rows; j++)
        {
            int last = 1, next = 1;
            for (int k = 0; k < cols; k++)
            {
                last *= mat[min][k];
                next *= mat[j][k];
            }
            if (last > next)
            {
                min = j;
            }
        }
        for (int k = 0; k < cols; k++)
        {
            int temp = mat[min][k];
            mat[min][k] = mat[i][k];
            mat[i][k] = temp;
        }
    }
}

void print_matrix(int mat[][MAX_COLS], int rows, int cols)
{
    printf("Matrix after sorting: \n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%3d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int mat[MAX_ROWS][MAX_COLS];
    int rows, cols;

    //printf("Please enter the number of rows and columns: ");
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || rows > 10 || cols <= 0 || cols > 10)
    {
        printf("Error: Invalid input\n");
        return 1;
    }
    if (input_matrix(mat, rows, cols) == 1)
    {
        printf("Error: Invalid input\n");
        return 1;
    }

    matrix_sort_mult(mat, rows, cols);
    print_matrix(mat, rows, cols);
    return 0;
}

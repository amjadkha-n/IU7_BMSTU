# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>

# define MAX_ROWS 10
# define MAX_COLS 10

int input_matrix(int mat[][MAX_COLS], int rows, int cols)
{
    // printf("Please enter the elements of the square matrix: ");
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

int find_max_below_side_diag(int mat[][MAX_COLS], int rows, int cols)
{
    int max = INT_MIN;
    for (int i = 0 ; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (mat[i][j] % 10 == 5)
            {
                if (i + j > rows - 1 && abs(mat[i][j]) % 10 == 5 && mat[i][j] > max)
                {
                    max = mat[i][j];
                }
            }
            else if (i + j > rows - 1 && abs(mat[i][j]) % 10 == 5 && mat[i][j] > max)
            {
                max = mat[i][j];
            }
        }
    }
    if (max == INT_MIN || abs(max) % 10 != 5)
        return 1;
    else
        return max;
}
int main()
{
    int mat[MAX_ROWS][MAX_COLS];
    int rows, cols;

    // printf("Please enter the number of rows and columns of the square matrix: ");
    int input = scanf("%d %d", &rows, &cols);
    if (input != 2 || rows <= 0 || rows > 10 || cols <= 0 || cols > 10)
    {
        printf("Error: Invalid input\n");
        return 1;
    }
    if (rows != cols)
    {
        printf("Given matrix is not a square matrix\n");
        return 1;
    }
    if (input_matrix(mat, rows, cols) == 1)
    {
        printf("Error: Invalid input\n");
        return 1;
    }
    int max_num = find_max_below_side_diag(mat, rows, cols);
    if (max_num != 1)
    {
        printf("The maximum number that ends with five and is located below the side diagonal is: %d\n", max_num);
        return 0;
    }
    else
    {
        printf("No number found that meets the criteria\n");
        return 2;
    }
}

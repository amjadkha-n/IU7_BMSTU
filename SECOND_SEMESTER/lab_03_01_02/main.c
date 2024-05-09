#include <stdio.h>

#define MAX_ROWS 10
#define MAX_COLS 10

int input_matrix(int mat[][MAX_COLS], int rows, int cols)
{
    //printf("Enter matrix elements:\n", rows, cols);
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

int check_if_alternating(int mat[][MAX_COLS], int rows, int col)
{
    if (rows < 2)
        return 0;
    for (int i = 0; i < rows - 1; i++)
        if (i % 2 == 0 && !(mat[i][col] < 0 && mat[i + 1][col] > 0) && !(mat[i][col] > 0 && mat[i + 1][col] < 0))
            return 0;
        else if (i % 2 != 0 && !(mat[i][col] > 0 && mat[i + 1][col] < 0) && !(mat[i][col] < 0 && mat[i + 1][col] > 0))
            return 0;
    return 1;
}

void putting_values(int mat[][MAX_COLS], int arr[MAX_COLS], int rows, int cols)
{
    for (int j = 0; j < cols; j++)
    {
        if (check_if_alternating(mat, rows, j))
            arr[j] = 1;
        else
            arr[j] = 0;
    }
}

void print_array(int arr[], int cols)
{
    printf("Array:\n");
    for (int j = 0; j < cols; j++)
    {
        if (j < cols - 1)
            printf("%d ", arr[j]);
        else
            printf("%d", arr[j]);
    }
    printf("\n");
}

int main()
{
    int mat[MAX_ROWS][MAX_COLS];
    int arr[MAX_ROWS];
    int rows, cols;

    //printf("Enter the number of rows and columns of matrix (max %dx%d): ", MAX_ROWS, MAX_COLS);
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0 || rows > MAX_ROWS || cols > MAX_COLS)
    {
        printf("Error: Invalid input\n");
        return 1;
    }

    int check = input_matrix(mat, rows, cols);
    if (check == 1)
    {
        printf("Error: Invalid input\n");
        return 1;
    }
    putting_values(mat, arr, rows, cols);

    print_array(arr, cols);

    return 0;
}

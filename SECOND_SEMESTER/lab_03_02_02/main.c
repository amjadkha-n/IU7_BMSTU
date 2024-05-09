# include <stdio.h>
# include <stdlib.h>

# define MAX_ROWS 10
# define MAX_COLS 10

int input_matrix(int mat[][MAX_COLS], int rows, int cols)
{
    // printf("Please enter the elements of the matrix: ");
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

int sum_digits(int num)
{
    int sum = 0;
    num = abs(num);
    while (num > 0)
    {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int is_sum_digits_odd(int mat[MAX_COLS], int cols)
{
    int count = 0;
    int sum;
    for (int i = 0; i < cols; i++)
    {
        sum = sum_digits(mat[i]);
        if (sum % 2 != 0)
            count++;
    }
    return count;
}
void print_array(int mat[][MAX_COLS], int rows, int cols)
{
    printf("Modified matrix: \n");
    for (int i = 0; i < rows; i++)
    {
        if (i >= 0 && i < rows && (is_sum_digits_odd(mat[i], cols) >= 2))
        {
            for (int j = 0; j < cols; j++)
            {
                printf(" -1 ");
            }
            printf("\n");
        }
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
    // printf("Please enter the number of rows and columns: ");
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
    print_array(mat, rows, cols);
    return 0;
}

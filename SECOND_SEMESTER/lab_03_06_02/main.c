# include <stdio.h>

# define MAX_ROWS 10
# define MAX_COLS 10

void bull_move(int mat[][MAX_COLS], int rows, int cols)
{
    int num = 1;
    for (int j = 0; j < cols; j++)
    {
        for (int i = 0 ; i < rows; i++)
        {
            int ind_j = cols - 1 - j;
            int ind_i;

            if (j % 2 == 0)
            {
                ind_i = rows - 1 - i;
            }
            else
            {
                ind_i = i;
            }
            mat[ind_i][ind_j] = num;
            num++;
        }
    }
}
void print_matrix(int mat[][MAX_COLS], int rows, int cols)
{
    printf("Modified matrix:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%3d", mat[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int mat[MAX_ROWS][MAX_COLS];
    int rows, cols;

    //printf("Please enter the number of rows and columns of the matrix: ");
    if (scanf("%d %d", &rows, &cols) != 2 || rows <= 0 || rows > 10 || cols <= 0 || cols > 10)
    {
        printf("Error: Invalid input\n");
        return 1;
    }
    
    bull_move(mat, rows, cols);
    print_matrix(mat, rows, cols);

    return 0;
}

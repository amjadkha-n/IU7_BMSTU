# include <stdio.h>

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

int check_prime(int num)
{
    if (num < 2)
        return 0;
    for (int i = 2; i <= num / 2; i++)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}
void add_prime_in_arr(int mat[][MAX_COLS], int arr[MAX_ROWS + MAX_COLS], int rows, int cols, int *size)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (check_prime(mat[i][j])) 
            {
                arr[(*size)] = mat[i][j];
                (*size)++;
            }
        }
    }
}

void reverse_array(int arr[MAX_ROWS + MAX_COLS], int size)
{
    int temp = 0;
    for (int i = 0; i < size / 2; i++)
    {
        temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

void ret_val_to_mat(int mat[][MAX_COLS], int arr[MAX_ROWS + MAX_COLS], int rows, int cols)
{
    int k = 0; 
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (check_prime(mat[i][j]))
            {
                mat[i][j] = arr[k];
                k++;
            }
        }
    }
}

void print_matrix(int mat[][MAX_COLS], int rows, int cols)
{
    printf("Modified matrix: \n");
    for (int i = 0 ; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (j == cols - 1)
            {
                printf("%3d \n", mat[i][j]);
            }
            else
            {
                printf("%3d ", mat[i][j]);
            }
        }   
    }
}

int main()
{
    int mat[MAX_ROWS][MAX_COLS], arr[MAX_ROWS + MAX_COLS];

    int rows, cols, size = 0;
    // printf("Please enter the number of the rows and columns of the matirx: ");
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
    add_prime_in_arr(mat, arr, rows, cols, &size);
    if (size == 0)
    {
        printf("Array is empty\n");
        return 2;
    }
    reverse_array(arr, size);
    ret_val_to_mat(mat, arr, rows, cols);
    print_matrix(mat, rows, cols);

    return 0;
}

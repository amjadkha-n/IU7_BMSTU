#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 10

int read_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Error: Invalid input\n");
            return 1;
        }
    }
    return 0;
}

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int is_full_square(int num) 
{
    double root = sqrt(num);
    return (fabs(root - (int) root) < 1e-9);
}

int remove_full_squares(int arr[], int size)
{
    int new_size = size;
    int is_empty = 1;
    int has_squares = 0;

    for (int i = 0; i < new_size; i++)
    {
        if (is_full_square(arr[i]))
        {
            has_squares = 1;
            for (int j = i; j < new_size - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            new_size--;
            i--;
        }
        else
        {
            is_empty = 0;
        }
    }
    if (is_empty && !has_squares)
    {
        return 0;
    }
    else
    {
        return new_size;
    }
}

int main()
{
    int arr[MAX_SIZE];
    int n;

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SIZE)
    {
        printf("Error: Invalid input\n");
        return 1;
    }

    if (read_array(arr, n) != 0)
    {
        return 1;
    }

    int new_size = remove_full_squares(arr, n);
    if (new_size == 0)
    {
        printf("Array is empty\n");
        return 2;
    }
    else
    {
        printf("New array: ");
        print_array(arr, new_size);
    }
    
    return 0;
}

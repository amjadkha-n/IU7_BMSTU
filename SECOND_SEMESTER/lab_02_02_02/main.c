#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

int read_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int num = scanf("%d", &arr[i]);
        if (num != 1)
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

int is_same_first_and_last_digit(int num)
{
    num = abs(num);
    int first = num;
    while (first >= 10)
    {
        first /= 10;
    }
    return first == num % 10;
}

int print_result(int arr[], int size) 
{
    int new_arr[MAX_SIZE];
    int new_size = 0;

    for (int i = 0; i < size; i++)
    {
        if (is_same_first_and_last_digit(arr[i]))
        {
            new_arr[new_size] = arr[i];
            new_size++;
        }
    }

    printf("Result: ");
    if (new_size > 0)
    {
        print_array(new_arr, new_size);
    }
    else
    {
        printf("Array does not contain elements that start and end with the same digit.\n");
        return 1;
    }
    return 0;
}

int main()
{
    int arr[MAX_SIZE];
    int n;

    int count = scanf("%d", &n);

    if (count != 1 || n < 1 || n > MAX_SIZE)
    {
        printf("Error: Invalid number of elements\n");
        return 1;
    }
    if (read_array(arr, n) == 1)
    {
        return 1;
    }
    
    return print_result(arr, n);
}

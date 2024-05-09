#include <stdio.h>

#define MAX_SIZE 11

void input_array(int arr[], int *n) 
{
    for (*n = 0; *n < MAX_SIZE; (*n)++)
    {
        if (scanf("%d", &arr[*n]) != 1)
        {
            break;
        }
    }
}

void print_array(int arr[], int n)
{
    for (int i = 0; i < n; i++) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void selection_sort(int arr[], int n) 
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) 
    {
        min_idx = i;
        for (j = i + 1; j < n; j++) 
        {
            if (arr[j] < arr[min_idx]) 
            {
                min_idx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

int main() 
{
    int arr[MAX_SIZE];
    int n;

    input_array(arr, &n);
    if (n == 0)
    {
        printf("Error: Invalid input\n");
        return 1;
    }
    else if (n == MAX_SIZE) 
    {   
        n = n - 1;
        selection_sort(arr, n);
        printf("Overflow! array size exceeded\n");

        printf("Array after sorting: ");
        print_array(arr, n);
        return 100;
    }
    else
    {
        selection_sort(arr, n);
        printf("Array after sorting: ");
        print_array(arr, n);
        return 0;
    }
}

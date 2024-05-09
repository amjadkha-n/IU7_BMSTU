#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 10

int read_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int res = scanf("%d", &arr[i]);
        if (res != 1)
        {
            printf("Error: Invalid input\n");
            return 1;
        }
    }
    return 0;
}

double find_negative_mean(int arr[], int size)
{
    int neg_count = 0;
    int neg_sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < 0)
        {
            neg_count++;
            neg_sum += arr[i];
        }
    }
    if (neg_count == 0)
    {
        return -1;
    }
    return (double) neg_sum / neg_count;
}

void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[MAX_SIZE];
    int n;

    int count = scanf("%d", &n);
    if (count != 1 || n < 1 || n > MAX_SIZE)
    {
        printf("Error: Invalid input\n");
        return 1;
    }

    if (read_array(arr, n) == 1)
    {
        return 1;
    }

    double neg_mean = find_negative_mean(arr, n);
    if (neg_mean == -1)
    {
        printf("Error: No negative elements found\n");
        return 2;
    }
    else
    {
        printf("Arithmetic mean of negative elements: %.6lf\n", neg_mean);
    }
    return 0;
}

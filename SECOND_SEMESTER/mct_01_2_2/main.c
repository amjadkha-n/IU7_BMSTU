# include <stdio.h>
# include <math.h>
# include <stdlib.h> 

int filter(int arr[], int n) 
{
    int i, j;
    for (i = j = 0; i < n; i++)
    {
        if (sqrt(arr[i]) == floor(sqrt(arr[i]))) {
            arr[j++] = arr[i];
        }
    }
    return j;
}

void insert(int arr[], int n, int num) {
    int i, j;
    for (i = j = 0; i < n; i++) {
        if (arr[i] >= 10 && arr[i] <= 99) {
            arr[j++] = arr[i];
            arr[j++] = num;
        } else {
            arr[j++] = arr[i];
        }
    }
}

int main() {
    int n, arr[1024], i;

    printf("Enter number of elements (max 1024): ");
    if (scanf("%d", &n) != 1 || n > 1024 || n <= 0)
    {
        printf("Error: Invalid input\n");
        exit(1);
    }
    printf("Enter array elements: ");
    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Error: invalid input\n");
            exit(1);
        }
    }

    n = filter(arr, n);

    insert(arr, n, 7);

    printf("Final array: ");
    for (i = 0; i < n * 2 - 1; i++) {
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[n * 2 - 1]);

    return 0;
}
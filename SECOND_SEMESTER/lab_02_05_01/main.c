#include <stdio.h>

#define MAX_SIZE 10 

int enter_array(int *array, int *length)
{
    int count;
    count = scanf("%d", length);

    if (count != 1 || *length <= 0 || *length > MAX_SIZE)
    {
        printf("Error: Invalid input\n");
        return 1;
    }

    for (int i = 0; i < *length; i++)
    {
        count = scanf("%d", array);

        if (count != 1)
        {
            printf("Error: Invalid input\n");
            return 1;
        }

        array += 1;
    }
    return 0;
}

int calculate_sum(int *array, int *start, int *end)
{
    int sum = 0, count_pos = 0, count_neg = 0, min;
    int len = end - start;

    for (int i = 0; i < len; i++)
    {
        if (*start > 0)
            count_pos += 1;

        if (*start < 0)
            count_neg += 1;

        start += 1;
    }

    if (count_neg == 0 || count_pos == 0)
    {
        return 0;
    }
    if (count_neg < count_pos)
    {
        min = count_neg;
    }
    else
    {
        min = count_pos;
    }
    start = array;
    end = start + len - 1;

    for (int i = 0; i < min; i++)
    {
        while (*start >= 0)
        {
            start += 1;
        }
        while (*end <= 0)
        {
            end -= 1;
        }
        sum += (*start) * (*end);
        start += 1; 
        end -= 1;
    }

    return sum;
}

int main()
{
    int array[MAX_SIZE], *start = array, *end;
    int length, sum;

    int ch = enter_array(start, &length);

    if (ch == 1)
    {
        return 1;
    }

    // Setting pointers to start and end of array
    start = array;
    end = start + length;

    sum = calculate_sum(array, start, end);

    if (sum == 0)
    {
        printf("There are no positive or negative elements\n");
        return 2;
    }
    else
    {
        printf("Sum of the product is: %d\n", sum);
        return 0;
    }
}

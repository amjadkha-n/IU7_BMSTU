#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 0

int main()
{
    int num;
    int product;

    scanf("%d", &num);

    product = abs((num / 100) * (num / 10 % 10) * (num % 10));
    printf("%d\n", product);
    return OK;
}

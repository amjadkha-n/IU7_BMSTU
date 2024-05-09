#include <stdio.h>
#include <limits.h>

#define OK 0
#define IN_ERR 1
#define LOGIC_ERR -1

long long int fib(unsigned short n)
{
    long long int f0 = 0, f1 = 1;

    if (n < 0)
        return LOGIC_ERR;

    if (n == 0)
        return f0;

    if (n == 1)
        return f1;

    for (unsigned short i = 2; i <= n; i++)
    {
        long long int temp = f1;
        f1 += f0;
        f0 = temp;
        if (f1 < f0)
            return LOGIC_ERR;
    }

    return f1;
}

int main(void)
{
    unsigned short n;

    if (scanf("%hu", &n) != 1)
    {
        printf("Error: Invalid input\n");
        return IN_ERR;
    }

    long long int res = fib(n);

    if ((res == LOGIC_ERR) || (res > INT_MAX))
    {
        printf("Error: Integer overflow\n");
        return LOGIC_ERR;
    }

    printf("%lld\n", res);

    return OK;
}

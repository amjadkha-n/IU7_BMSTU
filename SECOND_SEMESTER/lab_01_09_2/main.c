#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_result(double x)
{
    double res = 0.0;
    int n = 1;
    if (x < 0)
    {
        printf("Error: Invalid input\n");
        exit(1);
    }
    while (x >= 0)
    {
        res += sqrt(n + x);
        n++;

        if (scanf("%lf", &x) != 1)
        {
            printf("Error: Invalid input\n");
            exit(1);
        }
    }

    return res / (n - 1);
}

int main(void)
{
    setbuf(stdout, NULL);
    double x;

    if (scanf("%lf", &x) != 1)
    {
        printf("Error: Invalid input\n");
        return -1;
    }

    double res = calculate_result(x);
    if (isnan(res))
    {
        return -1;
    }
    printf("%.6lf\n", res);

    return 0;
}


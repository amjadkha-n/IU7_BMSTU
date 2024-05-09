# include <stdio.h>
# include <stdlib.h>
# include <math.h>

int main()
{
    double eps;
    double x;
    printf("Please enter the value of epsilon: ");
    if (scanf("%lf", &eps) != 1 || eps < 0)
    {
        printf("Error: Invalid input\n");
        exit(1);
    }
    printf("Please enter the value of x: ");
    if (scanf("%lf", &x) != 1)
    {
        printf("Error: Invalid input\n");
        exit(1);
    }

    double sum = 0.0;
    int i = 3;
    double a_i;
    while (1) 
    {
        a_i = pow(-1, 2 * i - 1) * pow(x, i - 2) / (2 * tgamma(i + 3) - tgamma(i + 2));
        if (fabs(a_i) < eps)
        {
            break;
        }
        sum += a_i;
        i++;
    }
    printf("Sum of the sequence is %.5e\n", sum);
    double y = cos(asin(x));
    printf("f(x) = cos(asin(x)) = %.5f\n", y);

    return 0;
}   
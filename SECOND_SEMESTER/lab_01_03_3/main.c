#include <stdio.h>
#include <stdlib.h>

int main()
{
    double v0, a, t;
    int values = scanf("%lf%lf%lf", &v0, &a, &t);
    if (values != 3)
    {
        printf("Error: Invalid input");
        return 1;
    }
    else if (t < 0.0)
    {
        printf("Error: value can't be negative\n");
        return 1;
    }
    else 
    {
        double s = v0 * t + 0.5 * a * t * t;
        printf("%.6lf\n", s);
        return 0;
    }
}



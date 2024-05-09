#include <stdio.h>
#include<stdlib.h>
#include <math.h>

#define OK 0
#define ERROR 1

double area(float x1, float y1, float x2, float y2, float x3, float y3)
{
    return fabs(((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2))) / 2);
}

int main()
{
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;

    int coordinates1 = scanf("%f%f", &x1, &y1);

    if (coordinates1 != 2)
    {
        printf("Error: Invalid input\n");
        return ERROR;
    }

    int coordinates2 = scanf("%f%f", &x2, &y2);

    if (coordinates2 != 2)
    {
        printf("Error: Invalid input\n");
        return ERROR;
    }

    int coordinates3 = scanf("%f%f", &x3, &y3);

    if (coordinates3 != 2)
    {
        printf("Error: Invalid input\n");
        return ERROR;
    }

    double a = area(x1, y1, x2, y2, x3, y3);

    if (a <= 0)
    {
        printf("Can't draw triangle\n");
        return ERROR;
    }

    printf("%.6lf\n", a);
    return OK;
}


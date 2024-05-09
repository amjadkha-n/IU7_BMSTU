#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define OK 0
#define ERR 1

int main()
{    
    double a;
    double b;
    double phi;
  
    int values = scanf("%lf%lf%lf", &a, &b, &phi);
    
    if (values != 3)
    {
        printf("Please enter digits\n");
        return ERR;
    }
    else if (a < 0 || b < 0)
    {
        printf("Sides can't be negative\n");
        return ERR;
    }
    else if (phi < 0)
    {
        printf("Angle can't be negative\n");
        return ERR;
    }
    else
    {
        double degree = phi * PI / 180;
        double sin_angle = sin(degree);
        double area = 0.5 * a * b * sin_angle;
        printf("%.6lf\n", area);
        return OK;
    }
}


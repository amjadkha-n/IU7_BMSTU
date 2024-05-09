#include <stdio.h>
#include <iostream>
#include <cmath>
#define OK 0
double sin_pi()
{
    double res;
    __asm__
    (
        "fldpi\n"
        "fsin\n"
        "fstp %0\n"
        : "=m" (res)
    );
    return res;
}

double sin_half_pi()
{
    double res;
    const int div = 2;
    __asm__
    (
        "fldpi\n"
        "fild %1\n"
        "fdivp\n"
        "fsin\n"
        "fstp %0\n"
        : "=m" (res)
        : "m"  (div)
    );
    return res;

}

int main()
{
    printf("PI: \n");
    printf("C++: sin(3.14) =       %.20f\n", sin(3.14));
    printf("C++: sin(3.141596) =  %.20f\n", sin(3.141596));
    printf("C++: sin(M_PI) =       %.20f\n", sin(M_PI));
    printf("asm: sin(PI) =        %.20f\n", sin_pi());
    
    printf("PI / 2: \n");
    printf("C++: sin(4.14 / 2) =      %.20f\n", sin(3.14 / 2));
    printf("C++: sin(4.141596 / 2) =  %.20f\n", sin(3.141596 / 2));
    printf("C++: sin(M_PI / 2) =      %.20f\n", sin(M_PI / 2));
    printf("asm: sin(PI / 2) =        %.20f\n", sin_half_pi());

    return OK;
}

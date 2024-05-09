#include <iostream>
#include <assert.h>
#include <cmath>
#include <iomanip>
#include <cstdio>

#define EPS 1e-8

double func_cpp(double x)
{
    return cos(x*x*x + 7);
}

double bisection_method_cpp(double a, double b)
{
    double fa = func_cpp(a);
    double fb = func_cpp(b);

    assert((fa * fb <= 0));
    
    double fc, c;
    do {
        c = (a + b) / 2.0;
        fc = func_cpp(c); 
        
        if (fa * fc < 0)
        {
            b = c; 
            fb = fc;
        } else {
            a = c; 
            fa = fc;
        }
    } while (fabs(b - a) > EPS);
    
    return (a + b) / 2.0;
}


double func_asm(double x)
{
    double res;
    const int add = 7;
    __asm__(
        "fld %1\n" 
        "fld %1\n"
        "fmulp\n" 
        "fld %1\n"
        "fmulp\n" 
        "fild %2\n"
        "faddp\n"
        "fcos\n" 
        "fstp %0\n"
        : "=m" (res)
        : "m" (x), "m" (add)
        );
    return res;
}
double bisection_method_asm(double a, double b)
{
    double fa = func_asm(a), fb = func_asm(b), fc;
    double c;

    assert((fa * fb <= 0));
    do {
        c = (a + b) / 2.0; 

        fc = func_asm(c);
        
        if (fa * fc < 0) 
        {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    } while (fabs(b - a) > EPS);
    
    return (a + b) / 2.0;
}

double bisection_method_pure_asm(double a, double b)
{
    double c;
    const int div = 2;
    do
    {
        double fa = func_asm(a), fb = func_asm(b), fc;
        double a_s = a, b_s = b;
        __asm__(
            "fld %1\n"
            "fld %2\n"
            "faddp\n" 
            "fild %3\n"
            "fdivp\n" 
            "fstp %0\n" 
            : "=m" (c)  
            : "m" (a), "m" (b), "m" (div)
        );
        
        
        fc = func_asm(c);

        __asm__(
            "fld %2\n" 
            "fld %5\n" 
            "fmulp\n"  

            "fldz\n"
            "fcom\n"

            "fstsw ax\n"
            "sahf\n" 

            "ja greater\n"
            "jmp less\n"

            "less:\n"
            "fstp %0\n" 
            "fstp %1\n" 
            "fld %4\n" 
            "fstp %0\n"
            "fld %5\n" 
            "fstp %2\n"
            "fld %7\n" 
            "fstp %1\n"
            "jmp end\n"

            "greater:\n"
            "fstp %0\n" 
            "fstp %1\n" 
            "fld %4\n" 
            "fstp %1\n" 
            "fld %5\n" 
            "fstp %3\n" 
            "fld %6\n" 
            "fstp %0\n"

            "end:\n"
            : "=m" (a), "=m" (b), "=m" (fa), "=m" (fb)
            : "m" (c), "m" (fc), "m" (a_s), "m" (b_s) 
            : "%ax"                                      // We indicate that we use AX
        );
    } while (fabs(b - a) > EPS);
    return (a + b) / 2.0;
}

enum rc
{
    OK = 0
};


int main()
{
    double a = -2; // The initial left boundary of the interval
    double b = 2; // The initial right boundary of the interval
    
    printf("\n---f(x) = cos(x^3 + 7)---\n");
    double root = bisection_method_cpp(a, b);
    // std::setprecision(20): This manipulator sets the precision of floating-point output to 20 decimal places. It ensures 
    // that the root value is printed with high precision.
    std::cout << "c++ root:       " << std::setprecision(20) << root << std::endl;

    root = bisection_method_asm(a, b);
    std::cout << "asm root:       " << std::setprecision(20) << root << std::endl;
    
    root = bisection_method_pure_asm(a, b);
    std::cout << "asm(pure) root: " << std::setprecision(20) << root << std::endl;
    
    return OK;
}

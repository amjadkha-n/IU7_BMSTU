#include <stdio.h>
#include <math.h>

// Define a function to calculate s(x) with a given eps.
double calc_sum(double x, double eps)
{
    double result = 0, term = x;
    int i = 1;
    while (fabs(term) > eps)
    {
        result += term;
        term = term * x * x * i * i / (i + 1) / (i + 2);
        
        i += 2;
    }
    return result;
}

int main(void)
{
    int input_result;
    double x_value, eps, asin_result, s_value, big_delta, delta;
    input_result = scanf("%lf%lf", &x_value, &eps); 
    if ((input_result != 2) || (eps < 0) || (eps > 1) || (fabs(x_value) <= 1e-10) || (fabs(x_value) > 1))
    {
        printf("Error: Invalid input\n"); 
        return -1;
    }
    asin_result = asin(x_value);
    s_value = calc_sum(x_value, eps); 
    big_delta = fabs(asin_result - s_value);    
    delta = big_delta / fabs(asin_result); // Calculate the absolute and relative errors
    printf("Exact value: %g \n", asin_result);
    printf("Approximate value: %g \n", s_value); //An approximate value is an estimated value that is close to the actual value
    //In numerical analysis, the absolute error is the difference between the actual value and the approximate value of a quantity.
    // It represents how far off the approximation is from the true value
    printf("Absolute error: %g \n", big_delta); 
    //Relative error is the ratio of the absolute error to the true value of the quantity being measured. It is a measure of how
    //accurate the approximation is relative to the true value. It is expressed as a percentage or a decimal value.
    printf("Relative error: %g \n", delta);
    return 0;
}

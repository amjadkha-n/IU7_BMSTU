# include "my_mod.h"

// Function to calculate the expectation (mean) of numbers
int count_average(FILE *f, double *avg)
{
    int count = 0;
    double sum = 0.0;
    double number;

    while (fscanf(f, "%lf", &number) == COUNT_READ)
    {
        sum += number;
        count++;
    }

    if (count == 0)
        return NO_NUMBER;

    *avg = sum / count;

    return EXIT_SUCCESS;
}

// Function to calculate the variance of numbers
int count_variance(FILE *f, double avg, double *disp)
{
    int count = 0;
    double sum_squares = 0.0;
    double number;

    while (fscanf(f, "%lf", &number) == COUNT_READ)
    {
        double diff = number - avg;
        sum_squares += diff * diff;
        count++;
    }

    if (count == 0)
        return NO_NUMBER;

    if (count == 1)
        return ONE_NUMBER;

    *disp = sum_squares / count;

    return EXIT_SUCCESS;
}

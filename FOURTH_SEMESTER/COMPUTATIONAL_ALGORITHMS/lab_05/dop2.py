## @file normal_distribution_quantile.py
#  @brief This script calculates the quantile function (inverse CDF) of the standard normal distribution
#         using numerical integration and Newton's method.
#  
#  The script includes:
#  - Functions to perform numerical integration using the trapezoidal rule.
#  - Implementation of Newton's method to find the quantile value.

import math
import numpy as np

## @brief Integrand function for the standard normal distribution.
#  @param t Variable of integration.
#  @return Value of the integrand at t.
def integrand(t):
    return math.exp(- (t ** 2) / 2)

## @brief Computes the integral of a function using the trapezoidal rule.
#  @param f Function to be integrated.
#  @param x Upper limit of integration.
#  @param n Number of subdivisions for the trapezoidal rule.
#  @return Approximation of the integral from 0 to x.
def trapezoidal_rule(f, x, n=100):
    xa, xb = 0, x  # Integration bounds
    h = (xb - xa) / n  # Step size
    sum = 0.5 * (f(xa) + f(xb))  # Initial sum with boundary values
    for i in range(1, n):
        x = xa + i * h  # Compute the x value for the i-th step
        sum += f(x)  # Add the function value at x to the sum
    return h * sum  # Return the approximate integral

## @brief Computes the value of the CDF of the standard normal distribution at x.
#  @param x Point at which to evaluate the CDF.
#  @return Value of the CDF at x.
def f(x):
    integral = trapezoidal_rule(integrand, x)  # Compute the integral of the standard normal PDF up to x
    return (2 / math.sqrt(2 * math.pi)) * integral  # Normalize the result

## @brief Computes the derivative of the CDF of the standard normal distribution.
#  @param x Point at which to evaluate the derivative.
#  @return Value of the derivative (PDF) at x.
def df(x):
    return 2 / math.sqrt(2 * math.pi) * math.exp(-(x ** 2) / 2)  # Standard normal PDF

## @brief Uses Newton's method to find the x such that the CDF of the standard normal distribution equals c.
#  @param c Target CDF value.
#  @return Quantile value corresponding to the target CDF value c.
def newton(c):
    steps = 1000  # Maximum number of iterations
    x = 0.5  # Initial guess
    eps = 1e-8  # Convergence tolerance

    i = 0
    while i < steps:
        fx = f(x) - c  # Compute the function value minus the target CDF value
        if abs(fx) < eps:  # Check for convergence
            return x

        dfx = df(x)  # Compute the derivative (PDF)
        if dfx == 0:  # Avoid division by zero
            return x
        x -= fx / dfx  # Update the guess using Newton's method
        i += 1  # Increment the iteration counter
    return None  # Return None if the method did not converge

## @brief Main function to demonstrate the Newton's method for finding quantiles of the standard normal distribution.
#  @return None
def main():
    target_cdf_value = 0.4608  # Example target CDF value
    quantile = newton(target_cdf_value)  # Find the quantile
    print(quantile)  # Print the result

if __name__ == "__main__":
    main()  # Call the main function

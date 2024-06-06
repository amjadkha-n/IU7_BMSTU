## @file numerical_methods.py
#  @brief This script demonstrates numerical methods including Simpson's rule for integration,
#         Newton's method for finding roots of equations, and binary search to find values
#         for a specific integral.
#  
#  The script includes:
#  - A function to compute the standard normal distribution function.
#  - Simpson's rule for numerical integration.
#  - Newton's method for finding roots of a nonlinear equation.
#  - Binary search to find a specific value for an integral.
# Этот скрипт демонстрирует численные методы, включая правило Симпсона для интегрирования, метод Ньютона для нахождения корней
#  уравнений и бинарный поиск для нахождения значений определенного интеграла.
import math
import numpy as np

## @brief Computes the value of the standard normal distribution function.
#  @param x Input value.
#  @return The value of the standard normal distribution function at x.
def f(x):
    return (1 / math.sqrt(2 * math.pi)) * math.exp(-(x ** 2) / 2)

## @brief Computes the integral of the standard normal distribution function using Simpson's rule.
#  @param xCur The upper limit of integration.
#  @return The approximate value of the integral from 0 to xCur.
def simpson(xCur):
    # Number of steps for Simpson's rule (higher means more accurate)
    steps = 1000
    # Step size
    step = xCur / (steps * 2)

    # Generate x values for integration
    xValues = np.array([i * step for i in range(steps * 2 + 1)])
    # Compute function values at x values
    funcValues = np.array([f(x_i) for x_i in xValues])

    # Compute sums for Simpson's rule
    sumX1 = 4 * np.sum([funcValues[2 * i - 1] for i in range(1, steps)])
    sumX2 = 2 * np.sum([funcValues[2 * i] for i in range(1, steps - 1)])

    # Return the result of Simpson's rule
    return (step / 3) * (funcValues[0] + funcValues[-1] + sumX1 + sumX2)

## @brief Solves a nonlinear equation f(x) = 0 using Newton's method.
#  @param f Function for which the root is sought.
#  @param df Derivative of the function f.
#  @param x0 Initial guess for the root.
#  @param eps Convergence tolerance.
#  @return The root of the equation and the number of iterations.
def newton_method(f, df, x0, eps=1e-6):
    """
    Solves the nonlinear equation f(x) = 0 using Newton's method.

    @param f Function for which the root is sought.
    @param df Derivative of the function f.
    @param x0 Initial guess for the root.
    @param eps Convergence tolerance.

    @return The root of the equation and the number of iterations.
    """
    # Maximum number of iterations to prevent infinite loop
    max_iter = 1000
    # Initial guess
    x = x0

    for i in range(max_iter):
        # Compute function value at current guess
        fx = f(x)
        # Check if the function value is close enough to zero
        if abs(fx) < eps:
            return x, i
        # Compute derivative value at current guess
        dfx = df(x)
        # Prevent division by zero
        if dfx == 0:
            break
        # Update guess using Newton's formula
        x = x - fx / dfx

    # Return None if no solution is found within max_iter iterations
    return None, max_iter

# Example usage of the newton_method function
# Solve the equation x^2 - 2 = 0
f = lambda x: x ** 2 - 2  # Function definition
df = lambda x: 2 * x      # Derivative of the function
x0 = 1.0                  # Initial guess

# Find the root using Newton's method
root, num_iter = newton_method(f, df, x0)
if root is not None:
    print(f"The root of the equation: {root}")
    print(f"Number of iterations: {num_iter}")
else:
    print("No solution found.")

## @brief Uses binary search to find the value x such that the integral from 0 to x equals a given value.
#  @param value The target value of the integral.
#  @return The value x such that the integral from 0 to x equals the target value.
def bin_search(value):
    # Convergence tolerance for binary search
    eps = 1e-3
    # Initial bounds for the search
    left = 0
    right = 1

    # Expand the right bound until the integral exceeds the target value
    while value > simpson(right):
        left = right
        right *= 2

    # Perform binary search within the bounds until the interval is smaller than eps
    while right - left > eps:
        midX = (right + left) / 2

        # Narrow the search interval based on the value of the integral
        if value < simpson(midX):
            right = midX
        else:
            left = midX

    # Return the left bound as the result
    return left

# Input from the user for the target integral value
y = float(input("Enter y value: "))

# Find the x value such that the integral from 0 to x equals y
ans = bin_search(y)

# Print the result
print(f"Answer is {ans:.5f}")

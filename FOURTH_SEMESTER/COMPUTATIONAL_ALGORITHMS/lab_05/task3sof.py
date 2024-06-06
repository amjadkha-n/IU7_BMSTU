## @file bvp_newton_solver.py
#  @brief This script solves a boundary value problem (BVP) for a nonlinear differential equation 
#         using the finite difference method and Newton's method.
#  
#  The script includes:
#  - Functions to form the system of nonlinear algebraic equations.
#  - Functions to compute the Jacobian matrix of the system.
#  - Implementation of Newton's method to solve the nonlinear system.

import numpy as np

# Problem parameters
xa = 0.0  # Left boundary of the interval
xb = 1.0  # Right boundary of the interval
ya = 1.0  # Boundary condition at x = xa
yb = 3.0  # Boundary condition at x = xb

N = 10  # Number of grid points
h = 1 / N  # Step size

## @brief Computes the term for approximating the second derivative using finite differences.
#  @param x Index in the grid.
#  @param y Array of function values at the grid points.
#  @return The finite difference approximation of the second derivative at index x.
def term(x, y):
    return (y[x - 1] - 2 * y[x] + y[x + 1]) / (h ** 2)

## @brief Computes the values of the system of nonlinear equations at all grid points.
#  @param y Array of function values at the grid points.
#  @return Array of function values representing the nonlinear equations.
def F(y):
    f = np.zeros(N + 1)  # Initialize the array for function values

    f[0] = y[0] - ya  # Boundary condition at x = xa
    f[N] = y[N] - yb  # Boundary condition at x = xb

    for i in range(1, N):
        f[i] = term(i, y) - y[i] ** 3 - (i * h) ** 2  # Approximate the second derivative and form the equation

    return f  # Return the array of function values

## @brief Computes the Jacobian matrix of the system of nonlinear equations.
#  @param y Array of function values at the grid points.
#  @return Jacobian matrix of the system.
def jacobian(y):
    J = np.zeros((N + 1, N + 1))  # Initialize the Jacobian matrix

    J[0, 0] = 1  # Derivative of the boundary condition at x = xa
    J[N, N] = 1  # Derivative of the boundary condition at x = xb

    for i in range(1, N):
        J[i, i - 1] = 1 / (h ** 2)  # Derivative with respect to y[i-1]
        J[i, i] = -2 / (h ** 2) - 3 * y[i] ** 2  # Derivative with respect to y[i]
        J[i, i + 1] = 1 / (h ** 2)  # Derivative with respect to y[i+1]

    return J  # Return the Jacobian matrix

## @brief Solves the system of nonlinear equations using Newton's method.
#  @param X Initial guess for the solution.
#  @param function Function representing the system of nonlinear equations.
#  @param jacobian Function representing the Jacobian matrix of the system.
#  @param imax Maximum number of iterations.
#  @param tol Tolerance for convergence.
#  @return Solution vector after convergence.
def iter_newton(X, function, jacobian, imax=1e6, tol=1e-5):
    for i in range(int(imax)):
        J = jacobian(X)  # Calculate the Jacobian matrix
        Y = function(X)  # Calculate the function values
        dX = np.linalg.solve(J, Y)  # Solve for the correction dX from JdX = Y
        X -= dX  # Update the solution

        if np.linalg.norm(dX) < tol:  # Check for convergence
            print('converged.')
            break

    return X  # Return the converged solution

# Define the finite difference grid
x = np.linspace(xa, xb, N + 1)
print(x)

# Solve the system using Newton's method
result = iter_newton(x, F, jacobian)
print(list(map(float, result)))  # Print the solution as a list of floats

## @file newton_solver.py
#  @brief This script solves a system of nonlinear equations using Newton's method.
#  
#  The script defines a system of three nonlinear equations with three variables (x, y, z).
#  It computes the Jacobian matrix for the system symbolically and uses Newton's method to find
#  the roots of the system by iteratively updating the variable values until convergence.

# Скрипт определяет систему из трех нелинейных уравнений с тремя переменными (x, y, z). Он вычисляет матрицу Якоби для системы 
# символически и использует метод Ньютона для нахождения корней системы путем итеративного обновления значений переменных до сходимости.
import sympy as sym
import numpy as np
from scipy.linalg import solve

# Number of variables in the system of equations
N = 3
# Convergence tolerance for the Newton's method iterations
eps = 1e-3

## @brief Solves a system of nonlinear equations using Newton's method.
#  
#  This function performs Newton's method for solving a system of nonlinear equations.
#  It iteratively updates the guess for the variables until the change (delta) is less
#  than the specified tolerance (eps).
#
#  @param F Function that takes the current values of the variables and returns the function values.
#  @param Jacobian Function that takes the current values of the variables and returns the Jacobian matrix.
#  @return Array of values that are the solution to the system of equations.
def Newton(F, Jacobian):
    # Initial guess for the variables (can be modified as needed)
    curValues = np.array([0.54, 0.54, 0.54], dtype=float)

    # Compute the function values at the current guess
    FCur = F(*curValues)
    # Compute the Jacobian matrix at the current guess
    JacobianCur = Jacobian(*curValues)

    # Solve the linear system JacobianCur * delta = FCur to find the correction delta
    delta = solve(JacobianCur, FCur).reshape((N,))
    # Update the current values of the variables by adding delta
    curValues += delta

    # Iterate until the solution converges within the specified tolerance
    while np.linalg.norm(delta) > eps:
        # Update the current values by subtracting delta
        curValues -= delta

        # Recompute the function values at the new guess
        FCur = F(*curValues)
        # Recompute the Jacobian matrix at the new guess
        JacobianCur = Jacobian(*curValues)

        # Solve for the new delta
        delta = solve(JacobianCur, FCur).reshape((N,))

        # Print the current values of the variables for each iteration
        x, y, z = curValues
        print(f"Current values: x = {x:.7f}, y = {y:.7f}, z = {z:.7f}")

    # Return the final solution (values of variables)
    return curValues

# Define the variables for the system of equations
vars = ['x', 'y', 'z']
# Define the system of equations as strings
funcs = ['x ** 2 + y ** 2 + z ** 2 - 1',  # Equation 1: A sphere equation
         '2 * x ** 2 + y ** 2 - 4 * z',   # Equation 2: A paraboloid equation
         '3 * x ** 2 - 4 * y + z ** 2']   # Equation 3: A different quadratic equation

# Create a symbolic matrix of the functions using sympy
F = sym.Matrix(funcs)
print("F = ", F)  # Print the matrix of the system of equations

# Compute the Jacobian matrix of the system of equations symbolically
Jacobian = sym.Matrix(funcs).jacobian(vars)

# Create a function that computes the Jacobian matrix for given numerical values of variables
Jacobian = sym.lambdify(sym.symbols(vars), Jacobian)
# Create a function that computes the function values for given numerical values of variables
F = sym.lambdify(sym.symbols(vars), F)

# Call the Newton function to solve the system of equations
values = Newton(F, Jacobian)
space = ' '

# Print the final solution with formatted output
print(f"Answer is x: {values[0]:.5f}\n{space:>10}y: {values[1]:.5f}\n{space:>10}z: {values[2]:.5f}\n")

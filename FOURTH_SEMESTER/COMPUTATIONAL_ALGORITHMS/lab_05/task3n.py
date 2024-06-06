## @file bvp_newton_solver.py
#  @brief This script solves a boundary value problem (BVP) for a nonlinear differential equation 
#         using the finite difference method and Newton's method.
#  
#  The script includes:
#  - Functions to form the system of nonlinear algebraic equations.
#  - Functions to compute the Jacobian matrix of the system.
#  - Implementation of Newton's method to solve the nonlinear system.
#  - Visualization of the solution using Matplotlib.

import sympy as sym
import numpy as np
from scipy.linalg import solve
import matplotlib.pyplot as plt

# Problem parameters
N = 100  # Number of grid points
eps = 1e-3  # Tolerance for Newton's method

## @brief Solves the system of nonlinear equations using Newton's method.
#  @param F Function representing the system of nonlinear equations.
#  @param Jacobian Function representing the Jacobian matrix of the system.
#  @param initValues Initial guess for the solution.
#  @return Solution vector after convergence.
def Newton(F, Jacobian, initValues):
    curValues = np.array(initValues, dtype="float")  # Convert initial values to numpy array

    FCur = F(*curValues)  # Evaluate the function at current values
    JacobianCur = Jacobian(*curValues)  # Evaluate the Jacobian at current values

    delta = solve(JacobianCur, FCur).reshape((N + 1,))  # Solve for the correction delta
    curValues += delta  # Update the current values

    # Iterate until the solution converges within the tolerance
    while np.linalg.norm(delta) > eps:
        curValues -= delta

        FCur = F(*curValues)  # Re-evaluate the function at updated values
        JacobianCur = Jacobian(*curValues)  # Re-evaluate the Jacobian at updated values

        delta = solve(JacobianCur, FCur).reshape((N + 1,))  # Solve for the new correction

    return curValues  # Return the converged solution

# Boundary conditions
start = [0, 1]  # Boundary condition at the left end
end = [1, 3]  # Boundary condition at the right end

# Define the finite difference grid
step = (end[0] - start[0]) / N  # Step size
xValues = np.array([i * step for i in range(N + 1)])  # Array of x-values in the grid

# Define the symbolic variables for the solution
vars = [f'y{i}' for i in range(N + 1)]

# Formulate the system of nonlinear equations using finite differences
funcs = [f'{vars[i - 1]} - 2 * {vars[i]} + {vars[i + 1]} - ({step} ** 2) * ({vars[i]} ** 3 + {xValues[i]} ** 2)' for i in range(1, N)]
funcs.extend(['y0 - 1', f'y{N} - 3'])  # Add boundary conditions to the system

# Convert the system of equations to a sympy Matrix
F = sym.Matrix(funcs)
Jacobian = sym.Matrix(funcs).jacobian(vars)  # Compute the Jacobian matrix

# Lambdify the system of equations and the Jacobian matrix
Jacobian = sym.lambdify(sym.symbols(vars), Jacobian)
F = sym.lambdify(sym.symbols(vars), F)

# Initial guess for the solution
delta = (end[1] - start[1]) / (end[0] - start[0])
initValues = [start[1] + delta * i * step for i in range(N + 1)]

# Solve the system using Newton's method
yValues = Newton(F, Jacobian, initValues)

# Plot the initial guess and the converged solution
plt.grid()
plt.plot(xValues, initValues, label="Init values")
plt.plot(xValues, yValues, label="Result values")
plt.legend()
plt.show()

# Print a subset of the solution values for verification
print(yValues[20:30])

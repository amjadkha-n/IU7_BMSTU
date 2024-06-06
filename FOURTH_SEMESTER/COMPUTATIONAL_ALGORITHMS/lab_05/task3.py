## @file bvp_solver.py
#  @brief This script solves a boundary value problem (BVP) for a second-order differential equation
#         using the finite difference method and Newton's method for nonlinear systems.
#  
#  The script includes:
#  - Functions to approximate the second derivative using finite differences.
#  - Functions to form the system of nonlinear algebraic equations.
#  - Functions to compute the Jacobian matrix of the system.
#  - Implementation of Newton's method to solve the nonlinear system.
#  - Visualization of the solution using Matplotlib.

# решаем краевую задачу для дифференциального уравнения второго порядка с использованием метода конечных разностей и метода Ньютона.
#  Он задает параметры задачи, аппроксимирует вторую производную, формирует систему нелинейных уравнений, вычисляет матрицу Якоби, решает систему
#  линейных уравнений методом Гаусса и итеративно применяет метод Ньютона до достижения сходимости. Решение задачи выводится в числовом виде и 
# визуализируется графически.
from math import sqrt
import numpy as np
from matplotlib import pyplot as plt

# Problem parameters
xa = 0.0  # Left boundary of the domain
xb = 1.0  # Right boundary of the domain
ya = 1.0  # Boundary condition at xa
yb = 3.0  # Boundary condition at xb

N = 10  # Number of grid points
h = 1 / N  # Step size
tol = 1e-6  # Tolerance for Newton's method
max_iter = 1000  # Maximum number of iterations for Newton's method

## @brief Approximates the second derivative using finite differences.
#  @param x Index of the current grid point.
#  @param y Array of function values at grid points.
#  @return Approximation of the second derivative at point x.
def term(x, y):
    return (y[x - 1] - 2 * y[x] + y[x + 1]) / (h ** 2)

## @brief Forms the system of nonlinear algebraic equations for the BVP.
#  @param y Array of function values at grid points.
#  @return Array representing the system of nonlinear equations.
def F(y):
    f = np.zeros(N + 1)  # Initialize the array for the system of equations

    f[0] = y[0] - ya  # Apply boundary condition at xa
    f[N] = y[N] - yb  # Apply boundary condition at xb

    # Form the system of equations using finite differences
    for i in range(1, N):
        print("y[i] =", y[i])
        f[i] = term(i, y) - y[i] ** 3 - (i * h) ** 2
        print("f[i] =", f[i])

    return f

## @brief Computes the Jacobian matrix for the system of nonlinear equations.
#  @param y Array of function values at grid points.
#  @return Jacobian matrix of the system.
def J(y):
    jac = np.zeros((N + 1, N + 1))  # Initialize the Jacobian matrix

    jac[0, 0] = 1.0  # Derivative w.r.t. the first boundary condition
    jac[N][N] = 1.0  # Derivative w.r.t. the last boundary condition

    # Fill the Jacobian matrix with finite differences
    for i in range(1, N):
        jac[i][i - 1] = 1.0 / (h ** 2)
        jac[i][i] = -2.0 / (h ** 2) - 3.0 * y[i] ** 2
        jac[i][i + 1] = 1.0 / (h ** 2)

    return jac

## @brief Solves the linear system J * delta_x = -F using Gaussian elimination.
#  @param J Jacobian matrix.
#  @param b Right-hand side vector.
#  @return Solution vector delta_x.
def x_delta_by_gauss(J, b):
    return np.linalg.solve(J, b)

## @brief Computes the Euclidean norm of a vector.
#  @param var_seq Input vector.
#  @return Euclidean norm of the vector.
def get_vector_norm(var_seq):
    sum = 0
    for i in range(2):
        sum += var_seq[i] ** 2
    return sqrt(sum)

## @brief Solves a linear system using Gaussian elimination.
#  @param A Coefficient matrix.
#  @param B Right-hand side vector.
#  @return Solution vector.
def gauss(A, B):
    n = len(B)

    # Forward elimination to convert A to upper triangular form
    for i in range(n):
        maxEl = abs(A[i][i])
        maxRow = i
        for k in range(i + 1, n):
            if abs(A[k][i]) > maxEl:
                maxEl = abs(A[k][i])
                maxRow = k

        # Swap rows to place the largest element on the diagonal
        for k in range(i, n):
            tmp = A[maxRow][k]
            A[maxRow][k] = A[i][k]
            A[i][k] = tmp
        tmp = B[maxRow]
        B[maxRow] = B[i]
        B[i] = tmp

        # Eliminate entries below the pivot
        for k in range(i + 1, n):
            c = -A[k][i] / A[i][i]
            for j in range(i, n):
                if i == j:
                    A[k][j] = 0
                else:
                    A[k][j] += c * A[i][j]
            B[k] += c * B[i]

    # Back substitution to solve for x
    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        x[i] = B[i]
        for j in range(i + 1, n):
            x[i] -= A[i][j] * x[j]
        x[i] /= A[i][i]

    return x

## @brief Computes the next iteration of the solution using Newton's method.
#  @param x_init Initial guess for the solution.
#  @return Updated solution after one iteration.
def newton(x_init):
    jac = J(x_init)  # Compute the Jacobian matrix
    func_y = F(x_init)  # Compute the system of equations

    dx = gauss(jac, -func_y)  # Solve for the correction delta_x

    print("jac =", jac)
    print("func_y =", func_y)
    print("dx =", dx)

    return x_init + dx

## @brief Solves the system of nonlinear equations using Newton's method.
#  @param x_init Initial guess for the solution.
#  @return Converged solution.
def iter_newton(x_init):
    count = 0
    x_old = x_init
    x_new = newton(x_old)
    diff = np.linalg.norm(x_old - x_new)

    # Iterate until the solution converges within the tolerance or maximum iterations
    while diff > tol and count < max_iter:
        count += 1
        print("count =", count)
        x_new = newton(x_old)
        diff = np.linalg.norm(x_old - x_new)
        x_old = x_new
        print(x_new)

    convergent_val = x_new
    return convergent_val

# Create the grid and initial guess for y
x = np.linspace(xa, xb, N + 1)
y = np.linspace(ya, yb, N + 1)  # Initial guess for y

# Solve the system of nonlinear equations using Newton's method
y = iter_newton(y)

# Print the solution
print("x\t y")
for i in range(N + 1):
    print("{:.4f}\t {:.4f}".format(x[i], y[i]))

# Plot the solution
plt.plot(x, y)
plt.xlabel("x")
plt.ylabel("y")
plt.show()

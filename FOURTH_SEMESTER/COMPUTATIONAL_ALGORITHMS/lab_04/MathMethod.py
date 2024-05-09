from Utility import *

def Gauss(CoeffMat, Rights):
    """
    Solves a system of linear equations using Gaussian elimination.

    Parameters:
        CoeffMat (list of lists): The coefficient matrix of the system.
        Rights (list): The right-hand side vector of the system.

    Returns:
        list: The solution vector of the system.

    Raises:
        ValueError: If the length of CoeffMat and Rights are not the same.

    This function performs Gaussian elimination to solve a system of linear equations Ax = b, where A is the coefficient matrix and
     b is the right-hand side vector.
    It transforms the coefficient matrix into upper triangular form by eliminating coefficients below the diagonal and then back-substitutes 
    to find the solution.
    """

    # Iterating through each row of the coefficient matrix
    n = len(CoeffMat)
    if n != len(Rights):
        raise ValueError("Mat and Rights must have the same length")
    # Transforming the coefficient matrix into upper triangular form
    for i in range(n):
        for j in range(i + 1, n):
            # Calculating the coefficient to eliminate elements below the diagonal
            coeff = -(CoeffMat[j][i] / CoeffMat[i][i])
            # Performing row operations to eliminate elements below the diagonal
            for k in range(i, n):
                CoeffMat[j][k] += coeff * CoeffMat[i][k]
            Rights[j] += coeff * Rights[i]
    # Back-substituting to find the solution
    for i in range(n - 1, -1, -1):
        for j in range(i - 1, -1, -1):
            # Calculating the coefficient to eliminate elements above the diagonal
            coeff = -(CoeffMat[j][i] / CoeffMat[i][i])
            # Performing row operations to eliminate elements above the diagonal
            CoeffMat[j][i] += coeff * CoeffMat[i][i]
            Rights[j] += coeff * Rights[i]
    # Finding the solutions of the system of linear equations
    res = [Rights[i] / CoeffMat[i][i] for i in range(n)]
    return res

def LeastSquaresCoefs(x, y, p, n):
    """
    Calculates the coefficients of a polynomial of degree n that best fits the given data using least squares method.

    Parameters:
        x (list): The x-values of the data points.
        y (list): The y-values of the data points.
        p (list): The weights of the data points.
        n (int): The degree of the polynomial to fit.

    Returns:
        list: The coefficients of the polynomial.

    Raises:
        ValueError: If the lengths of x, y, and p are not the same.

    This function computes the coefficients of a polynomial of degree n that minimizes the sum of the squares of the differences between the 
    observed and predicted values.
    It constructs a system of linear equations using the least squares approach and solves it using Gaussian elimination.
    """

    # Checking if the lengths of x, y, and p are the same
    dataLen = len(x)
    if dataLen != len(y) or dataLen != len(p):
        raise ValueError("x, y and p must have the same length")

    # Calculating the coefficients for the x terms
    aCoeffsx = [sum([p[i] * x[i] ** j for i in range(dataLen)]) for j in range(2 * n + 1)]
    # Calculating the coefficients for the y terms
    aCoeffsy = [sum([p[i] * y[i] * x[i] ** j for i in range(dataLen)]) for j in range(n + 1)]
    # Constructing the coefficient matrix for the system of linear equations
    CoeffMat = [[aCoeffsx[i + j] for i in range(n + 1)] for j in range(n + 1)]

    # Solving the system of linear equations to find the coefficients
    return Gauss(CoeffMat, aCoeffsy)

def LeastSquare(x, y, p, n):
    """
    Generates a function that represents the polynomial of degree n that best fits the given data points using least squares method.

    Parameters:
        x (list): The x-values of the data points.
        y (list): The y-values of the data points.
        p (list): The weights of the data points.
        n (int): The degree of the polynomial to fit.

    Returns:
        function: A function representing the polynomial curve.
    The least squares method is a mathematical technique used to find the best-fitting curve to a set of data points. In the context of polynomial
     regression, the least squares method is used to find the coefficients of a polynomial of degree n that best fits the given data points.
    This function computes the coefficients of a polynomial of degree n using the least squares method with the given data points.
    It then constructs and returns a function that calculates the y-value of the polynomial for a given x-value.
    """

    # Calculating the coefficients of the polynomial using least squares method
    a = LeastSquaresCoefs(x, y, p, n)

    # Defining a function to evaluate the polynomial at a given x-value
    def func(xp):
        return sum([a[i] * xp ** i for i in range(n + 1)])
    
    return func

def LeastSquaresCoeffs2D(x, y, z, p, n):
    """
    Computes the coefficients of a 2D polynomial surface that best fits the given data points using least squares method.

    Parameters:
        x (list): The x-values of the data points.
        y (list): The y-values of the data points.
        z (list): The z-values of the data points.
        p (list): The weights of the data points.
        n (int): The degree of the polynomial surface to fit.

    Returns:
        list: The coefficients of the polynomial surface.

    This function calculates the coefficients of a 2D polynomial surface of degree n using the least squares method
    with the given data points. It constructs a system of linear equations using the data points and their weights,
    and solves it to obtain the coefficients.
    """

    # Check if the lengths of the input lists are consistent
    dataLen = len(x)
    if dataLen != len(y) or dataLen != len(z) or dataLen != len(p):
        raise ValueError("x, y, z, and p must have the same length")
    
    # Define functions to compute the sums for coefficients
    def aSum(xdeg, ydeg):
        return sum([xn ** xdeg * yn ** ydeg * pn for xn, yn, zn, pn in zip(x, y, z, p)])
    
    def zSum(xdeg, ydeg):
        return sum([xn ** xdeg * yn ** ydeg * zn * pn for xn, yn, zn, pn in zip(x, y, z, p)])
    
    # Calculate the coefficients of the polynomial surface
    aCoeffs = [[aSum(i + k, j + t) for k in range(n + 1) for t in range(n + 1 - k) ] for i in range(n + 1) for j in range(n + 1 - i) ]
    zCoeffs = [zSum(i, j) for i in range(n + 1) for j in range(n + 1 - i) ]

    # Solve the system of linear equations to find the coefficients
    return Gauss(aCoeffs, zCoeffs)

def LeastSquare2D(x, y, z, p, n):
    """
    Constructs a 2D polynomial function that best fits the given data points using the least squares method.

    Parameters:
        x (list): The x-values of the data points.
        y (list): The y-values of the data points.
        z (list): The z-values of the data points.
        p (list): The weights of the data points.
        n (int): The degree of the polynomial function to fit.

    Returns:
        function: A 2D polynomial function that approximates the data.

    This function computes a 2D polynomial function of degree n that best fits the given data points using the least
    squares method. It first calculates the coefficients of the polynomial function using the provided data points
    and their weights. Then, it constructs the polynomial function based on the computed coefficients.
    """

    # Calculate the coefficients of the 2D polynomial surface
    a = LeastSquaresCoeffs2D(x, y, z, p, n)
    
    # Define the polynomial function
    def func(xp, yp):
        res = 0
        ind = 0
        # Compute the value of the polynomial function at (xp, yp)
        for i in range(n + 1):
            for j in range(n + 1 - i):
                # Compute the contribution of each term in the polynomial
                res += a[ind] * xp ** i * yp ** j
                ind += 1
        return res
    
    return func
# def ScalarMult(x, f1, f2):
#     """
#     Computes the scalar product of two functions over the given domain.

#     Parameters:
#         x (list): The domain over which to compute the scalar product.
#         f1 (function): The first function.
#         f2 (function): The second function.

#     Returns:
#         float: The scalar product of f1 and f2 over the domain x.

#     This function computes the scalar product of two functions f1 and f2 over the given domain x. It evaluates each
#     function at every point in the domain, multiplies the corresponding function values, and sums the products to
#     obtain the scalar product.
#     """
#     return sum([f1(xn) * f2(xn) for xn in x])


# def yScalarMult(x, y, f):
#     """
#     Computes the scalar product of a function and a vector over the given domain.

#     Parameters:
#         x (list): The domain over which to compute the scalar product.
#         y (list): The vector.
#         f (function): The function.

#     Returns:
#         float: The scalar product of f and y over the domain x.

#     This function computes the scalar product of a function f and a vector y over the given domain x. It evaluates
#     the function at each point in the domain, multiplies the function value with the corresponding value in the vector,
#     and sums the products to obtain the scalar product.
#     """
#     return sum([f(x[i]) * y[i] for i in range(len(x))])

def GetApproximateODE(x, n, funcs, coeffFuncs):
    """
    GetApproximateODE computes an approximate Ordinary Differential Equation (ODE) solution.

    This function takes a set of data points (x) and a set of functions (funcs) representing the solutions to the ODE.
    It also requires a set of coefficient functions (coeffFuncs) that determine the polynomial terms used to approximate the solution.

    Parameters:
    - x (list): List of x values.
    - n (int): Degree of the polynomial approximation.
    - funcs (list): List of functions representing the ODE solutions.
    - coeffFuncs (list): List of coefficient functions for the polynomial terms.

    Returns:
    - func (function): Approximate ODE solution function.
    - poliCoeffs (list): Coefficients of the polynomial terms.

    Raises:
    - ValueError: If the number of functions doesn't match the expected degree.

    Purpose:
    This function aims to compute an approximate solution to an Ordinary Differential Equation (ODE)
    by fitting a polynomial of degree 'n' to the provided ODE solutions using the specified coefficient functions.

    """

    # Check if the number of functions matches the expected degree
    if (len(funcs) != n + 1 or len(coeffFuncs) != n + 1):
        raise ValueError("Number of functions must equal n + 1")
    
    # Define the zeroth coefficient function
    f0 = coeffFuncs[0]

    # Compute the matrix of coefficients for the polynomial terms
    cCoeffs = [[sum([f1(xp) * f2(xp)  for xp in x]) for f2 in coeffFuncs[1:]] for f1 in coeffFuncs[1:] ]

    # Compute the coefficients for the linear terms
    fCoeffs = [-sum([f0(xp) * f(xp) for xp in x])  for f in coeffFuncs[1:]]

    # Solve the system of equations to obtain polynomial coefficients
    poliCoeffs = Gauss(cCoeffs, fCoeffs)
    
    # Define the approximate function using the computed polynomial coefficients
    def func(xp):
        return funcs[0](xp) + sum([poliCoeffs[i] * funcs[i + 1](xp) for i in range(n)])

    return func, poliCoeffs

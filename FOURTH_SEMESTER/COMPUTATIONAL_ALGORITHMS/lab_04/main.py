# Importing Plotly Express library with an alias 'px'
import plotly.express as px
# Importing Plotly Graph Objects library with an alias 'go'
import plotly.graph_objects as go
# Importing all functions from the 'MathMethod' module
from MathMethod import *
# Importing all functions from the 'Utility' module
from Utility import *
# Importing the 'numpy' library with an alias 'np'
import numpy as np
# Importing the 'erfi' function from the 'scipy.special' module
from scipy.special import erfi

# Reading data from the file "data/tmp41" using the function 'read_xypdata'
x, y, p = read_xypdata("data/tmp41")

# Generating a linearly spaced array 'x_pred' using numpy with 20 points between the minimum and maximum of 'x'
x_pred = np.linspace(min(x), max(x), 20)
# Performing least squares regression using the function 'LeastSquare' to obtain a predictive function 'f_pred'
f_pred = LeastSquare(x, y, p, 3)
# Generating predicted 'y' values using the obtained predictive function for each value in 'x_pred'
y_pred = [f_pred(xi) for xi in x_pred]

# Calculating the coefficients of the polynomial using the least squares method for a polynomial of degree 3
f_coeffs = LeastSquaresCoefs(x, y, p, 3)
# Creating a string representation of the polynomial equation using the obtained coefficients
str = " + ".join([f"{f_coeffs[i]} * x^{i}" for i in range(3 + 1)])
# Printing the polynomial equation solution
print(f"Решение: {str}")

# Creating a line plot using Plotly Express with 'x' and 'y' values
fig = px.line(x=x, y=y)

# Adding a scatter trace of predicted values to the plot
# In Plotly, the add_trace function is used to add new traces (data series) to an existing plot. This function 
# allows you to create multiple traces on the same plot, enabling you to visualize multiple sets of data simultaneously.

# A scatter plot is a type of plot that displays individual data points on a two-dimensional plane. It is commonly used 
# to visualize relationships between two variables.
fig.add_trace(go.Scatter(x=x_pred, y=y_pred))
# Displaying the plot
fig.show()


# Reading data from the file "data/tmp42" using the function 'read_xypdata'
x, y, p = read_xypdata("data/tmp42")

# Generating a linearly spaced array 'x_pred' using numpy with 20 points between the minimum and maximum of 'x'
x_pred = np.linspace(min(x), max(x), 20)
# Performing least squares regression using the function 'LeastSquare' to obtain a predictive function 'f_pred'
f_pred = LeastSquare(x, y, p, 2)
# Generating predicted 'y' values using the obtained predictive function for each value in 'x_pred'
y_pred = [f_pred(xi) for xi in x_pred]

# Calculating the coefficients of the polynomial using the least squares method for a polynomial of degree 3
f_coeffs = LeastSquaresCoefs(x, y, p, 3)
# Creating a string representation of the polynomial equation using the obtained coefficients
str = " + ".join([f"{f_coeffs[i]} * x^{i}" for i in range(3 + 1)])
# Printing the polynomial equation solution
print(f"Решение: {str}")

# Creating a line plot using Plotly Express with 'x' and 'y' values
fig = px.line(x=x, y=y)
# Adding a scatter trace of predicted values to the plot
fig.add_trace(go.Scatter(x=x_pred, y=y_pred))
# Displaying the plot
fig.show()

# Defining a function 'f' that returns the square of its input
def f(x):
    return x ** 2

# Generating data using the function 'get_xypdata' with specific parameters and the defined function 'f'
x, y, p = get_xypdata(-10, 12, 50, 0, 1, f)

# Generating a linearly spaced array 'x_pred' using numpy with 10 points between -10 and 12
x_pred = np.linspace(-10, 12, 10)
# Performing least squares regression using the function 'LeastSquare' to obtain a predictive function 'f_pred'
f_pred = LeastSquare(x, y, p, 4)
# Generating predicted 'y' values using the obtained predictive function for each value in 'x_pred'
y_pred = [f_pred(xi) for xi in x_pred]

# Calculating the coefficients of the polynomial using the least squares method for a polynomial of degree 3
f_coeffs = LeastSquaresCoefs(x, y, p, 3)
# Creating a string representation of the polynomial equation using the obtained coefficients
str = " + ".join([f"{f_coeffs[i]} * x^{i}" for i in range(3 + 1)])
# Printing the polynomial equation solution
print(f"Решение: {str}")

# Creating an empty line plot using Plotly Express
fig = px.line()
# Adding a scatter trace of the function and its approximation to the plot
fig.add_trace(go.Scatter(x=x, y=y, name="Функция"))
fig.add_trace(go.Scatter(x=x_pred, y=y_pred, name="Приближение"))
# Displaying the plot
fig.show()

# Defining a function 'f' that returns a mathematical expression involving 'np.cos' and 'np.sin'
def f(x):
    return x ** 3 + np.cos(4 * x - 2) * 5 

# Generating data using the function 'get_xypdata' with specific parameters and the defined function 'f'
x, y, p = get_xypdata(-2, 4, 50, 0, 1, f)

# Generating a linearly spaced array 'x_pred' using numpy with 100 points between -2 and 4
x_pred = np.linspace(-2, 4, 100)
# Performing least squares regression using the function 'LeastSquare' to obtain a predictive function 'f_pred'
f_pred = LeastSquare(x, y, p, 4)
# Generating predicted 'y' values using the obtained predictive function for each value in 'x_pred'
y_pred = [f_pred(xi) for xi in x_pred]

# Calculating the coefficients of the polynomial using the least squares method for a polynomial of degree 3
f_coeffs = LeastSquaresCoefs(x, y, p, 3)
# Creating a string representation of the polynomial equation using the obtained coefficients
str = " + ".join([f"{f_coeffs[i]} * x^{i}" for i in range(3 + 1)])
# Printing the polynomial equation solution
print(f"Решение: {str}")

# Creating an empty line plot using Plotly Express
fig = px.line()
# Adding a scatter trace of the function and its approximation to the plot
fig.add_trace(go.Scatter(x=x, y=y, name="Функция"))
fig.add_trace(go.Scatter(x=x_pred, y=y_pred, name="Приближение"))
# Displaying the plot
fig.show()

# Reading data from the file "data/tmp43" using the function 'read_xypzdata'
x, y, z, p = read_xypzdata("data/tmp43")

# Performing least squares regression in two dimensions using the function 'LeastSquare2D' to obtain a predictive function 'func'
func = LeastSquare2D(x, y, z, p, 3)

# Generating linearly spaced arrays 'x_pred' and 'y_pred' using numpy with 40 points each between the minimum and maximum of 'x' and 'y' respectively
x_pred = np.linspace(min(x), max(x), 40)
y_pred = np.linspace(min(y), max(y), 40)
# Generating predicted 'z' values using the obtained predictive function for each combination of values in 'x_pred' and 'y_pred'
z_graph = [[func(xi, yi) for xi in x_pred]for yi in y_pred]

# Calculating the coefficients of the polynomial using the least squares method for a polynomial of degree 1 in two dimensions
fcoeffs = LeastSquaresCoeffs2D(x, y, z, p, 1)

# Creating a 3D scatter plot using Plotly Express with 'x', 'y', and 'z' values
fig = px.scatter_3d(x=x, y=y, z=z)
# Adding a surface trace of the predicted values to the plot
fig.add_trace(go.Surface(x=x_pred, y=y_pred, z=z_graph))
# Displaying the plot
fig.show()

# Reading data from the file "data/tmp44" using the function 'read_xypzdata'
x, y, z, p = read_xypzdata("data/tmp44")

# Performing least squares regression in two dimensions using the function 'LeastSquare2D' to obtain a predictive function 'func'
func = LeastSquare2D(x, y, z, p, 3)

# Generating linearly spaced arrays 'x_pred' and 'y_pred' using numpy with 40 points each between the minimum and maximum of 'x' and 'y' respectively
x_pred = np.linspace(min(x), max(x), 40)
y_pred = np.linspace(min(y), max(y), 40)
# Generating predicted 'z' values using the obtained predictive function for each combination of values in 'x_pred' and 'y_pred'
z_graph = [[func(xi, yi) for xi in x_pred]for yi in y_pred]

# Creating a 3D scatter plot using Plotly Express with 'x', 'y', and 'z' values
fig = px.scatter_3d(x=x, y=y, z=z)
# Adding a surface trace of the predicted values to the plot
fig.add_trace(go.Surface(x=x_pred, y=y_pred, z=z_graph))
# Displaying the plot
fig.show()

# Defining a function 'f' that returns the product of 'np.cos' and 'np.sin' of its inputs
def f(x, y):
    return np.cos(x) * np.sin(y)

# Generating data using the function 'get_xyzpdata' with specific parameters and the defined function 'f'
x, y, z, p = get_xyzpdata(-2, 3, 10, -2, 3, 10, 0, 1, f)

# Performing least squares regression in two dimensions using the function 'LeastSquare2D' to obtain a predictive function 'func'
func = LeastSquare2D(x, y, z, p, 4)

# Generating linearly spaced arrays 'x_pred' and 'y_pred' using numpy with 40 points each between the minimum and maximum of 'x' and 'y' respectively
x_pred = np.linspace(min(x), max(x), 40)
y_pred = np.linspace(min(y), max(y), 40)
# Generating predicted 'z' values using the obtained predictive function for each combination of values in 'x_pred' and 'y_pred'
z_graph = [[func(xi, yi) for xi in x_pred]for yi in y_pred]

# Creating a 3D scatter plot using Plotly Express with 'x', 'y', and 'z' values
fig = px.scatter_3d(x=x, y=y, z=z)
# Adding a surface trace of the predicted values to the plot
fig.add_trace(go.Surface(x=x_pred, y=y_pred, z=z_graph))
# Displaying the plot
fig.show()

# Defining a function 'ODESolution' that returns a mathematical expression involving exponential and error functions
def ODESolution(x):
    return ((-(np.exp(0.5) + 1) / erfi(1 / np.sqrt(2))) * erfi(x / np.sqrt(2)) + 1) / np.exp(x ** 2 / 2) + x

# Defining functions 'f0', 'f1', 'f2', 'f3', and 'f4' representing the coefficients of the polynomial terms
def f0(x):
    return 1 - x

def f1(x):
    return x * (1 - x)

def f2(x):
    return x ** 2 * (1 - x)

def f3(x):
    return x ** 3 * (1 - x)

def f4(x):
    return x**4 * (1 - x)

# Defining functions 'c0', 'c1', 'c2', 'c3', and 'c4' representing the coefficients of the polynomial terms in the solution
def c0(x):
    return 1 - 4 * x

def c1(x):
    return - 2 + 2 * x - 3 * x**2

def c2(x):
    return 2 - 6 * x + 3 * x**2 - 4 * x**3

def c3(x):
    return 6 * x - 12 * x**2 + 4 * x**3 - 5 * x**4

def c4(x):
    return 12 * x**2 - 20 * x**3 + 5 * x**4 + 6 * x**5

# Generating linearly spaced array 'x' using numpy with 100 points between 0 and 1
x = np.linspace(0, 1, 100)
# Calculating 'y' values using the 'ODESolution' function for each value in 'x'
y = [ODESolution(xp) for xp in x]

# Generating linearly spaced array 'x_pred' using numpy with 10 points between 0 and 1
x_pred = np.linspace(0, 1, 10)
# Obtaining the predictive function 'f_pred2' and coefficients 'c_pred2' using 'GetApproximateODE' function with degree 2 and specified functions and coefficients
f_pred2, c_pred2 = GetApproximateODE(x_pred, 2, [f0, f1, f2], [c0, c1, c2])
# Obtaining the predictive function 'f_pred3' and coefficients 'c_pred3' using 'GetApproximateODE' function with degree 3 and specified functions and coefficients
f_pred3, c_pred3 = GetApproximateODE(x_pred, 3, [f0, f1, f2, f3], [c0, c1, c2, c3])
# Obtaining the predictive function 'f_pred4' and coefficients 'c_pred4' using 'GetApproximateODE' function with degree 4 and specified functions and coefficients
f_pred4, c_pred4 = GetApproximateODE(x_pred, 4, [f0, f1, f2, f3, f4], [c0, c1, c2, c3, c4])

# Printing the polynomial equation solutions for degrees 2, 3, and 4
print(f"Решение степени 2: 1 - x + {c_pred2[0]}x(1 - x) + {c_pred2[1]}x^2(1-x)")
print(f"Решение степени 3: 1 - x + {c_pred3[0]}x(1 - x) + {c_pred3[1]}x^2(1-x) + {c_pred3[2]}x^3(1-x)")
print(f"Решение степени 4: 1 - x + {c_pred4[0]}x(1 - x) + {c_pred4[1]}x^2(1-x) + {c_pred4[2]}x^3(1-x) + {c_pred4[3]}x^4(1-x)")

# Generating 'y' values using the obtained predictive functions for each value in 'x'
y_pred2 = [f_pred2(xp) for xp in x]
y_pred3 = [f_pred3(xp) for xp in x]
y_pred4 = [f_pred4(xp) for xp in x]

# Creating an empty line plot using Plotly Express
fig = px.line()
# Adding traces of the exact solution and its approximations for degrees 2, 3, and 4 to the plot
fig.add_trace(go.Scatter(x=x, y=y, name="Точное решение"))
fig.add_trace(go.Scatter(x=x, y=y_pred2, name="Приближенное при степени 2"))
fig.add_trace(go.Scatter(x=x, y=y_pred3, name="Приближенное при степени 3"))
fig.add_trace(go.Scatter(x=x, y=y_pred4, name="Приближенное при степени 4"))

# Displaying the plot
fig.show()

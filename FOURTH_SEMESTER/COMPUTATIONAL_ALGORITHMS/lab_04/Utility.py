# from numpy import linspace
# from random import random

# def read_xypdata(filename):
#     """
#     read_xypdata reads data from a file containing x, y, and p values.

#     This function reads data from a file with the given filename, where each line contains
#     space-separated x, y, and p values. It then converts these values into lists of floats.

#     Parameters:
#     - filename (str): The name of the file to read data from.

#     Returns:
#     - x (list): List of x values.
#     - y (list): List of y values.
#     - p (list): List of p values.

#     Purpose:
#     This function is designed to facilitate reading data from a file containing x, y, and p values
#     and converting them into lists of floats for further processing or analysis.

#     """

#     # Open the file and read its contents
#     with open(filename, "r") as f:
#         data = f.read().splitlines()

#     # Split each line of data into x, y, and p values
#     for i in range(len(data)):
#         data[i] = data[i].split()

#     # Extract x, y, and p values from the data
#     x, y, p = zip(*data[1:])

#     # Convert x, y, and p values to lists of floats
#     x = list(map(float, x))
#     y = list(map(float, y))
#     p = list(map(float, p))

#     return x, y, p

# def get_xypdata(xs, xe, xstep, ps, pe, func):
#     """
#     get_xypdata generates x, y, and p data based on the given parameters and a function.

#     This function generates x values evenly spaced between xs and xe with a step size of xstep.
#     It then evaluates the given function at each x value to obtain corresponding y values.
#     Random p values are generated within the range [ps, pe] to match the length of x.

#     Parameters:
#     - xs (float): Start value of x.
#     - xe (float): End value of x.
#     - xstep (int): Step size for generating x values.
#     - ps (float): Start value of p.
#     - pe (float): End value of p.
#     - func (function): Function to evaluate for generating y values.

#     Returns:
#     - x (list): List of generated x values.
#     - y (list): List of corresponding y values obtained by evaluating the function at x.
#     - p (list): List of generated random p values.

#     Purpose:
#     This function is designed to generate synthetic x, y, and p data based on the given parameters
#     and a function. It allows users to create data for testing or analysis purposes.

#     """

#     # Generate evenly spaced x values
#     x = list(linspace(xs, xe, xstep))

#     # Evaluate the given function at each x value to obtain y values
#     y = [func(xi) for xi in x]

#     # Generate random p values within the specified range
#     pcoef = (pe - ps)
#     p = [random() * pcoef + ps for _ in range(len(x))]

#     return x, y, p

# def get_xyzpdata(xs, xe, xstep, ys, ye, ystep,  ps, pe, func):
#     """
#     get_xyzpdata generates x, y, z, and p data based on the given parameters and a function.

#     This function generates x and y values using linspace with the specified range and step sizes.
#     For each combination of x and y values, it evaluates the given function to obtain z values.
#     Random p values are generated within the range [ps, pe] for each data point.

#     Parameters:
#     - xs (float): Start value of x.
#     - xe (float): End value of x.
#     - xstep (int): Step size for generating x values.
#     - ys (float): Start value of y.
#     - ye (float): End value of y.
#     - ystep (int): Step size for generating y values.
#     - ps (float): Start value of p.
#     - pe (float): End value of p.
#     - func (function): Function to evaluate for generating z values.

#     Returns:
#     - x (list): List of generated x values.
#     - y (list): List of generated y values.
#     - z (list): List of corresponding z values obtained by evaluating the function at (x, y).
#     - p (list): List of generated random p values.

#     Purpose:
#     This function is designed to generate synthetic x, y, z, and p data based on the given parameters
#     and a function. It allows users to create 3D data for testing or analysis purposes.

#     """

#     x = []
#     y = []
#     z = []
#     p = []

#     # Generate x and y values using linspace with the specified range and step sizes
#     for xi in linspace(xs, xe, xstep):
#         for yi in linspace(ys, ye, ystep):
#             x.append(xi)
#             y.append(yi)
#             z.append(func(xi, yi))
#             p.append(random() * (pe - ps) + ps)

#     return x, y, z, p
# def read_xypzdata(filename):
#     """
#     read_xypzdata reads data from a file containing x, y, z, and p values.

#     This function reads data from the specified file, where each line contains
#     space-separated values for z, y, x, and p. It then parses these values
#     into separate lists and returns them.

#     Parameters:
#     - filename (str): The name of the file to read data from.

#     Returns:
#     - x (list): List of x values.
#     - y (list): List of y values.
#     - z (list): List of z values.
#     - p (list): List of p values.

#     Purpose:
#     This function is intended to read data from a file where each line contains
#     space-separated values for z, y, x, and p. It's useful for importing 3D data
#     sets stored in a simple text format.
#     """

#     with open(filename, "r") as f:  # Open the file in read mode
#         data = f.read().splitlines()  # Read lines from the file and split them

#     for i in range(len(data)):  # Iterate over each line of the data
#         data[i] = data[i].split()  # Split each line into a list of values

#     z, y, x, p = zip(*data[1:])  # Unzip the data and assign to variables
#     x = list(map(float, x))  # Convert x values to float
#     y = list(map(float, y))  # Convert y values to float
#     z = list(map(float, z))  # Convert z values to float
#     p = list(map(float, p))  # Convert p values to float

#     return x, y, z, p  # Return the parsed data



from numpy import linspace
from random import random

def read_xypdata(filename):
    with open(filename, "r") as f:
        data = f.read().splitlines()
    for i in range(len(data)):
        data[i] = data[i].split()
    x, y, p = zip(*data[1:])
    x = list(map(float, x))
    y = list(map(float, y))
    p = list(map(float, p))
    return x, y, p

def get_xypdata(xs, xe, xstep, ps, pe, func):
    x = list(linspace(xs, xe, xstep))
    y = [func(xi) for xi in x]
    pcoef = (pe - ps)
    p = [random() * pcoef + ps for _ in range(len(x))]

    return x, y, p

def get_xyzpdata(xs, xe, xstep, ys, ye, ystep,  ps, pe, func):
    x = []
    y = []
    z = []
    p = []
    for xi in linspace(xs, xe, xstep):
        for yi in linspace(ys, ye, ystep):
            x.append(xi)
            y.append(yi)
            z.append(func(xi, yi))
            p.append(random() * (pe - ps) + ps)
    return x, y, z, p

def read_xypzdata(filename):
        with open(filename, "r") as f:
            data = f.read().splitlines()
        for i in range(len(data)):
            data[i] = data[i].split()
        z, y, x, p = zip(*data[1:])
        x = list(map(float, x))
        y = list(map(float, y))
        z = list(map(float, z))
        p = list(map(float, p))
        return x, y, z, p

# get_xyzpdata(-10, 10, 20, -10, 10, 20, 0, 1, lambda x, y: x + y)
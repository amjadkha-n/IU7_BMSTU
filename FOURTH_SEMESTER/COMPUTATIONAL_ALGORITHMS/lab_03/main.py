import matplotlib.pyplot as plt
import numpy as np

from spline import *
from newton import *

def read_table(name):
    data = []  # array of matrices to store tables 5 * 5 * 5
    with open(name, mode='r') as f:
        n, m = map(int, f.readline().split())  # Reading table dimensions
        for _ in range(n):
            temp = []
            for _ in range(m):
                temp.append(list(map(int, f.readline().split())))  # Reading data and adding to temporary list
            data.append(temp)  # Adding temporary list to the overall data structure

    return data


def get_value_for_3d_newton(table, x, y, nx, ny):
    """
    Calculates the value of a function at a given point using trivariate Newton interpolation.

    Args:
        table (list): Three-dimensional table of values representing the function.
        x (float): The x-coordinate of the point at which to calculate the function value.
        y (float): The y-coordinate of the point at which to calculate the function value.
        nx (int): The degree of the Newton polynomial along the x-axis.
        ny (int): The degree of the Newton polynomial along the y-axis.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs trivariate Newton interpolation to approximate the value of the function
        at the specified point (x, y). It uses the given table of values and the degrees of Newton polynomials
        along the x and y axes for interpolation.

    Raises:
        ValueError: If the provided table of values is empty or if the degrees of the Newton polynomials are invalid.
    """
    # Creating a new table to store Newton coefficients for each row.
    new_table = [[px] for px in range(len(table))]
    
    # Iterating over each row in the input table.
    for j in range(len(table)):
        # Creating a temporary table where each element is [i, table[j][i], 1].
        # This fixes one row and adds to it the index of the element, its value, and a dummy variable 1.
        temp = [[i, table[j][i], 1] for i in range(len(table[0]))]
        # Getting the approximate value at point Y using the Newton's method.
        # Then this value is added to the row of the new table along with the dummy variable 1.
        new_table[j] += [approximate_newton(temp, y, ny), 1]

    # Getting the final approximate value at point X using the Newton's method.
    return approximate_newton(new_table, x, nx)

def get_value_for_3d_spline(table, x, y):
    """
    Calculates the value of a function at a given point using trivariate spline interpolation.

    Args:
        table (list): Three-dimensional table of values representing the function.
        x (float): The x-coordinate of the point at which to calculate the function value.
        y (float): The y-coordinate of the point at which to calculate the function value.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs trivariate spline interpolation to approximate the value of the function
        at the specified point (x, y). It uses the given table of values to construct a spline along the y-axis
        for each row in the table, and then interpolates along the x-axis using the resulting spline functions.

    Raises:
        ValueError: If the provided table of values is empty.
    """
    new_table = [[px] for px in range(len(table))]
    for j in range(len(table)):
        temp = [[i, table[j][i]] for i in range(len(table[0]))]
        spline = Spline(temp, 0, 0)
        new_table[j].append(spline.aproximate_value(y))

    spline = Spline(new_table, 0, 0)
    return spline.aproximate_value(x)

def get_value_for_3d_mashup_nx(table, x, y, nx):
    """
    Calculates the value of a function at a given point using trivariate mixed interpolation with Newton interpolation along the x-axis.

    Args:
        table (list): Three-dimensional table of values representing the function.
        x (float): The x-coordinate of the point at which to calculate the function value.
        y (float): The y-coordinate of the point at which to calculate the function value.
        nx (int): The degree of the Newton polynomial along the x-axis.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs trivariate mixed interpolation, combining spline interpolation along the y-axis
        and Newton interpolation along the x-axis. It constructs splines along the y-axis for each row in the table
        and then applies Newton interpolation along the x-axis using the resulting values.

    Raises:
        ValueError: If the provided table of values is empty.
    """
    new_table = [[px] for px in range(len(table))]
    for j in range(len(table)):
        temp = [[i, table[j][i]] for i in range(len(table[0]))]
        spline = Spline(temp, 0, 0)
        new_table[j] += [spline.aproximate_value(y), 1]

    return approximate_newton(new_table, x, nx)


def get_value_for_3d_mashup_ny(table, x, y, ny):
    """
    Calculates the value of a function at a given point using trivariate mixed interpolation with Newton interpolation along the y-axis.

    Args:
        table (list): Three-dimensional table of values representing the function.
        x (float): The x-coordinate of the point at which to calculate the function value.
        y (float): The y-coordinate of the point at which to calculate the function value.
        ny (int): The degree of the Newton polynomial along the y-axis.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs trivariate mixed interpolation, combining spline interpolation along the x-axis
        and Newton interpolation along the y-axis. It constructs splines along the x-axis for each row in the table
        and then applies Newton interpolation along the y-axis using the resulting values.

    Raises:
        ValueError: If the provided table of values is empty.
    """
    new_table = [[px] for px in range(len(table))]
    for j in range(len(table)):
        temp = [[i, table[j][i], 1] for i in range(len(table[0]))]
        new_table[j] += [approximate_newton(temp, y, ny), 1]

    spline = Spline(new_table, 0, 0)
    return spline.aproximate_value(x)

def get_value_for_4d_newton(table, x, y, z, nx, ny, nz):
    new_table = [[px] for px in range(len(table))]
    # print(new_table)
    for i in range(len(table)):
        new_table[i] += [get_value_for_3d_newton(table[i], x, y, nx, ny),1]  # фиксируем zi и считаем для 3 мерного 2 переменных

    return approximate_newton(new_table, z, nz)
def get_value_for_4d_newton(table, x, y, z, nx, ny, nz):
    """
    Calculates the value of a function at a given point using quadrivariate Newton interpolation.

    Args:
        table (list): Four-dimensional table of values representing the function.
        x (float): The x-coordinate of the point at which to calculate the function value.
        y (float): The y-coordinate of the point at which to calculate the function value.
        z (float): The z-coordinate of the point at which to calculate the function value.
        nx (int): The degree of the Newton polynomial along the x-axis.
        ny (int): The degree of the Newton polynomial along the y-axis.
        nz (int): The degree of the Newton polynomial along the z-axis.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs quadrivariate Newton interpolation to approximate the value of the function
        at the specified point (x, y, z). It applies trivariate Newton interpolation along the z-axis for each
        "layer" of the 3D table, and then interpolates along the remaining x and y axes using the resulting values.

    Raises:
        ValueError: If the provided table of values is empty or if the degrees of the Newton polynomials are invalid.
    """
    new_table = [[px] for px in range(len(table))]
    for i in range(len(table)):
        new_table[i] += [get_value_for_3d_newton(table[i], x, y, nx, ny), 1]  # fixing zi and calculating for 3D 2 variables

    return approximate_newton(new_table, z, nz)


def get_value_for_4d_spline(table, x, y, z):
    """
    Calculates the value of a function at a given point using quadrivariate spline interpolation.

    Args:
        table (list): Four-dimensional table of values representing the function.
        x (float): The x-coordinate of the point at which to calculate the function value.
        y (float): The y-coordinate of the point at which to calculate the function value.
        z (float): The z-coordinate of the point at which to calculate the function value.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs quadrivariate spline interpolation to approximate the value of the function
        at the specified point (x, y, z). It constructs trivariate spline functions for each "layer" of the 3D table
        and then interpolates along the remaining x and y axes using the resulting spline functions.

    Raises:
        ValueError: If the provided table of values is empty.
    """
    new_table = [[px] for px in range(len(table))]
    for i in range(len(table)):
        new_table[i].append(get_value_for_3d_spline(table[i], x, y))

    spline = Spline(new_table, 0, 0)

    return spline.aproximate_value(z)


def get_value_for_4d_mashup_nx(table, x, y, z, nx):
    """
    Calculates the value of a function at a given point using quadrivariate mixed interpolation with Newton interpolation along the x-axis.

    Args:
        table (list): Four-dimensional table of values representing the function.
        x (float): The x-coordinate of the point at which to calculate the function value.
        y (float): The y-coordinate of the point at which to calculate the function value.
        z (float): The z-coordinate of the point at which to calculate the function value.
        nx (int): The degree of the Newton polynomial along the x-axis.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs quadrivariate mixed interpolation, combining spline interpolation along the y and z axes
        and Newton interpolation along the x-axis. It constructs splines along the y and z axes for each "layer" of the 3D table
        and then applies Newton interpolation along the x-axis using the resulting values.

    Raises:
        ValueError: If the provided table of values is empty.
    """
    new_table = [[px] for px in range(len(table))]
    for i in range(len(table)):
        new_table[i].append(get_value_for_3d_mashup_nx(table[i], x, y, nx))

    spline = Spline(new_table, 0, 0)

    return spline.aproximate_value(z)

def get_value_for_4d_mashup_ny(table, x, y, z, ny):
    """
    Calculates the value of a function at a given point using quadrivariate mixed interpolation with Newton interpolation along the y-axis.

    Args:
        table (list): Four-dimensional table of values representing the function.
        x (float): The x-coordinate of the point at which to calculate the function value.
        y (float): The y-coordinate of the point at which to calculate the function value.
        z (float): The z-coordinate of the point at which to calculate the function value.
        ny (int): The degree of the Newton polynomial along the y-axis.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs quadrivariate mixed interpolation, combining spline interpolation along the x and z axes
        and Newton interpolation along the y-axis. It constructs splines along the x and z axes for each "layer" of the 3D table
        and then applies Newton interpolation along the y-axis using the resulting values.

    Raises:
        ValueError: If the provided table of values is empty.
    """
    new_table = [[px] for px in range(len(table))]
    for i in range(len(table)):
        new_table[i].append(get_value_for_3d_mashup_ny(table[i], x, y, ny))

    spline = Spline(new_table, 0, 0)

    return spline.aproximate_value(z)

def get_value_for_4d_mashup_nz(table, x, y, z, nz):
    """
    Calculates the value of a function at a given point using quadrivariate mixed interpolation with Newton interpolation along the z-axis.

    Args:
        table (list): Four-dimensional table of values representing the function.
        x (float): The x-coordinate of the point at which to calculate the function value.
        y (float): The y-coordinate of the point at which to calculate the function value.
        z (float): The z-coordinate of the point at which to calculate the function value.
        nz (int): The degree of the Newton polynomial along the z-axis.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs quadrivariate mixed interpolation, combining spline interpolation along the x and y axes
        and Newton interpolation along the z-axis. It constructs splines along the x and y axes for each "layer" of the 3D table
        and then applies Newton interpolation along the z-axis using the resulting values.

    Raises:
        ValueError: If the provided table of values is empty.
    """
    new_table = [[px] for px in range(len(table))]
    for i in range(len(table)):
        new_table[i] += [get_value_for_3d_spline(table[i], x, y), 1]

    return approximate_newton(new_table, z, nz)

def get_value_for_4d_mashup_nx_ny(table, x, y, z, nx, ny):
    """
    Calculates the value of a function at a given point using quadrivariate mixed interpolation with Newton interpolation along the x and y axes.

    Args:
        table (list): Four-dimensional table of values representing the function.
        x (float): The x-coordinate of the point at which to calculate the function value.
        y (float): The y-coordinate of the point at which to calculate the function value.
        z (float): The z-coordinate of the point at which to calculate the function value.
        nx (int): The degree of the Newton polynomial along the x-axis.
        ny (int): The degree of the Newton polynomial along the y-axis.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs quadrivariate mixed interpolation, combining spline interpolation along the z axis
        and Newton interpolation along the x and y axes. It constructs splines along the z axis for each "layer" of the 3D table
        and then applies Newton interpolation along the x and y axes using the resulting values.

    Raises:
        ValueError: If the provided table of values is empty.
    """
    new_table = [[px] for px in range(len(table))]
    for i in range(len(table)):
        new_table[i] += [get_value_for_3d_newton(table[i], x, y, nx, ny), 1]

    spline = Spline(new_table, 0, 0)

    return spline.aproximate_value(z)

def get_value_for_4d_mashup_nx_nz(table, x, y, z, nx, nz):
    """
    Calculates the value of a function at a given point using quadrivariate mixed interpolation with Newton interpolation along the x and z axes.

    Args:
        table (list): Four-dimensional table of values representing the function.
        x (float): The x-coordinate of the point at which to calculate the function value.
        y (float): The y-coordinate of the point at which to calculate the function value.
        z (float): The z-coordinate of the point at which to calculate the function value.
        nx (int): The degree of the Newton polynomial along the x-axis.
        nz (int): The degree of the Newton polynomial along the z-axis.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs quadrivariate mixed interpolation, combining spline interpolation along the y axis
        and Newton interpolation along the x and z axes. It constructs splines along the y axis for each "layer" of the 3D table
        and then applies Newton interpolation along the x and z axes using the resulting values.

    Raises:
        ValueError: If the provided table of values is empty.
    """
    new_table = [[px] for px in range(len(table))]
    for i in range(len(table)):
        new_table[i] += [get_value_for_3d_mashup_nx(table[i], x, y, nx), 1]

    return approximate_newton(new_table, z, nz)


def get_value_for_4d_mashup_ny_nz(table, x, y, z, ny, nz):
    """
    Calculates the value of a function at a given point using quadrivariate mixed interpolation with Newton interpolation along the y and z axes.

    Args:
        table (list): Four-dimensional table of values representing the function.
        x (float): The x-coordinate of the point at which to calculate the function value.
        y (float): The y-coordinate of the point at which to calculate the function value.
        z (float): The z-coordinate of the point at which to calculate the function value.
        ny (int): The degree of the Newton polynomial along the y-axis.
        nz (int): The degree of the Newton polynomial along the z-axis.

    Returns:
        float: The interpolated value of the function at the given point.

    Notes:
        This function performs quadrivariate mixed interpolation, combining spline interpolation along the x axis
        and Newton interpolation along the y and z axes. It constructs splines along the x axis for each "layer" of the 3D table
        and then applies Newton interpolation along the y and z axes using the resulting values.

    Raises:
        ValueError: If the provided table of values is empty.
    """
    new_table = [[px] for px in range(len(table))]
    for i in range(len(table)):
        new_table[i] += [get_value_for_3d_mashup_ny(table[i], x, y, ny), 1]

    return approximate_newton(new_table, z, nz)

def main():
    data = read_table('/home/amjad-j/Documents/Fourth_semester/Computational algorithms/lab_03/data.txt')
    x, y, z = [float(x) for x in input("Введите x, y, z: ").split()]
    nx, ny, nz = [int(x) for x in input("Введите nx, ny, nz: ").split()]

    print("Полиномом Ньютона: {:.3f}".format(get_value_for_4d_newton(data, x, y, z, nx, ny, nz)))
    print("Сплайн: {:.3f}".format(get_value_for_4d_spline(data, x, y, z)))
    print("Смешанная интерполяция (Ньютон по x): {:.3f}" \
          .format(get_value_for_4d_mashup_nx(data, x, y, z, nx)))
    print("Смешанная интерполяция (Ньютон по y): {:.3f}" \
          .format(get_value_for_4d_mashup_ny(data, x, y, z, ny)))
    print("Смешанная интерполяция (Ньютон по z): {:.3f}" \
          .format(get_value_for_4d_mashup_nz(data, x, y, z, nz)))
    print("Смешанная интерполяция (Ньютон по x и y): {:.3f}" \
          .format(get_value_for_4d_mashup_nx_ny(data, x, y, z, nx, ny)))
    print("Смешанная интерполяция (Ньютон по x и z): {:.3f}" \
          .format(get_value_for_4d_mashup_nx_nz(data, x, y, z, nx, nz)))
    print("Смешанная интерполяция (Ньютон по y и z): {:.3f}" \
          .format(get_value_for_4d_mashup_ny_nz(data, x, y, z, ny, nz)))


if __name__ == '__main__':
    main()


# def main():
#     data = read_table('/home/amjad-j/Documents/Fourth_semester/Computational algorithms/lab_03/data.txt')
#     x, y, z = [float(x) for x in input("Введите x, y, z: ").split()]
#     nx, ny, nz = [int(x) for x in input("Введите nx, ny, nz: ").split()]

#     results = [
#         ("Полиномом Ньютона", get_value_for_4d_newton(data, x, y, z, nx, ny, nz)),
#         ("Сплайн", get_value_for_4d_spline(data, x, y, z)),
#         ("Смешанная интерполяция (Ньютон по x)", get_value_for_4d_mashup_nx(data, x, y, z, nx)),
#         ("Смешанная интерполяция (Ньютон по y)", get_value_for_4d_mashup_ny(data, x, y, z, ny)),
#         ("Смешанная интерполяция (Ньютон по z)", get_value_for_4d_mashup_nz(data, x, y, z, nz)),
#         ("Смешанная интерполяция (Ньютон по x и y)", get_value_for_4d_mashup_nx_ny(data, x, y, z, nx, ny)),
#         ("Смешанная интерполяция (Ньютон по x и z)", get_value_for_4d_mashup_nx_nz(data, x, y, z, nx, nz)),
#         ("Смешанная интерполяция (Ньютон по y и z)", get_value_for_4d_mashup_ny_nz(data, x, y, z, ny, nz))
#     ]

#     print("| Метод интерполяции                       | Результат      |")
#     print("|------------------------------------------|----------------|")
#     for method, result in results:
#         print("|------------------------------------------|----------------|")
#         print(f"| {method:<40} | {result:>14.3f} |")
#     print("|------------------------------------------|----------------|")

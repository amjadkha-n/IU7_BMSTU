import prettytable as pt
import matplotlib.pyplot as plt
from gaus import integral_by_gauss, solve_ls_by_gaus_method
from derivative import *
from math import log, exp

task = int(input("Введите номер задания: "))
if task == 1:
    # /// \brief Small value used as the convergence criteria for the numerical integration.
    epsilon = 1e-3

    # /// \brief 1Maximum number of nodes for the Gauss integration.
    max_dot_count = 13

    # /// \brief Upper limit function for the region of integration.
    f_1 = lambda x: 1 - x

    # /// \brief Lower limit function for the region of integration.
    f_2 = lambda x: 0

    # /// \brief Open the data file and read the data points.
    with open("./data.txt", "r") as file:
        # /// \brief Read the first line, split by tab, and convert to float, excluding the first element.
        xs = list(map(float, file.readline().split('\t')[1:]))
        ys = []
        zs = []

        # /// \brief Loop through the remaining lines in the file to read ys and zs.
        for line in file:
            # /// \brief Convert the line to a list of floats.
            line = list(map(float, line.split('\t')))
            # /// \brief The first element is a y value.
            ys.append(line[0])
            # /// \brief The remaining elements are z values.
            zs.append(line[1:])

            # /// \brief Take the logarithm of each z value.
            for i in range(len(zs[-1])):
                zs[-1][i] = log(zs[-1][i])

        # /// \brief Form the matrix for solving the system of linear equations.
        matrix = [[1, xs[0], ys[0], zs[0][0]], [1, xs[-1], ys[-1], zs[-1][-1]],[1, xs[0], ys[-1], zs[-1][0]]]

        # /// \brief Solve the system using Gaussian elimination method to get the coefficients.
        result_coef = solve_ls_by_gaus_method(matrix)

        # /// \brief Define the function using the result coefficients.
        function = lambda x, y: result_coef[0] + result_coef[1] * x + result_coef[2] * y

        # /// \brief Define the real value function by exponentiating the linear function.
        real_value = lambda x, y: exp(function(x, y))

        result_x = []

        # /// \brief Calculate the integral for varying number of nodes in the x direction.
        for i in range(1, max_dot_count + 1):
            result_x.append(integral_by_gauss(min(xs), max(xs), i, max_dot_count, real_value, f_2, f_1, epsilon))

        result_y = []

        # /// \brief Calculate the integral for varying number of nodes in the y direction.
        for i in range(1, max_dot_count + 1):
            result_y.append(integral_by_gauss(min(xs), max(xs), max_dot_count, i, real_value, f_2, f_1, epsilon))

        # /// \brief Print the results for the x and y direction variations.
        print(result_x)
        print(result_y)

        # /// \brief Plot the results showing the change in integral value with number of nodes.
        plt.grid()
        plt.plot([i for i in range(1, max_dot_count + 1)], result_x, label="Изменение количества узлов по направлению x")
        plt.plot([i for i in range(1, max_dot_count + 1)], result_y, label="Изменение количества узлов по направлению y")
        plt.legend()
        plt.show()
else:
    # /// \brief Step size for first order differences.
    step_1 = 1

    # /// \brief Step size for second order differences.
    step_2 = 2

    # /// \brief Order of accuracy for Runge's formula.
    p = 2

    # /// \brief y values for the function.
    ys = [0.571, 0.889, 1.091, 1.231, 1.333, 1.412]

    # /// \brief x values for the function.
    xs = [i + 1 for i in range(6)]

    # /// \brief Create a PrettyTable object for displaying results.
    table = pt.PrettyTable()
    columns = ["x", "y", "1", "2", "3", "4", "5"]

    # /// \brief Add x and y columns to the table.
    table.add_column(columns[0], xs)
    table.add_column(columns[1], ys)

    buffer_c = []
    buffer_l = []
    buffer_l_2 = []

    # /// \brief Calculate one-sided left differences.
    for i in range(1, len(xs)):
        buffer_l.append(one_side_left_dif_derivative(step_1, ys[i], ys[i - 1]))

    # /// \brief Calculate one-sided left difference for the first element.
    buffer_l.insert(0, one_side_left_dif_derivative(step_1, ys[0]))

    # /// \brief Calculate centered differences.
    for i in range(1, len(xs) - 1):
        buffer_c.append(center_dif_derivative(step_1, ys[i + 1], ys[i - 1]))

    # /// \brief Insert 'None' for the first and last elements in centered differences.
    buffer_c.insert(0, center_dif_derivative(0))
    buffer_c.append("None")

    # /// \brief Calculate one-sided left differences with larger step.
    for i in range(step_2, len(xs)):
        buffer_l_2.append(one_side_left_dif_derivative(step_2, ys[i], ys[i - step_2]))

    buffer_runge = []

    # /// \brief Calculate Runge's corrected differences.
    for i in range(2, len(buffer_l)):
        buffer_runge.append(second_runge_formula(float(buffer_l[i]), float(buffer_l_2[i - step_2]), int(step_2 / step_1), p))

    buffer_runge.insert(0, "None")
    buffer_runge.insert(0, "None")

    xsi = [ x for x in xs ]
    teta = [xs[i] / ys[i] for i in range(len(xs))]

    buffer_align = []

    # /// \brief Calculate derivatives using alignment variables.
    for i in range(len(xs) - 1):
        buffer_align.append(derivative_with_align_vars(teta[i], teta[i + 1], xsi[i], xsi[i + 1], ys[i], xs[i]))

    buffer_align.append("None")

    buffer_second = []

    # /// \brief Calculate second order differences.
    for i in range(1, len(xs) - 1):
        buffer_second.append(second_dif_derivative(step_1, ys[i + 1], ys[i], ys[i - 1]))

    buffer_second.insert(0, center_dif_derivative(0))
    buffer_second.append("None")

    # /// \brief Add calculated differences to the table.
    table.add_column("1", buffer_l)
    table.add_column("2", buffer_c)
    table.add_column("3", buffer_runge)
    table.add_column("4", buffer_align)
    table.add_column("5", buffer_second)

    # /// \brief Print the table.
    print(table)

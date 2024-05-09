def h(x1, x2):
    """
    Calculate the difference between two x values.

    :param x1: First x value.
    :param x2: Second x value.
    :return: Difference between x2 and x1.
    """
    return x2 - x1


def a(x):
    """
    Identity function returning the same value as input.

    :param x: Input value.
    :return: Same value as input.
    """
    return x


def c(c_i, ksi_i, theta_i):
    """
    Calculates the following coefficient c in the spline.

    :param c_i: The current coefficient is c.
    :param ksi_i: The current ksi coefficient.
    :param theta_i: The current theta coefficient.
    :return: The following coefficient is c.
    """
    print(ksi_i * c_i + theta_i)
    return ksi_i * c_i + theta_i



def calc_a_values(y_values):
    """
    Calculates the coefficients of 'a' for a cubic spline based on the values of y.

    :param y_values: A list of y values.
    :return: List of coefficients a.
    """
    a_values = []
    for i in range(len(y_values) - 1):
        a_values.append(y_values[i])
    return a_values



def f(y1, y2, y3, h1, h2):
    """
    Calculates the value of the function 'f' for cubic spline interpolation.

    :param y1: The value of y at the previous point.
    :param y2: The value of y at the current point.
    :param y3: The value of y at the next point.
    :param h1: The distance between the current and previous points.
    :param h2: The distance between the next and current points.
    :return: The value of the function f.
    """
    return 3 * ((y3 - y2) / h2 - (y2 - y1) / h1)



def ksi(ksi1, h1, h2):
    """
    Calculates the ksi coefficient for cubic spline interpolation.

    :param ksi1: Previous ksi coefficient.
    :param h1: The distance between the current and previous points.
    :param h2: The distance between the next and current points.
    :return: The value of the ksi coefficient.
    """
    return - h1 / (h2 * ksi1 + 2 * (h2 + h1))



def theta(fi, theta_i, ksi_i, h1, h2):
    """
    Calculates the theta coefficient for cubic spline interpolation.

    :param fi: The value of the function f.
    :param theta_i: Previous theta coefficient.
    :param ksi_i: The current ksi coefficient.
    :param h1: The distance between the current and previous points.
    :param h2: The distance between the next and current points.
    :return: The value of the theta coefficient.
    """
    return (fi - h1 * theta_i) / (h1 * ksi_i + 2 * (h2 + h1))



def calc_h_values(x_values):
    """
    Calculates the difference between consecutive values of x.

    :param x_values: A list of x values.
    :return: A list of differences between consecutive x values.
    """
    h_values = []
    for i in range(1, len(x_values)):
        h_values.append(h(x_values[i], x_values[i - 1]))
    return h_values



def calc_c_values(x_values, y_values, start, end):
    """
    Calculates the coefficients c for cubic spline interpolation.

    :param x_values: A list of x values.
    :param y_values: A list of y values.
    :param start: Initial coefficient c.
    :param end: The final coefficient of c.
    :return: List of coefficients c.
    """
    # Получение количества значений x
    size_x = len(x_values)
    # Инициализация списка для хранения коэффициентов c
    c_values = [0] * (size_x - 1)
    # Установка первого и второго коэффициентов c на основе предоставленных начального и конечного значений
    c_values[0] = start
    c_values[1] = end

    # Инициализация значений ksi и theta на основе начальных и конечных коэффициентов
    if start == 0 and end == 0:
        ksi_values = [0, 0]
        theta_values = [0, 0]
    elif start == 0:
        ksi_values = [0, end / 2]
        theta_values = [0, end / 2]
    else:
        ksi_values = [start / 2, end / 2]
        theta_values = [start / 2, end / 2]

    # Рассчет значений ksi и theta для каждого интервала
    for i in range(2, size_x):
        # Рассчет разности между последовательными значениями x
        h2 = x_values[i] - x_values[i - 1]
        h1 = x_values[i - 1] - x_values[i - 2]

        # Рассчет значения производной функции
        fi_cur = f(y_values[i - 2], y_values[i - 1], y_values[i], h1, h2)
        # Рассчет коэффициента ksi
        ksi_cur = ksi(ksi_values[i - 1], h1, h2)
        # Рассчет коэффициента theta
        theta_cur = theta(fi_cur, theta_values[i - 1], ksi_values[i - 1], h1, h2)

        # Добавление текущих значений ksi и theta в соответствующие списки
        ksi_values.append(ksi_cur)
        theta_values.append(theta_cur)

    # Установка последнего коэффициента c равным последнему значению theta
    c_values[-1] = theta_values[-1]

    # Обратная подстановка для расчета других коэффициентов c
    for i in range(size_x - 2, 0, -1):
        c_values[i - 1] = c(c_values[i], ksi_values[i], theta_values[i])

    return c_values



def b(y1, y2, c1, c2, h):
    """
    Calculates the coefficient b for cubic spline interpolation.

    :param y1: The value of y at the previous point.
    :param y2: The value of y at the current point.
    :param c1: Previous coefficient c.
    :param c2: Current coefficient c.
    :param h: The distance between the current and previous points.
    :return: The value of the coefficient b.
    """
    return (y2 - y1) / h - (h * (c2 + 2 * c1) / 3)


def d(c1, c2, h):
    """
    Calculates the coefficient d for cubic spline interpolation.

    :param c1: Previous coefficient c.
    :param c2: Current coefficient c.
    :param h: The distance between the current and previous points.
    :return: The value of the d coefficient.
    """
    return (c1 - c2) / (3 * h)


def calc_b_values(x_values, y_values, c_values):
    """
    Calculates the coefficients b for cubic spline interpolation.

    :param x_values: A list of x values.
    :param y_values: A list of y values.
    :param c_values: List of coefficients of c.
    :return: List of coefficients b.
    """
    b_values = []
    for i in range(1, len(x_values) - 1):
        hi = x_values[i] - x_values[i - 1]
        b_values.append(b(y_values[i - 1], y_values[i], c_values[i - 1], c_values[i], hi))

    hi = x_values[-1] - x_values[-2]
    b_values.append(b(y_values[-2], y_values[-1], 0, c_values[-1], hi))

    return b_values



def calc_d_values(x_values, c_values):
    """
    Calculates the coefficients d for cubic spline interpolation.

    :param x_values: A list of x values.
    :param c_values: List of coefficients of c.
    :return: List of coefficients d.
    """
    d_values = []

    size = len(x_values)

    for i in range(1, size - 1):
        hi = x_values[i] - x_values[i - 1]
        d_values.append(d(c_values[i], c_values[i - 1], hi))

    hi = x_values[-1] - x_values[-2]
    d_values.append(d(0, c_values[-1], hi))

    return d_values


def calculate_coefs_spline(x_values, y_values, start, end):
    """
    Calculates all coefficients for cubic spline interpolation.

    :param x_values: A list of x values.
    :param y_values: A list of y values.
    :param start: Initial coefficient c.
    :param end: The final coefficient of c.
    :return: Lists of coefficients a, b, c and d.
    """
    a_values = calc_a_values(y_values)
    c_values = calc_c_values(x_values, y_values, start, end)
    b_values = calc_b_values(x_values, y_values, c_values)
    d_values = calc_d_values(x_values, c_values)

    return a_values, b_values, c_values, d_values


def find_index(x_values, x):
    """
    Finds the index of the point closest to the target value of x.

    :param x_values: A list of x values.
    :param x: The target value of x.
    :return: Index of the nearest point.
    """
    size = len(x_values)
    index = 1

    while index < size and x_values[index] < x:
        index += 1

    return index - 1



def count_polynom(x, x_values, index, coefs):
    """
    Evaluates the polynomial at the target value of x.

    :param x: The target value of x.
    :param x_values: A list of x values.
    :param index: The index of the nearest point to x.
    :param coefs: Lists of coefficients a, b, c and d.
    :return: The value of the polynomial at x.
    """
    h = x - x_values[index]
    y = 0

    for i in range(4):
        y += coefs[i][index] * (h ** i)

    return y


def print_spline_funct(table, x, start, end):
    """
    Prints the value of the spline function at the target x.

    :param table: List of points.
    :param x: The target value of x.
    :param start: Initial coefficient c.
    :param end: The final coefficient of c.
    """
    x_values = [i.get_x() for i in table]
    y_values = [i.get_y() for i in table]

    index = find_index(x_values, x)
    coeffs = calculate_coefs_spline(x_values, y_values, start, end)

    fx = coeffs[0][index]
    for i in range(1, len(coeffs)):
        fx += coeffs[i][index] * (x - x_values[index]) ** i

    print("F(x) = {:.6f}".format(fx), end=' ')


def spline(table, x, start, end):
    """
    Evaluates the spline function in the target x.

    :param table: List of points.
    :param x: The target value of x.
    :param start: Initial coefficient c.
    :param end: The final coefficient of c.
    :return: The value of the spline function at x.
    """
    x_values = [i.get_x() for i in table]
    y_values = [i.get_y() for i in table]

    coeffs = calculate_coefs_spline(x_values, y_values, start, end)

    index = find_index(x_values, x)

    y = count_polynom(x, x_values, index, coeffs)

    return y



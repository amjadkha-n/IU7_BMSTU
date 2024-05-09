from scipy.misc import derivative
import numpy as np

infinity = None


def get_index(points, x):
    """
    Finds the index of the point closest to the specified x value in the list of points.
    
    :param points: A list of points.
    :param x: The set value of x.
    :return: Index of the point with the smallest deviation from x.
    """
    # Инициализация переменных для минимального отклонения и индекса ближайшей точки
    dif = abs(points[0].get_x() - x)  # Вычисление начального отклонения
    index = 0  # Инициализация индекса на 0
    
    # Перебор каждой точки для поиска ближайшей
    for i in range(len(points)):
        # Обновление минимального отклонения и индекса при нахождении меньшего отклонения
        if abs(points[i].get_x() - x) < dif:
            dif = abs(points[i].get_x() - x)
            index = i
    return index  # Возврат индекса ближайшей точки


# Получение ближайших рабочих точек для вычислений
def get_working_points(points, index, n):
    """
    Retrieves a subset of points around the specified index.
    
    :param points: A list of points.
    :param index: The index of the target point.
    :param n: The number of points in the subset.
    :return: A subset of points around the specified index.
    """
    left = index  # Инициализация левой границы индексом
    right = index  # Инициализация правой границы индексом
    
    # Итерация для выбора 'n' точек вокруг указанного индекса
    for i in range(n - 1):
        # Переключение между движением влево и вправо от центрального индекса
        if i % 2 == 0:
            if left == 0:  # Обеспечение, чтобы левая граница не выходила за 0
                right += 1  # Перемещение правой границы вправо
            else:
                left -= 1  # Перемещение левой границы влево
        else:
            if right == len(points) - 1:  # Обеспечение, чтобы правая граница не превышала длину списка
                left -= 1  # Перемещение левой границы влево
            else:
                right += 1  # Перемещение правой границы вправо
    return points[left:right + 1]  # Возврат подмножества точек


# Вычисление многочлена Ньютона и сохранение результатов в таблице
def newton_method(point_table):
    """
    Calculates the coefficients of the Newton polynomial and stores them in a table.
    
    :param point_table: List of points.
    :return: Table of coefficients of the Newton polynomial.
    """
    count_of_rows_of_table_data = 2  # Начальное количество строк в таблице
    table_of_sub = []  # Инициализация таблицы
    
    # Создание таблицы с x и y значениями точек
    [table_of_sub.append([point.get_x(), point.get_y()]) for point in point_table]
    
    # Транспонирование таблицы для удобства доступа к строкам
    table_of_sub = list([list(row) for row in np.transpose(table_of_sub)])
    x_row = table_of_sub[0]  # Получение строки значений x

    # Добавление столбцов (строк в моей реализации)
    for count_of_args in range(1, len(x_row)):
        table_of_sub.append([])  # Добавление новой строки для коэффициентов
        cur_y_row = table_of_sub[len(table_of_sub) - count_of_rows_of_table_data]  # Получение текущей строки значений y

        # Добавление следующего элемента
        # Перебор каждой точки для вычисления разделенных разностей и заполнения таблицы
        for j in range(0, len(x_row) - count_of_args):
            # Проверка, если соседние значения y равны бесконечности
            if cur_y_row[j] == infinity and cur_y_row[j + 1] == infinity:
                cur = 1  # Если оба значения бесконечны, устанавливаем разделенную разность равной 1 (для стабильности)
            # Проверка, если левое значение y равно бесконечности
            elif cur_y_row[j] == infinity:
                cur = cur_y_row[j + 1] / (x_row[j] - x_row[j + count_of_args])  # Вычисление разделенной разности
            # Проверка, если правое значение y равно бесконечности
            elif cur_y_row[j + 1] == infinity:
                cur = cur_y_row[j] / (x_row[j] - x_row[j + count_of_args])  # Вычисление разделенной разности
            else:
                # Вычисление разделенной разности по формуле: (f(x_j) - f(x_{j+1})) / (x_j - x_{j+count_of_args})
                cur = (cur_y_row[j] - cur_y_row[j + 1]) / (x_row[j] - x_row[j + count_of_args])
            
            # Добавление вычисленной разделенной разности в таблицу
            table_of_sub[count_of_args + count_of_rows_of_table_data - 1].append(cur)
    return table_of_sub  # Возврат таблицы коэффициентов



# Вычисление многочлена Ньютона и возвращение приближенного значения в точке x
def newton_polynomial(point_table, n, x):
    """
    Calculates the approximate value of the function at a given point x using interpolation by the Newton polynomial.
    
    :param point_table: List of points.
    :param n: The number of points to interpolate.
    :param x: The value of x.
    :return: The approximate value of the function at point x.
    """
    # Выбор подмножества точек вокруг заданной точки x
    working_table = get_working_points(point_table, get_index(point_table, x), n)
    
    # Вычисление коэффициентов многочлена Ньютона с использованием разделенных разностей
    subs = newton_method(working_table)
    
    # Вычисление и возврат приближенного значения в точке x
    return calc_approximate_value(subs, n, x)



# Нахождение второй производной многочлена Ньютона в заданной точке x
def find_derivative_newton_polynomial(point_table, n, x):
    """
    Calculates the second derivative of the Newton polynomial at a given point x.
    
    :param point_table: List of points.
    :param n: The number of points to interpolate.
    :param x: The value of x.
    :return: The second derivative of the Newton polynomial at point x.
    """
    # Выбор подмножества точек вокруг заданной точки x
    working_table = get_working_points(point_table, get_index(point_table, x), n)
    
    # Вычисление коэффициентов многочлена Ньютона с использованием разделенных разностей
    subs = newton_method(working_table)

    # Определение функции, соответствующей многочлену Ньютона
    def aprox_func(x):
        res = 0
        for i in range(len(subs)):
            res += subs[i][0] * x ** i
        return res

    # Вычисление второй производной численно с использованием функции derivative из scipy
    y_derivative_n_2 = derivative(aprox_func, x, n=2, dx=1e-6)
    return y_derivative_n_2



# Вычисление окончательного результата с использованием интерполяции методом Ньютона
def calc_approximate_value(tableOfSub, n, x):
    """
    Calculates the final result using Newton's interpolation method based on the provided coefficient table.
    
    :param tableOfSub: Table of coefficients of the Newton polynomial.
    :param n: The number of points used for interpolation.
    :param x: The target value of x.
    :return: The final result of the interpolation at x.
    """
    countOfArgs = 2  # Начальное количество аргументов

    # Инициализация суммы первым коэффициентом полинома
    if tableOfSub[1][0] == infinity:
        sum = tableOfSub[1][1]
    else:
        sum = tableOfSub[1][0]

    mainPart = 1  # Инициализация главной части полинома
    
    # Итерация по коэффициентам для вычисления значения полинома при x
    for i in range(n - 1):
        # Вычисление главной части полинома
        if tableOfSub[0][i] == infinity:
            mainPart *= x
        else:
            mainPart *= (x - tableOfSub[0][i])

        # Проверка, что следующий коэффициент не равен бесконечности
        if tableOfSub[i + countOfArgs][0] != infinity:
            # Добавление произведения главной части и коэффициента к сумме
            sum += mainPart * tableOfSub[i + countOfArgs][0]
    
    return sum  # Возврат окончательного результата интерполяции при x




# вывод таблицу всех данных f(xi .... xn)
def printSubTable(subTable):
    countArray = len(subTable)
    maxLen = len(subTable[0])
    print(("+" + "-" * 22) * countArray + "+")
    print("| {:^20s} | {:^20s}".format("X", "Y"), end=' ')
    for k in range(2, countArray):
        print("| {:^20s}".format("Y" + "\'" * (k - 1)), end=' ')
    print("|")
    print(("+" + "-" * 22) * countArray + "+")

    for i in range(maxLen):
        for j in range(countArray):
            if j >= countArray - i:
                print("| {:^20s}".format(" "), end=' ')
            else:
                print("| {:^20.10f}".format(subTable[j][i]), end=' ')
        print("|")

    print(("+" + "-" * 22) * countArray + "+")

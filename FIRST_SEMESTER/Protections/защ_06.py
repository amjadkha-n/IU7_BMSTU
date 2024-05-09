#list1 = list(map(int, input("Please enter the elements of the list: ").split()))
'''list1 = [1, 2, 3, 4, 3, 2, 1, 2, 3, 4, 3, 2, 1, 2, 3, 4]
ind = []
print(list1)
new_list = list1
for i in range(1, len(list1) - 1):
    if list1[i] > list1[i + 1] and list1[i] > list1[i - 1] or (
        list1[i] < list1[i + 1] and list1[i] < list1[i - 1]):
        ind.append(i)
print(ind)
k = int(input("Please enter the value of k: "))
l = int(input("Please enter the value of l: "))
if k > len(ind) - 1 or k <= 0:
    print("Values are exceeding from the length of list")
    exit()
if l > len(ind) - 1 or k <= 0:
    print("Values are exceeding from the length of list")
    exit()
sum = 0
ind_1 = ind
for i in range(len(list1) - 1):
    if i == ind_1[k]:
        sum = list1[i + 1] + list1[i + 2]

for i in range(len(list1) - 1):
    if i == ind[l - 1]:
        list1[i] = sum
print(list1)'''


#list1 = list(map(int, input("Please enter the elements of the list: ").split()))
'''list1 = [-5, -3, 2, 1, -5, -5, -3, -2, 0]


l_seq = []
max_seq = []

for i in range(len(list1)):
    if list1[i] < 0 and list1[i] % 2 == 1 and list1[i] % 2 :
        l_seq.append(list1[i])
    else:
        if len(l_seq) > len(max_seq):
            max_seq = l_seq
        l_seq = []
if len(l_seq) > len(max_seq):
    max_seq = l_seq
print(max_seq)'''




'''print('Find the row that has the highest arithmetic mean')
n = int(input('Enter the number of rows: '))
matrix = []
for i in range(n):
    matrix.append(list(map(int, input(f'Enter the elements of the rows, separated by a space: ').split())))

# Condition, checks if the matrix is rectangular
for i in range(1,n):
    if len(matrix[i]) != len(matrix[0]):
        # Exception
        raise IndexError('The matrix must be rectangular')

# printing matrix
for i in range(n):
    for num in matrix[i]:
        print(num, end=" ")
    print()'''


'''R, C = map(int, input("Please enter the number of rows and columns: ").split())
if R == C:
    print("Given matrix is not a rectangular matrix")
    exit()
else:
    matrix = []
    for i in range(R):
        a = []
        for j in range(C):
            a.append(int(input(f"Please enter the element of the {i+1} row and {j+1} column: ")))
        matrix.append(a)

for i in range(R):
    for j in range(C):
        print(f"{matrix[i][j]:^6.5g}", end = " ")
    print()

ind, max_row = 0, 0
for i, lst in enumerate(matrix):
    count = 0
    sum = 0
    for num in lst:
        sum += num
        count += 1
    average = round(sum / count, 5)
    if average > max_row:
        max_row = average
        ind = i
if max_row > 0:
    print(f"Row that has the highest arithmetic mean is {matrix[ind]}")
else:
    print("Matrix is empty")'''
'''

arr1 = list(map(int, input("Please enter the elements of the first array: ").split()))
arr2 = list(map(int, input("Please enter the elements of the second array: ").split()))

i, j, k = 0, 0, 0
n1 = len(arr1)
n2 = len(arr2)
arr3 = [0] * (n1 + n2)
while i < n1 and j < n2:
    arr3[k] = arr1[i]
    k += 1
    i += 1
    arr3[k] = arr2[j]
    k +=1 
    j += 1
while i < n1:
    arr3[k] = arr1[i]
    k += 1
    i += 1
while j < n2:
    arr3[k] = arr1[j]
    k += 1
    j += 1
min_num = max_num = -1
for i in range(len(arr3)):
    if (arr3[i] % 2 == 0 and arr3[i] > 0) and (min_num == -1 or arr3[min_num] < arr3[i]):
        min_num = i
    if (arr3[i] % 2 == 1 and arr3[i] < 0) and (max_num == -1 or arr3[max_num] < arr3[i]):
        max_num = i
temp = min_num
min_num = max_num
max_num = temp
for i in arr3:
    if i == min_num:
        i = max_num
    if i == max_num:
        i = min_num
print(arr3)'''
'''
R, C = map(int, input("Please enter the number of rows and columns: ").split())
M = [[int(input(f"Please enter the element of {i + 1} row and {j + 1} column: "))for j in range(C)]for i in range(R)]
import sys
ind, max_col = 0, sys.maxsize
col = -1
for i in range(len(M[0])):
    count = 0
    for j in range(len(M)):
        if M[j][i] % 2 == 1:
            count += 1
    if count != 0 and count < max_col:
        max_col = count
        col = i
if col == -1 or max_col == sys.maxsize:
    print("No prime numbers found in the matrix")
else:
    print(f"Column that has the largest number of prime numbers have is {col + 1} column of the matrix, and the amount is {max_col}")
        '''

        # Сидякина Елена ИУ7-16Б
'''
Требуется написать программу для вычисления приближённого значения интеграла
известной, заданной в программе, функции двумя разными методами.
Методом парабол и серединных прямоугольников.
'''
import math as m
eps0 = 10e-8
def f(x):  #функция
    y = x**2
    return y

def f0(x):  #пеервообразная функции
    y = x**3/3
    return y

def Method1(n, f): #метод серединных прямоугольников
    start = a
    stop = b
    h = (stop - start) / n
    s = 0
    for i in range(n):
        s += f(start + h / 2)
        start += h
    s *= h
    return s

def Method2(n, f): #метод парабол
    if n % 2 == 0:
        start = a
        stop = b
        h = (stop - start) / n
        s = f(start) + f(stop)  
        for i in range(1, n):
            s += (3 - (-1)**i)*f(start + i * h)
        s *= h / 3
        return s
    else:
        return m.nan

try: #проверяем данные на корректность
    a = float(input("Введите начало интегрируемого отрезка: "))
    b = float(input("Введите конец интегрируемого отрезка: "))
    n1 = int(input("Введите количество отрезков разбиения в первом случае: "))
    n2 = int(input("Введите количество отрезков разбиения во втором случае: "))
    eps = float(input("Введите допустимую погрешность: "))
    if (a - b) > eps0 or n1 <= 0 or n2 <= 0:
        print('Введены некорректные данные.')
    else:
        I = f0(b) - f0(a)
        count = 1
        print('_' * 46)  # вывод таблицы значений интегралов
        print('|' + ' ' * 14 + '|' + ' ' * 6 + 'N1' + ' ' * 6 + '|'
              + ' ' * 6 + 'N2' + ' ' * 6 + '|')
        print('_' * 46)
        print('|   Метод 1    |{:^14.6g}|{:^14.6g}|'.format(Method1(n1, f), Method1(n2, f)))
        print('_' * 46)
        print('|   Метод 2    |{:^14.6g}|{:^14.6g}|'.format(Method2(n1, f), Method2(n2, f)))
        print('_' * 46)
        print("Абсолютная погрешность первого метода разбиения на n1: {:^12.6g}"
              .format(abs(Method1(n1, f) - I)))
        print("Относительная погрешность первого метода разбиения на n1: {:^12.6g}"
              .format(abs(Method1(n1, f) - I) / abs(I)))
        if n1 % 2 == 0:
            print("Абсолютная погрешность второго метода разбиения на n1: {:^12.6g}"
                .format(abs(Method2(n1, f) - I)))
            print("Относительная погрешность второго метода разбиения на n1: {:^12.6g}"
                  .format(abs(Method2(n1, f) - I) / abs(I)))
        else:
            print('Невозможно посчитать погрешности методом парабол для n2.')
        print("Абсолютная погрешность первого метода разбиения на n2: {:^12.6g}"
              .format(abs(Method1(n2, f) - I)))
        print("Относительная погрешность первого метода разбиения на n2: {:^12.6g}"
              .format(abs(Method1(n2, f) - I) / abs(I)))
        if n2 % 2 == 0:
            print("Абсолютная погрешность второго метода разбиения на n2: {:^12.6g}"
                  .format(abs(Method2(n2, f) - I)))
            print("Относительная погрешность второго метода разбиения на n2: {:^12.6g}"
                  .format(abs(Method2(n2, f) - I) / abs(I)))
        else:
            print('Невозможно посчитать погрешности методом парабол для n2.')
        if n1 % 2 == 0:
            if abs(I - Method2(n1, f)) > abs(I - Method1(n1, f)):
                while abs(Method2(count, f) - Method2(count * 2, f)) > eps:
                    count += 1
                print('Метод серединных прямоугольников наиболее эффективен.\n'
                        'Необходимо {} отрезков разбиения для вычисления интеграла методом парабол'
                      ' с точностью {:.6g}'.format(count, eps))
            else:
                while abs(Method1(count, f) - Method1(count * 2, f)) > eps:
                    count += 1
                print('Метод парабол наиболее эффективен.\n'
                        'Необходимо {} отрезков разбиения для вычисления интеграла методом серединных прямоугольников'
                      'с точностью {:.6g}'.format(count, eps))
        elif n2 % 2 == 0:
            if abs(I - Method2(n2, f)) > abs(I - Method1(n2, f)):
                while abs(Method2(count, f) - Method2(count * 2, f)) > eps:
                    count *= 2
                print('Метод серединных прямоугольников наиболее эффективен.\n'
                        'Необходимо {} отрезков разбиения для вычисления интеграла методом парабол'
                      ' с точностью {:.6g}'.format(count, eps))
            else:
                while abs(Method1(count, f) - Method1(count * 2, f)) > eps:
                    count *= 2
                print('Метод парабол наиболее эффективен.\n'
                        'Необходимо {} отрезков разбиения для вычисления интеграла методом серединных прямоугольников'
                      'с точностью {:.6g}'.format(count, eps))
        else:
            while abs(Method1(count, f) - Method1(count * 2, f)) > eps:
                count *= 2
            print('Метод парабол невозможно использовать.\n'
                  'Необходимо {} отрезков разбиения для вычисления интеграла методом серединных прямоугольников'
                  ' с точностью {:.6g}'.format(count, eps))
except ValueError as e:
    print('Нужно ввести число.')
except Exception as e:
    print('Произошла неизвестная ошибка. Проверьте корректность данных.')
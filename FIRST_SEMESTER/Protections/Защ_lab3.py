#1
'''
def outer():
    x = 1
    def inner():
        print("x in outer function: ", x)
    return inner
'''
#2
'''
def mul(a):
    def helper(b):
        return a * b
    return helper
a = mul(5)
b = mul(10)
print(a)
print(a(4), b(4))

'''
#3

'''
import time
def fib():
    x1 = 0
    x2 = 1
    def get_next_number():
        nonlocal x1, x2
        x3 = x1 + x2
        x1, x2 = x2, x3
        return x3
    return get_next_number

fibonacci = fib()
for i in range(2,10):
    num = fibonacci()
    print(f"The {i}th fibonacci number is {num}")

def fib_recursion(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fib_recursion(n - 1) + fib_recursion(n -2)
def fib_closure(n):
    f = fib()
    for i in range(2, n + 1):
        num = f()
    return num
t1 = time.time()
print(fib_closure(35))

t2 = time.time()
print("with closure", t2 - t1)
t1 = time.time()
t2 = time.time()
'''
#4
'''
def f(x):
    return x * x
def modify_list(L, fn):
    for idx, v in enumerate(L):
        L[idx] = fn(v)
A = [1, 2, 3]
modify_list(A,f)
print(A)

f2 = lambda x: 2 * x 
modify_list(A, f2)
print(A)
modify_list(A, lambda x, y = 1: x + y)
print(A)
'''

# 5
'''
from cProfile import label


a = [2, 3, 4, 5]
b = [5, 6, 7]

c = map(lambda x: 2 * x, a)
print(c)

for i in c:
    print(i)
print()

for i in map(lambda x: 2 * x, b):
    print(i)
e = map(lambda x:2 * x, b)
print(e)
print()
d = map(lambda x, y: y * x, a, b)
for i in d:
    print(i)
print()
c = map(max, range(1, 10), range(10, 1, -1))
for i in c:
    print(i)
'''
# 6
'''
a = list(range(2, 10))
b = filter(lambda x : x % 2 == 0, a)
print(list(b))
s_list = map(chr, range(ord("A"), ord('z') + 1))
s = ''.join(list(s_list))
print(s)

vowels = filter(lambda l: l.lower() in 'ariou', s)
print(str(list(vowels)))
'''

#7
'''
def f(c):
    print(ord(c), '\t', c, '\t\t')
ascii = ''.join(map(chr, range(32, 120)))
#print(ascii)
for i in map(f, ascii):
    pass
'''

# 8
'''
from functools import reduce

items = [1, 2,3,4,5]

def f(x, y):
    print(x, y)
    return x + y
sum_all = reduce(lambda x, y: x + y, items)
sum_all = reduce(f, items, 0)

print('sum', sum_all)

print()
from functools import reduce 
iterms = [1, 24, 17, 14, 9, 32, 2]
all_max = reduce(lambda a, b: a if (a > b) else b, iterms)
print(all_max)
'''
# 9
'''
a = [1, 2, 3]
b = "xyz"
c = [None, True]

res = list(zip(a, b, c))
print(res)

'''

# 10
'''
def f(a):
    print("main f:", a)
from pty import slave_open
from slave import f

def f(a):
    print('main_f 2', a)
'''

###
'''
x1 = float(input("Insert the first value: "))
x2 = float(input("Insert the final value:  "))   # Ввод данных
step = float(input("Insert the step: "))

a = []
x = x1
while x <= x2:
    y = x**2 - 25
    x += step
    a.append(y)
y_max = max(a)
y_min = min(a)

print()
print('y min= ','{:.2f}'.format(y_min),'̅'*85,'y max= ','{:.2f}'.format(y_max))
print()


n = int(((x2 - x1)/step)) + 1
for x in range(n):
  x = x1 + step*x
  y = x**2 - 25    # График

  print('|','{:5.1f}'.format(x),' '*round(((y-y_min)/(y_max-y_min))*80),'*')
'''

'''
n = int(input("Please enter the amount of lists: "))

lists = []

for i in range(n):
    lists.append(list(map(int, input("please enter the elements of the lists: ").split())))
ind, max_elem = 0, 0
for i, lst in enumerate(lists):
    count = 0
    for elem in range(0, len(lst), 3):
        if lst[elem] * lst[elem + 1] == lst[elem + 2]:
            count += 1
    if count > max_elem:
        max_elem = count
        ind = i
print(lists[ind]) 

'''

'''
list1 = list(map(int, input("Please enter the elements of the list: ").split()))
min_ind = max_ind = -1
#for j in list1:
#    if j < 0:
#        continue
#    else:
#        print("No negative numbers found")
#        exit()
for i in range(len(list1)):
    if list1[i] < 0 and (max_ind == -1 or list1[max_ind] < list1[i]):
        max_ind = i
    if list1[i] < 0 and (min_ind == -1 or list1[min_ind] > list1[i]):
        min_ind = i
print(f"min negative number = {list1[min_ind]} and max negative number = {list1[max_ind]}")'''

# Сидякина Елена ИУ7-16Б
# 1. Даны массивы D и F. Сформировать матрицу A по формуле
# ajk = sin(dj+fk)
# Определить среднее арифметическое положительных чисел каждой строки
# матрицы и количество элементов, меньших среднего арифметического.
# Результаты записать соответственно в массивы AV и L. Напечатать матрицу A в
# виде матрицы и рядом столбцы AV и L.
import math
# D = [1,2,10,7]
n = int(input("Введите длину массива D: "))
D = []
for i in range(n):
    D.append(int(input('Введите {}-й элемент массива D: '.format(i+1))))
# F = [5,9,7,8]
m = int(input("Введите длину массива F: "))
F = []
for i in range(m):
    F.append(int(input('Введите {}-й элемент массива F: '.format(i+1))))
A = []
AV = [0] * n
L = [0] * n
for j in range(n):
    A.append([])
    for k in range(m):
        A[j].append([])
for j in range(n):
    for k in range(m):
        A[j][k] = math.sin(D[j] + F[k])
for j in range(n):
    sm = 0
    cnt = 0
    for k in range(m):
        if A[j][k] > 0:
            sm += A[j][k]
            cnt += 1
    if cnt == 0:
        AV[j] = 0
    else:
        AV[j] = sm / cnt
for j in range(n):
    cntm = 0
    for k in range(m):
        if A[j][k] < AV[j]:
            cntm += 1
    L[j] = cntm
print('\nВведённая матрица:')
for i in range(n):
    for j in range(m):
        print('{:^12.6g}'.format(A[i][j]), end = '')
    print('{:^12.6g}'.format(AV[i]), end = '')
    print('{:^12.6g}'.format(L[i]))
    print()
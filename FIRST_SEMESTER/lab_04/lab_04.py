# Факирзаи Амджад
# ИУ7И-16Б
# fourth lab

# z1 = a ** 3 - 19.1 * a ** 2 + 27.9 * a + 5.58
# z2 = a **2 - sin * pi * a
# operator : for
import math as m
from math import *

a0 = float(input("Please enter the initial value: "))
h = float(input("Please enter the step: "))
an = float(input("Please enter the final value: "))
#a0, h, an = -100, 10, 100
steps = []
a = a0
while a < an:
    steps.append(a)
    a += h
steps.append(an)
print('-' * 31 + '\n|' + 'a'.center(9) + '|' + 'z1'.center(9) + '|' + 'z2'.center(9) + '|'
'\n' + '-' * 31)

def f(a):
    return [a ** 3 - 19.1 * a ** 2 + 27.9 * a + 5.58, a ** 2 - (m.sin(pi * a))] # Functions

a = a0
for a in steps:
    res = f(a)
    print(f"|{a:^9.2g}|{res[0]:^9.2g}|{res[1]:^9.2g}|") # h = steps, a = initial value, res[] = result of the funtion
    #h += h
print('-' * 31)

notch = int(8) # quantity of the y values
y0 = f(a0)
y_max = y0
y_min = y0
a = a0
for a in steps:
    res = f(a)
    y_max = [max(res[0], y_max[0]), max(res[1], y_max[1])]
    y_min = [min(res[0], y_min[0]), min(res[1], y_min[1])]


mid = (y_max[0] - y_min[0]) / (notch - 1)
#num = int(77 / notch - 1)

print(" " * 7, end = '')
i = 0
for i in range(notch - 1):
    print(f"{round(y_min[0] + i * mid, 3):<11.2g}", end = "")
print(round(y_max[0], 3))
eps = 1e-2



if y_min[0] > eps:
    for x in steps:
        res = f(x)
        print(f"{x:>7.1f} ", end = "")
        flag = flag1 = True
        for i in range(79):
            if flag and i * (y_max[0] - y_min[0]) / 78 >= res[0] - y_min[0]:
                print("*", end = "")
                flag = False
                if flag1 and i * (y_max[0] - y_min[0]) / 78 >= abs(y_min[0]):
                    flag1 = False
            elif flag1 and i * (y_max[0] - y_min[0]) / 78 >= abs(y_min[0]):
                print(" ", end = "")
                flag1 = False
            elif not flag1 and not flag:
                break
            else:
                print(" ", end = "")
        print(" ")
else:
    for x in steps:
        res = f(x)
        print(f"{x:>7.1f} ", end = "")
        flag = flag1 = True
        for i in range(79):
            if flag and i * (y_max[0] - y_min[0]) / 78 >= res[0] - y_min[0]:
                print("*", end = "")
                flag = False
                if flag1 and i * (y_max[0] - y_min[0]) / 78 >= abs(y_min[0]):
                    flag1 = False
            elif flag1 and i * (y_max[0] - y_min[0]) / 78 >= abs(y_min[0]):
                print("|", end = "")
                flag1 = False
            elif not flag1 and not flag:
                break
            else:
                print(" ", end = "")
        print(" ") 
        

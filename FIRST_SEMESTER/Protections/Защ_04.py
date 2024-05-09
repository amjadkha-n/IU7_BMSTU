import math as m
from math import *

x0 = float(input("Please enter the initial value: "))
h = float(input("Please enter the step: "))
xn = float(input("Please enter the final value: "))
print()
import math as m
print()
x = x0
steps = []

while x < xn:
    steps.append(x)
    x += h
steps.append(xn)
def f(x):
    return x ** 2 - 25
a = x0
notch = int(8)
y0 = f(x0)
y_max = y0
y_min = y0
for x in steps:
    res = f(x)
    y_max = max(res, y_max)
    y_min = min(res, y_min)
eps = 1e-2
if y_min > eps:
    for x in steps:
        res = f(x)
        print(f"{x:>7.1g}", end = "")
        flag = flag1 = True
        for i in range(79):
            if flag and i * (y_max - y_min) / 78 >= res - y_min:
                print("*", end = "")
                flag = False
                if flag1 and i * (y_max - y_min) / 78 >= abs(y_min):
                    flag1 = False
            elif flag1 and i * (y_max - y_min) / 78 >= abs(y_min):
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
        print(f"{x:>7.1f}", end = "")
        flag = flag1 = True
        for i in range(79):
            if flag and i * (y_max - y_min) / 78 >= res - y_min:
                print("*", end = "")
                flag = False
                if flag1 and i * (y_max - y_min) / 78 >= abs(y_min):
                    flag1 = False
            elif flag1 and i * (y_max - y_min) / 78 >= abs(y_min):
                print("|", end = "")
                flag1 = False
            elif not flag and not flag1:
                break
            else:
                print(" ", end = "")
        print(" ")




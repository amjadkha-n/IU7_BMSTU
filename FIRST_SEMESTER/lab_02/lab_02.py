# Факирзаи Амджад 
# ИУ7И-16Б
# Lab No-2
# квадратное уравнение

from math import sqrt

a = float(input("Please enter the first number: "))
b = float(input("Please enter the second number: "))
c = float(input("Please enter the third number: "))
eps = 1e-5
if abs(a) < eps:
    if abs(b) < eps:
        if abs(c) < eps:
            print("x-любое")
        else:
            print("No Solutions")
    else:
        x = - c / b
        print(f"x = {x:.4f}")
else:
    D = b * b - 4 * a * c
    if abs(D) < eps:
        x = - b / (2 * a)
        print(f"x = {x:.4f}")
            
    elif D > 0:
        D = sqrt(D)
        x1 = (- b - D) / (2 * a)
        x2 = (- b + D) / (2 * a)
        print(f"x1 = {x1:.4f} and x2 = {x2:.4f}")
    elif D < 0:
        print("No real roots existed")
   

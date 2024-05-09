# Факирзаи Амджад
# ИУ7И-16Б
# Third lab
'''
Написать программу, которая по введенным целочисленным координатам трех точек на плоскости вычисляет длины сторон
образованного треугольника и длину высоты, проведенной из наименьшего угла.
Определить, является ли треугольник остроугольным.Далее вводятся координаты точки. Определить, находится ли
точка внутри треугольника. Если да, то найти расстояние от точки до наиболее удаленной стороны треугольника или ее
продолжения.
'''
import math as m

print("Enter the coordinates of the first point")
xA = int(input("Please enter the X coordinate of the first point: "))
yA = int(input("Please enter the Y coordinate of the first point: "))
print("Enter the coordinates of the second point")
xB = int(input("Please enter the X coordinate of the second point: "))
yB = int(input("Please enter the Y coordinate of the second point: "))
print("Please enter the coordinates of the third point")
xC = int(input("Please enter the X coordinate of the third point: "))
yC = int(input("Please enter the Y coordinate of the third point: "))

# Lengths of the sides of the traingle
AB = m.sqrt((xB - xA) ** 2 + (yB - yA) ** 2) # c
BC = m.sqrt((xC - xB) ** 2 + (yC - yB) ** 2) # a
AC = m.sqrt((xC - xA) ** 2 + (yC - yA) ** 2) # b

print(f"a = {BC:.3g}")
print(f"b = {AC:.3g}")
print(f"c = {AB:.3g}")

a, b, c = BC, AC, AB
S = (a + b + c) / 2                # Formula of the semi parameter
A = m.sqrt(S*(S - a)*(S - b)*(S - c)) # Formula of the area of the traingle
print(f"Area = {A:.4g}")
BC2, AC2, AB2 = BC, AC, AB
if AB == 0 or BC == 0 or AC == 0:
    print("Sides are zero")
    exit(-1)
else:
    cosA = (AB2 + AC2 - BC2) / (2 * m.sqrt(AB2 * AC2))
    cosB = (AB2 + BC2 - AC2) / (2 * m.sqrt(AB2 * BC2))
    cosC = (AC2 + BC2 - AB2) / (2 * m.sqrt(AC2 * BC2))

    if cosA < cosB and cosA < cosC:
        lowest_angle = cosA
    elif cosB < cosA and cosB < cosC:
        lowest_angle = cosB
    else:
        lowest_angle = cosC


    if lowest_angle == cosA:
        base = a
        height = (2 * A) / base        # Formula of the height of the traingle
    elif lowest_angle == cosB:
        base = b
        height = (2 * A) / base
    else:
        base = c
        height = (2 * A) / base
    print(f"Height = {height:.5f}")

a1 = pow(a, 2)
b1 = pow(b, 2)
c1 = pow(c, 2)
eps = 1e-2

if a1 + b1 > c1 or b1 + c1 > a1 or a1 + c1 > b1:
    print("Given traingle is acute-angled triangle")
else:
    print("This is a traingle")


xP = int(input("Please enter the x coordinate of the point: "))
yP = int(input("Please enter the Y coordinate of the point: "))

A1 = abs((xA * (yB - yP) + xB * (yP - yA) + xP * (yA - yB)) / 2) # PAB
A2 = abs((xP * (yB - yC) + xB * (yC - yP) + yC * (yP - yB)) / 2) # PBC
A3 = abs((xA * (yP - yC) + xP * (yC - yA) + xC * (yA - yP)) / 2) # PAC
Sum = A1 + A2 + A3

print(A1, A2, A3)
if sum < eps or A == 0:
    print("Points are zero")
elif abs(Sum - A) < eps:
    print("Point is in the triangle")
    if AB < eps or BC < eps or AC < eps:
        print("Cordinates are zero")
    else:
        
        far_point = (2 * A1) / AB
        if far_point < (2 * A2) / BC:
            far_point = (2 * A2) / BC
        elif far_point < (2 * A3) / AC:
            far_point = (2 * A3) / AC
        print(f"Farthest point = {far_point:.4g}")
else:
    print("Point is not in the triangle")
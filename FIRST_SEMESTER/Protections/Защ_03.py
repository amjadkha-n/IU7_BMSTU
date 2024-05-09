'''
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
#a0, h, an = -10, 0.9, 10
a = a0
print('-' * 31 + '\n|' + 'a'.center(9) + '|' + 'z1'.center(9) + '|' + 'z2'.center(9) + '|'
'\n' + '-' * 31)

a = a0
a1 = a0
for i in range(1):
  res_1 = a ** 3 - 19.1 * a ** 2 + 27.9 * a + 5.56
  res_2 = a ** 2 - (m.sin(pi * a))
  first_value = res_1
y_max = y_min = first_value
a = a0
while a < an:
  res_1 = a ** 3 - 19.1 * a ** 2 + 27.9 * a + 5.56
  res_2 = a ** 2 - (m.sin(pi * a))
  print((f"|{a:^9.2g}|{res_1:^9.2g}|{res_2:^9.2g}|"))

  if y_max < res_1:
    y_max = res_1
  
  if y_min > res_1:
    y_min = res_1
  
  a += h

else:
  a = an
  res1 = a ** 3 - 19.1 * a ** 2 + 27.9 * a + 5.56
  res2 = a ** 2 - (m.sin(pi * a))
  print(f"|{an:^9.2g}|{res1:^9.2g}|{res2:^9.2g}|")
  if y_max < res1:
    y_max = res1
  if y_min > res1:
    y_min = res1
print("-" * 31)

notch = int(8) # quantity of the y values
mid = (y_max - y_min) / (notch - 1)

print(" " * 7, end = '')
i = 0
for i in range(notch - 1):
    print(f"{round(y_min + i * mid, 3):<11.2g}", end = "")
print(f"{round(y_max, 3)}")
eps = 1e-2
a = a0
a1 = a0
if y_min > eps:
  while a < an:
    res_1 = a ** 3 - 19.1 * a ** 2 + 27.9 * a + 5.56
    print(f"{a:>7.1f} ", end = "")
    a += h
    a1 + h
    flag = flag1 = True
    for i in range(79):
      if flag and i * (y_max - y_min) / 78 >= res_1 - y_min:
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
    a = an
    res_1 = a ** 3 - 19.1 * a ** 2 + 27.9 * a + 5.56
    print(f"{a:>7.1f}", end = "")
       
    flag = flag1 = True
    for i in range(79):
      if flag and i * (y_max - y_min) / 78 >= res_1 - y_min:
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
  while a < an:
    res_1 = a ** 3 - 19.1 * a ** 2 + 27.9 * a + 5.56
    print(f"{a:>7.1f} ", end = "")
    a += h
    a1 += h
      #else:
          #  print(f"{an:>7.1f}")
            
    flag = flag1 = True
    for i in range(79):
      if flag and i * (y_max - y_min) / 78 >= res_1 - y_min:
        print("*", end = "")
        flag = False
        if flag1 and i * (y_max - y_min) / 78 >= abs(y_min):
          flag1 = False
      elif flag1 and i * (y_max - y_min) / 78 >= abs(y_min):
        print("|", end = "")
        flag1 = False
      elif not flag1 and not flag:
        break
      else:
        print(" ", end = "")
    print(" ") 

  else:
    a = an
    res_1 = a ** 3 - 19.1 * a ** 2 + 27.9 * a + 5.56

    print(f"{a:>7.1f}", end = "")
       
    flag = flag1 = True
    for i in range(80):
      if flag and i * (y_max - y_min) / 80 >= res_1 - y_min:
        print("*", end = "")
        flag = False
        if flag1 and i * (y_max - y_min) / 80 >= abs(y_min):
          flag1 = False
      elif flag1 and i * (y_max - y_min) / 80 >= abs(y_min):
        print("|", end = "")
        flag1 = False
      elif not flag1 and not flag:
        break
      else:
        print(" ", end = "")
    print(" ")    
'''
import math as m
pi=3.14
z0 = float(input("Please enter the initial value: "))
h = float(input("Please enter the step: "))
zn = float(input("Please enter the final value: "))

z = z0
print('-' * 31 + '\n|' + 'a'.center(9) + '|' + 'z1'.center(9) + '|' + 'z2'.center(9) + '|'
'\n' + '-' * 31)

z = z0
z1 = z0
for i in range(1):
  res_1 = z ** 4 - 3 * z * 3 + 8 * z**2 - 5
  res_2 = 10.125*m.sqrt(abs(z)) - 20.15 * m.cos(pi/2 *z)
  first_value = res_1
y_max = y_min = first_value
z = z0
while z < zn:
  res_1 = z ** 4 - 3 * z * 3 + 8 * z**2 - 5
  res_2 = 10.125*m.sqrt(abs(z)) - 20.15 * m.cos(pi/2 *z)
  print((f"|{z:^9.2g}|{res_1:^9.2g}|{res_2:^9.2g}|"))

  if y_max < res_1:
    y_max = res_1
  
  if y_min > res_1:
    y_min = res_1
  
  z += h

else:
  z = zn
  res1 = z ** 4 - 3 * z * 3 + 8 * z**2 - 5
  res2 = 10.125*m.sqrt(abs(z)) - 20.15 * m.cos(pi/2 *z)
  print(f"|{zn:^9.2g}|{res1:^9.2g}|{res2:^9.2g}|")
  if y_max < res1:
    y_max = res1
  if y_min > res1:
    y_min = res1
print("-" * 31)

notch = int(8) # quantity of the y values
mid = (y_max - y_min) / (notch - 1)

print(" " * 7, end = '')
i = 0
for i in range(notch - 1):
    print(f"{round(y_min + i * mid, 3):<11.2g}", end = "")
print(f"{round(y_max, 3)}")
eps = 1e-2
z = z0
z1 = z0
if y_min > eps:
  while z < zn:
    res_1 = z ** 4 - 3 * z * 3 + 8 * z**2 - 5
    print(f"{z:^7.1f} ", end = "")
    z += h
    z1 + h
    flag = flag1 = True
    for i in range(79):
      if flag and i * (y_max - y_min) / 78 >= res_1 - y_min:
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
    z = zn
    res_1 = z ** 4 - 3 * z * 3 + 8 * z**2 - 5
    print(f"{z:^7.1f}", end = "")
       
    flag = flag1 = True
    for i in range(79):
      if flag and i * (y_max - y_min) / 78 >= res_1 - y_min:
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
  while z < zn:
    res_1 = z ** 4 - 3 * z * 3 + 8 * z**2 - 5
    print(f"{z:^7.1f} ", end = "")
    z += h
    z1 += h
      #else:
          #  print(f"{zn:>7.1f}")
            
    flag = flag1 = True
    for i in range(79):
      if flag and i * (y_max - y_min) / 78 >= res_1 - y_min:
        print("*", end = "")
        flag = False
        if flag1 and i * (y_max - y_min) / 78 >= abs(y_min):
          flag1 = False
      elif flag1 and i * (y_max - y_min) / 78 >= abs(y_min):
        print("|", end = "")
        flag1 = False
      elif not flag1 and not flag:
        break
      else:
        print(" ", end = "")
    print(" ") 

  else:
    z = zn
    res_1 = z ** 4 - 3 * z * 3 + 8 * z**2 - 5

    print(f"{z:^7}", end = "")
       
    flag = flag1 = True
    for i in range(80):
      if flag and i * (y_max - y_min) / 78 >= res_1 - y_min:
        print("*", end = "")
        flag = False
        if flag1 and i * (y_max - y_min) / 78 >= abs(y_min):
          flag1 = False
      elif flag1 and i * (y_max - y_min) / 78 >= abs(y_min):
        print("|", end = "")
        flag1 = False
      elif not flag1 and not flag:
        break
      else:
        print(" ", end = "")
    print(" ")

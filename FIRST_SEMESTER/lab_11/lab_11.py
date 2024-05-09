# Факирзаи Амджад 
# ИУ7И-16Б
# Lab-11 (sorting)
# Variant -> simple selection method(Метод простого выбора)
from time import *
from random import *

def simple_sel(n: list):
    start_t = time()
    num = 0
    for i in range(len(n) - 1):
        min_ind = i
        for j in range(i + 1, len(n)):
            if n[min_ind] > n[j]:
                min_ind = j
        if min_ind != i:
            (n[i], n[min_ind]) = (n[min_ind], n[i])
            num += 1
    end_t = time()
    return end_t - start_t, num

def sel_sort(n):
    for i in range(len(n)):
        min_num = i
        for j in range(i + 1, len(n)):
            if n[min_num] > n[j]:
                min_num = j
        (n[i], n[min_num]) = (n[min_num], n[i])
    return n

def sel_sort_rev(n):
    for i in range(len(n)):
        min_num = i
        for j in range(i + 1, len(n)):
            if n[min_num] < n[j]:
                min_num = j
        (n[i], n[min_num]) = (n[min_num], n[i])
    return n

arr = []
count = 1
while True:
    try:
        elem = input(f"Please enter the {count} element, Press Enter for exit: ")
        if elem == '':
            break
        arr.append(int(elem))
        count += 1
    except:
        print("Invalid input, try again!")
        continue
print(f"Original array = {arr}")
print(f"Sorted array = {sel_sort(arr)}")
print(f"Reversing the sorted array = {sel_sort_rev(arr)}")

'''dict = {}
while True:
    try:
        dict["sizes"] = list(map(int, input("Please enter the 3 sizes seperated by space: ").split()))
        if len(dict["sizes"]) == 3:
            break
    except:
        continue
'''

len_N1, len_N2, len_N3 = list(map(int, input("Please enter the length of the" 
                                    "arrays N1,N2,N3 seperated by space: ").split()))
rand_list1 = sample(range(10 ** 6), len_N1)
rand_list2 = sample(range(10 ** 6), len_N2)
rand_list3 = sample(range(10 ** 6), len_N3)

print('+' + '-' * 30 + '+' + '-' * 26 + '+' + '-' * 26 + '+' + '-' * 26 + '+')
print("|{:^30}|{:^26}|{:^26}|{:^26}|".format('', f' N1 = {len_N1}', f' N2 = {len_N2}', f' N3 = {len_N3}'))
print('+' + '-' * 30 + '+' + '-' * 11 + "+" + "-" * 14 + '+' + '-' * 11 + "+" + "-" * 14 +
      '+' + '-' * 11 + "+" + "-" * 14 + '+')
print("|{:^30}|{:^11}|{:^14}|{:^11}|{:^14}|{:^11}|{:^14}|".format('', 'время/s', "перестановки", 'время/s', "перестановки",
                                                               'время/s', "перестановки"))

t1, k1 = simple_sel(rand_list1) 
rand_list1_sort = sorted(rand_list1)
t4, k4  = simple_sel(rand_list1_sort)
rand_list1_reverse = sorted(rand_list1, reverse = True)
t7, k7 = simple_sel(rand_list1_reverse)

t2, k2 = simple_sel(rand_list2)
rand_list2_sort = sorted(rand_list2)
t5, k5, = simple_sel(rand_list2_sort)
rand_list2_reverse = sorted(rand_list2, reverse = True)
t8, k8, = simple_sel(rand_list2_reverse)

t3, k3 = simple_sel(rand_list3)
rand_list3_sort = sorted(rand_list3)
t6, k6 = simple_sel(rand_list3_sort)
rand_list3_reverse = sorted(rand_list3, reverse = True)
t9, k9 = simple_sel(rand_list3_reverse)

print('+' + '-' * 30 + '+' + '-' * 11 + "+" + "-" * 14 + '+' + '-' * 11 + "+" + "-" * 14
      + '+' + '-' * 11 + "+" + "-" * 14 + '+')
print(f"|{'Случайный список':^30}|{t1:^11.3g}|{k1:^14g}|{t2:^11.3g}|{k2:^14g}|{t3:^11.3g}|{k3:^14g}|")

print('+' + '-' * 30 + '+' + '-' * 11 + "+" + "-" * 14 + '+' + '-' * 11 + "+" +
      "-" * 14 + '+' + '-' * 11 + "+" + "-" * 14 + '+')
print(f"|{'Упорядоченный список':^30}|{t4:^11.3g}|{k4:^14g}|{t5:^11.3g}|{k5:^14g}|{t6:^11.3g}|{k6:^14g}|")

print('+' + '-' * 30 + '+' + '-' * 11 + "+" + "-" * 14 + '+' + '-' * 11 + "+" + "-"
      * 14 + '+' + '-' * 11 + "+" + "-" * 14 + '+')
print(f"|{'в обратном порядке':^30}|{t7:^11.3g}|{k7:^14g}|{t8:^11.3g}|{k8:^14g}|{t9:^11.3g}|{k9:^14g}|")
print('+' + '-' * 30 + '+' + '-' * 11 + "+" + "-" * 14 + '+' + '-' * 11 + "+" +
      "-" * 14 + '+' + '-' * 11 + "+" + "-" * 14 + '+')
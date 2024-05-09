'''import sys
R, C = map(int, input("Please enter the rows and columns of the matrix: ").split())
if R == C:
    print("Given matrix is not a rectangular matrix")
    exit()
else:
    M = []
    for i in range(R):
        a = []
        for j in range(C):
            a.append(int(input()))
        M.append(a)
for i in range(R):
    for j in range(C):
        print(f"{M[i][j]:^4.3g}", end = " ")
    print()
ind, max_row =0, 0
sum1 = 0
for i in range(len(M[0])):
    sum1 += M[i][0]
for i, lst in enumerate(M):
    count = 0
    sum = 0
    for num in lst:
        sum += num
    if sum > sum1:
        max_row = sum
        ind = i
print(M[ind])
'''

list1 = list(map(int, input("Please enter the elements: ").split()))
n = len(list1)
from time import *
time_e = time()
print(time_e)
for i in range(n):
    min_num = i

    for j in range(i + 1, n):
        if list1[j] < list1[min_num]:
            min_num = j
    (list1[i], list1[min_num]) = (list1[min_num], list1[i])

time_d = time()
cur_time = time_d - time_e
print(cur_time)
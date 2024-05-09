option = int(input("Please enter a number between 1 and 8: "))

'''Arrays D and F. are given to form the matrix A by the formula ajk = sin(dj+fk).
Determine the arithmetic mean of the positive numbers of each row of the matrix and 
the number of elements less than the arithmetic mean. Write the results to the AV and 
L arrays, respectively . Print the matrix A as a matrix and the columns AV and L. side by side.
'''
if option == 1:
from math import sin
n = int(input("Please enter the lenght of the array D: "))
D = []
for i in range(n):
    D.append(int(input(f"Please enter the {i + 1} element of the array D: ")))
m = int(input("Please enter the length of the array F: "))
F = []
for i in range(m):
    F.append(int(input(f"Please enter the {i + 1} element of the array F: ")))

Matrix = []
for i in range(n):
    Matrix.append([])
    for j in range(m):
        Matrix[i].append(sin(D[i] + F[j]))
AV = [0] * n
for i in range(n):
    sum = 0
    count = 0
    for j in range(m):
        if Matrix[i][j] > 0:
            sum += Matrix[i][j]
            count += 1
    if count == 0:
        AV[j] = 0
    else:
        AV[i] = round(sum / count, 5)
        
L = [0] * n
for i in range(n):
    count = 0
    for j in range(m):
        if AV[i] > Matrix[i][j]:
            count += 1
    L[i] = count
for i in range(n):
    for j in range(m):
        print(f"{Matrix[i][j]:10.5g}", end = '')
    print(f"{AV[i]:^15.6g}", end = "")
    print(f"{L[i]:^10.4g}")
# 2 -> Rotate the square integer matrix 90 degrees clockwise then 90 degrees counterclockwise. Output the initial,
# intermediate and final matrices. Do not enter additional matrices and arrays.Do not apply transposition.
elif option == 2:
    n = int(input("Please enter the length of the matrix: "))

    matrix = []
    for i in range(n):
        matrix.append([])
        for j in range(n):
            matrix[i].append(int(input()))
    for i in range(n):
        for j in range(n):
            print(" ", matrix[i][j], end = " ")
        print()
    print("Matrix after rotating 90 degrees in the clockwise direction")
    for i in range(n // 2):
        for j in range(i, n - i - 1):
            temp = matrix[i][j]
            matrix[i][j] = matrix[n - 1 - j][i]
            matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j]
            matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i]
            matrix [j][n - 1 - i] = temp
        for i in range(n):
            print(matrix[i])

    print("Matrix after rotating 90 degrees in the counter clockwise direction")
    for i in range(n // 2):
        for j in range(i, n - i - 1):
            temp = matrix[i][j]
            matrix[i][j] = matrix[j][n - 1 - i]
            matrix[j][n - 1 - i] = matrix[n - 1 - i][n - 1 - j]
            matrix[n - 1 - i][n - 1 - j] = matrix[n - 1 - j][i]
            matrix[n - 1 - j][i] = temp
    for i in range(n):
        print(matrix[i])
# 3 -> Count in each row of the matrix D the number of elements exceeding the sum of the elements of the corresponding rows 
#   of the matrix Z. Place these quantities in the array G, multiply the matrix D by the maximum element of the array G.
#    Print the Z matrix, the D matrix before and after the transformation, and the G array.
elif option == 3:
    a, b = map(int, input("Please enter the size of the two arrays: ").split())

    D = [[int(input(f"Please enter the element {i + 1} row and {j + 1} column: ")) for j in range(b)] for i in range(a)]
    Z = [[int(input(f"Please enter the element {i + 1} row and {j + 1} column: ")) for j in range(b)] for i in range(a)]
    print("Z:")
    for i in range(a):
        for j in range(b):
            print(" ", Z[i][j], end = " ")
        print()
    print("===")
    print("D:")
    for i in range(a):
        for j in range(b):
            print(" ", D[i][j], end = " ")
        print()
    G = []
    for i in range(a):
        sum = 0
        count = 0
        for j in range(b):
            sum += Z[i][j]
        for k in range(b):
            if D[i][k] > sum:
                count += 1
        G.append(count)

    max_val = max(G)
    for i in range(a):
        for j in range(b):
            D[i][j] *= max_val
    print("After multiplication")
    for i in range(a):
        for j in range(b):
            print(' ', D[i][j], end = " ")
        print()
    print("G:")
    print(G)

# 4 -> The matrix D and the array I containing the row numbers for which it is necessary to determine the maximum element are given. 
#   The values of the maximum elements are stored in the array R. Determine the arithmetic mean of the calculated maximum values.
#    Print the matrix D, arrays I and R, the arithmetic mean.
elif option == 4:
    m, n = map(int, input("Please enter the number of rows and columns of the Matrix D: ").split())
    D = [[int(input(f"Please enter the element of the {i + 1} row and {j + 1} column: "))for j in range(n)] for i in range(m)]

    #I = list(map(int, input("Please enter: the length of array: ").split()))
    I = []
    R = []
    i = 1
    while i != 0:
        i = int(input("Please enter the row number starting from 1, and will end with 0: "))
        if i > 0:
            I.append(i)
        else:
            continue
    for i in I:
        if i <= len(D):
            R.append(max(D[i - 1]))
    sum = 0
    for i in R:
        sum += i
    average = 0
    try:
        average = round(sum / len(R), 5)
    except ZeroDivisionError:
        print("given inputs are not matching with the row numbers")
        exit()
    print("D: ")
    for i in range(m):
        for j in range(n):
            print(" ", D[i][j], end = " ")
        print()
    print(f"Number of rows = {I} and Maximum values in the given rows = {R}")
    print(f"The arithmetic mean of the calculated maximum values are {average}")
# 5 -> A matrix of symbols is given. Replace all English vowels with dots in it. 
# Print the matrix before and after the conversion.
elif option == 5:
    R, C = map(int, input("Please enter the number of rows and columns: ").split())
    matrix = []
    for i in range(R):
        a = []
        for j in range(C):
            a.append(str(input(f"Please enter the element of the {i + 1} row and {j + 1} column: ")))
        matrix.append(a)
    print("Printing the matrix")
    for i in range(R):
        for j in range(C):
            print(" ", matrix[i][j], end = " ")
        print()

    for i in range(R):
        for j in range(C):
            if matrix[i][j] in 'aeiouAEIOU':
                matrix[i][j] = '.'
    print("Matrix after Replacing the vowels with .")
    for i in range(R):
        for j in range(C):
            print(" ", matrix[i][j], end = " ")
        print()
# 6 ->Form a matrix C by line-by-line multiplication of matrices A and V of the same dimension (elements in the i-th
#    row of matrix A are multiplied by the corresponding elements in the i-th row of matrix B), hen add all the 
#    elements in the columns of matrix C and write them into an array V. Print matrices A, B, C and array V.
elif option == 6:

    m, n= map(int, input("Please enter the number of rows and columns: ").split())
    A ,B, C, V = [], [], [], []
    for i in range(m):
        a = []
        for j in range(n):
            a.append(int(input(f"Please enter the element of {i + 1} row and {j + 1} column: ")))
        A.append(a)
    for i in range(m):
        b = []
        for j in range(n):
            b.append(int(input(f"Please enter the element of {i + 1} row and {j + 1} column: ")))
        B.append(b)

    print("A:")
    for i in range(m):
        for j in range(n):
            print(" ", A[i][j], end = " ")
        print()

    print("B:")
    for i in range(m):
        for j in range(n):
            print(" ", B[i][j], end = " ")
        print()
    print()

    for i in range(m):
        c = []
        for j in range(n):
            c.append(A[i][j] * B[i][j])
        C.append(c)

    print("C")
    for i in range(m):
        for j in range(n):
            print(" ", C[i][j], end = " ")
        print()
    for j in range(n):
        sum = 0
        for i in range(m):
            sum += C[i][j]
        V.append(sum)
    print("V:")
    print(V)


# 7 -> Enter a three-dimensional array (an array of matrices of size X *Y*Z), output from it the i-th slice 
#   (a matrix is a fragment of a three-dimensional array) by the second index (index numbering begins with 1).
elif option == 7:
    X = Y = Z = -1
    matrix = []
    while X <= 1:
        X = int(input("X = "))
    while Y <= 1:
        Y = int(input("Y = "))
    while Z <= 1:
        Z = int(input("Z = "))

    for i in range(Z):
        matrix.append([])
        for j in range(Y):
            matrix[i].append([])
            for k in range(X):
                matrix[i][j].append(int(input(f"Please enter the {k + 1} element of the {j + 1} row and {i + 1} column: ")))

    Slice = -1
    while Slice <= 0 or Slice > len(matrix):
        Slice = int(input(f"Please enter the number of slice (0 < I <= {len(matrix)}: "))
    for i in range(len(matrix)):
        print(matrix[i][Slice - 1])
    print(matrix)
else:
    print("invalid input")

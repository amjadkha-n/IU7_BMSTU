# Факирзаи Амджад
# ИУ7И-16Б
# Лаб № 8 (Матрицы - часть 1)

'''
1 -> Find a row that has the largest number of consecutive identical elements   # variant
2 -> Rearrange the rows with tha largest and smallest number of negative elements
3 -> Find a column that has the smallest number of negative elements            # variant
4 -> Rearrange the columns with the maximum and minimum sum of elements
5 -> Find the maximum value in the square above the main diagonal and the 
    minimum is under the side diagonal
6 -> Perform the transposition of the square matrix.

Note:
    Do not create new matrices in 2, 6, 8 points
'''
option = int(input("Please enter a number between 1 and 6: "))
if option == 1:
    R = int(input("Please enter the amount of the rows: "))
    C = int(input("Please enter the amount of the columns: "))

    matrix = []

    print("Please enter the elements row wise")

    for i in range(R):
        a = []
        for j in range(C):
            a.append(int(input()))
        matrix.append(a)

    print("Printing the matrix")

    #for i in range(R):
    #    for j in range(C):
    #        print(matrix[i][j], end = " ")
    #    print()
    ind, max_elem = 0, 0
    print(matrix)
    for i , row in enumerate(matrix):
        count = 0
        for num in range(0, len(row) - 1, 1):
            if row[num] == row[num + 1]:
                count += 1
        if count > max_elem:
            max_elem = count
            ind = i
    print(matrix[ind])

elif option == 2:

    R = int(input("Please enter the number of rows: "))
    C = int(input("Please enter the number of columns: "))

    matrix = []
    print("Please enter the matrix row wise")
    #print()
    for i in range(R):
        a = []
        for j in range(C):
            a.append(int(input()))
        matrix.append(a)
    print("Printing the matrix")
    for i in range(R):
        for j in range(C):
            print(matrix[i][j], end = " ")
        print()
    if len(matrix) == 0:
        print("List is empty")
    else:
        min_row, max_row, row_1, row_2 = len(matrix[0]), 0, 0, 0
        for i, row in enumerate(matrix):
            count = 0
            for elem in row:
                if elem < 0:
                    count += 1
            if count > max_row:
                max_row = count
                row_1 = i
            if count < min_row:
                min_row = count
                row_2 = i
        matrix[row_1], matrix[row_2] = matrix[row_2], matrix[row_1]
    print(matrix)

elif option == 3:
    
    import sys, random

    R = int(input("Please enter the number of rows: "))
    C = int(input("Please enter the number of columns; "))

    matrix = []
    print("Please enter the numbers row wise")


    for i in range(R):
        a = []
        for j in range(C):
            a.append(int(input()))
        matrix.append(a)
    print("Printing the matrix")
    for i in range(R):
        for j in range(C):
            print(" ",matrix[i][j], end = " ")
        print()
    if len(matrix) == 0:
        print("LIst is empty")
    else:
        col = -1
        max_count = sys.maxsize
        for i in range(len(matrix[0])):
            count = 0
            for j in range(len(matrix)):
                if matrix[j][i] < 0:
                    count += 1
        
            if count != 0 and count < max_count:
                max_count = count
                col = i
        
        if col == -1 or max_count == sys.maxsize:
            print("no negative numbers found")
        else:
            print(f"The smallest number of negative number is in {col + 1} column of the matrix, which has {max_count} neg numbers")

elif option == 4:
    R = int(input("Please enter the number of rows: "))
    C = int(input("Please enter the amount of columns: "))
    matrix = []
    print("Please enter the elements row wise")
    for i in range(R):
        a = []
        for j in range(C):
            a.append(int(input()))
        matrix.append(a)
    print("Printing the matrix")
    for i in range(R):
        for j in range(C):
            print(" ",matrix[i][j], end = " ")
        print()
    if len(matrix) == 0:
        print("List is empty")
    else:
        min_col, max_col, sum = 0, 0, 0
        for i in range(len(matrix)):
            sum += matrix[i][0]
        max_s = min_s = sum
        for i in range(len(matrix[0])):
            sum = 0
            for j in range(len(matrix)):
                sum += matrix[j][i]
            if sum > max_s:
                max_s = sum
                max_col = i
            if sum < min_s:
                min_s = sum
                min_col = i
        for i in range(len(matrix)):
            matrix[i][min_col], matrix[i][max_col] = matrix[i][max_col], matrix[i][min_col]
    for i in range(R):
        for j in range(C):
            print(matrix[i][j], end = " ")
        print()

elif option == 5:

    import  sys

    R = int(input("Please enter the number of rows: "))
    C = int(input("Please enter the number of columns: "))
    matrix = []
    print("Please enter the values row wise")
    for i in range(R):
        a = []
        for j in range(C):
            a.append(int(input()))
        matrix.append(a)
    print("Printing the matrix")
    if R != C:
        print("Given matrix is not a square matrix")
        exit()
    else:
        for i in range(R):
            for j in range(C):
                print(" ",matrix[i][j], end = " ")
            print()
        value = 0
        min_val = sys.maxsize
        # or
        #min_val = 9223372036854775807
        max_val = -sys.maxsize - 1
        # or
        # max_val = -9223372036854775808
        for i in range(len(matrix)):
            for j in range(len(matrix)):
                if i < j:
                    value = matrix[i][j]
                    if value > max_val:
                        max_val = value
                    if value < min_val:
                        min_val = value

        print(f"max value = {max_val}")

        value = 0
        min_val = sys.maxsize
        # or
        #min_val = 9223372036854775807
        max_val = -sys.maxsize - 1
        # or
        # max_val = -9223372036854775808
        for i in range(len(matrix)):
            for j in range(len(matrix)):
               ''' if i > j:
                    value1 = matrix[i][j]
                    if max_val <  value1:  
                        max_val = value1'''
                if i + j >= len(matrix):
                    if min_val >  matrix[i][j]:  
                        min_val = matrix[i][j]

        print(f"min value = {min_val}")

elif option == 6:
    n = int(input("Please enter length of the matrix: "))
    matrix = []

    print("Please enter the numbers row wise")
    for i in range(n):
        matrix.append([])
        for j in range(n):
            matrix[i].append(int(input()))
    print("Printing the matrix")
    for i in range(n):
        for j in range(n):
            print(" ", matrix[i][j], end = " ")
        print()
    for i in range(len(matrix)):
        for j in range(i):
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
    print("Printing the matrix after transposition")
    for i in range(n):
        for j in range(n):
            print("  ", matrix[i][j], end = " ")
        print()
# or 
	n = int(input("Please enter the size of the matrix: "))
	M = [[int(input(f"Please enter the element of the {i+1} row and {j+1} column: "))for j in range(n)]for i in range(n)]
	for row in M:
	    print(*row, sep = " ")

	for i in range(n):
	    for j in range(n):
		if i == j:
		    break
		else:
		    M[i][j], M[j][i] = M[j][i], M[i][j]
	print("\n")
	for row in M:
	    print(*row, sep = " ")
else:
    print("Invalid input")

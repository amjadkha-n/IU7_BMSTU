'''R, C = map(int, input("Please enter the amount of rows and columns: ").split())
if R == C:
    print("Not a rectangular matrix")
    exit()
matrix = []
for i in range(R):
    a = []
    for j in range(C):
        a.append(int(input()))
    matrix.append(a)
for i in range(R):
    for j in range(C):
        print(" ", matrix[i][j], end = " ")
    print()
print()
for i in range(len(matrix) // 2):
    for j in range(len(matrix[0])):
        matrix[i][j], matrix[len(matrix) - 1 - i][j] = matrix[len(matrix) - 1 -i][j], matrix[i][j]
print(matrix)'''


R = int(input("Please enter the number of rows: "))
C = int(input("Please enter the number columns: "))
if R == 0:
    print("Given matrix is not a rectangular matrix")
    exit()
else:
    M = []
    for i in range(R):
        a = []
        for j in range(C):
            a.append(int(input(f"Please enter the element of the {i + 1} row and {j + 1} column: ")))
        M.append(a)
for i in range(R):
    for j in range(C):
        print(f"{M[i][j]:^6.4g}", end = " ")
    print()


for i in range(len(M) // 2):
    for j in range(len(M[0])):
        M[i][j], M[len(M) - 1 - i][j] = M[len(M) - 1 - i][j], M[i][j]
print("Printing the matrix after transformation")
for i in range(R):
    for j in range(C):
        print(f"{M[i][j]:^6.4g}", end = " ")
    print()
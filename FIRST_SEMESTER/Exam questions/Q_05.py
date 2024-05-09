def read_file(file_name):
    rows = file_name.read().strip().split('\n')
    print(rows)
    for i, row in enumerate(rows):
        rows[i] = list(map(int, row.split()))
    return rows

def rot_the_Matrix(matrix):
    n = len(matrix)
    for i in range(n//2):
        for j in range(i, n - i - 1):
            if j % 2 == 0:
                temp = matrix[i][j]
                matrix[i][j] = matrix[n - 1 - j][i]
                matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j]
                matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i]
                matrix [j][n - 1 - i] = temp
            else:
                temp = matrix[i][j]
                matrix[i][j] = matrix[j][n - 1 - i]
                matrix[j][n - 1 - i] = matrix[n - 1 - i][n - 1 - j]
                matrix[n - 1 - i][n - 1 - j] = matrix[n - 1 - j][i]
                matrix[n - 1 - j][i] = temp
    max_e = 0
    ind = 0
    for i in range(n):
        print(*matrix[i])
        for j in range(n):
            if max_e < matrix[i][j]:
                max_e = matrix[i][j]
                ind = j
    print(matrix)
    print(ind)
    new_line = ''
    for i in range(n):
        for j in range(n):
            if j != ind:
                new_line += str(matrix[i][j]) + ' '
        new_line += '\n'
    print(new_line)
    return new_line
def writeToFile(matrix, output_file):
    for row in matrix:
        for col in row:
            output_file.write(str(col))

input_file = open("in.txt", "r")
output_file = open("out.txt", "w")

matrix = read_file(input_file)
matrix = rot_the_Matrix(matrix)
writeToFile(matrix, output_file)


''' В файле in. txt записана прямоугольная символьная матрица (размер не превышает
9х9, символы в строках разделены пробелами). Символ > показывает направление 
вправо, < - влево, ^ - вверх, v - вниз. Требуется найти самую длинную непрерывную
"дорожку" из этих символов и добавить к магрице строку, содержащую числа - 
количества символов, входящих в эту дорожку, в соответствующих столбцах. Затем 
отсортировать столбцы матрицы по убыванию найденных количеств и записать результат в файл out. txt.
'''



def bubble_sort(arr):
    for i in range(len(arr)):
        for j in range(0, len(arr) -i - 1):
            if arr[j][0] > arr[j + 1][0]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
    arr = arr[::-1]
    return arr
def find_seq(line, symbol):
    max_count = 0
    count = 0
    for elem in line.split():
        if elem == symbol:
            count += 1
        if count > max_count:
            max_count = count
        if elem != symbol:
            count = 0
    if count > max_count:
        max_count = count
    return max_count
with open('in.txt', 'r') as input, open('out.txt', 'w') as output:
    count = len(input.readlines())
    if count > 9:
        print("Length of the matrix is more than 9")
        exit()
    else:   
        input.seek(0, 0) 
        New_list = []
        for i, line in enumerate(input):
            up_count = find_seq(line, '^')
            down_count = find_seq(line, 'v')
            left_count = find_seq(line, '<')
            right_count = find_seq(line, '>')

            max_count = max(up_count, down_count, left_count, right_count)
            if max_count == up_count:
                New_list.append((max_count, i))
            elif max_count == down_count:
                New_list.append((max_count, i))
            elif max_count == left_count:
                New_list.append((max_count, i))
            else:
                New_list.append((max_count, i))
        New_list = bubble_sort(arr = New_list)
        print(New_list)
        for char in New_list:
            input.seek(0, 0)
            for ind, lst in enumerate(input):
                if char[1] == ind:
                    output.write(lst.replace('\n', '') + '\n')
                    
                    break
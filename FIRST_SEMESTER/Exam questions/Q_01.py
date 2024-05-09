'''В файле in.txt записаны строки, длина каждой не превышает 100 символов
 Столбцом символов в рамках этой задачи считать последовательность символов, 
 расположенных на одной и той же позиции во всех строках файла. Требуется 
 переписать в файл out.txt содержимое исходного файла так, чтобы туда не 
 попали столбцы из символов #, если они есть. Также к каждой строке через 
 пробел пужно добавить число чисел (и целых, и вещественных), которые в ней присутетвутот:
Считывать файл в память целиком нельзя.'''
with open('in.txt', 'r') as input, open('out.txt', 'w') as output:
    for length in input:
        if len(length) > 100:
            print('One of the line of text is more than 100 symbols')
            exit()
    input.seek(0, 0)
    list_of_ind = []
    for i, line in enumerate(input):
        ind = 0
        for char in line:
            if char == "#":
                list_of_ind.append(ind)
                ind += 1
            else:
                ind += 1
    list_of_ind.sort()
    i = 0
    New_list = []
    while i < len(list_of_ind) - 1:
        if list_of_ind[i] == list_of_ind[i + 1]:
            New_list.append(list_of_ind[i])
            New_list.append(list_of_ind[i + 1])
            i += 1
        else:
            i += 1
    input.seek(0, 0)
    for line in input:
        New_line = ''
        for i in range(len(line)):
            if i not in New_list:
                New_line += line[i] 
            else:
                if line[i] != '#':
                    New_line += line[i ]
        output.write(New_line.replace('\n', '') + '\n')
''' Даны два файла: in1 .txt и in2.txt, в каждом по N строк. В первом файле записаны номера
строк второго файла от 1 до N (не по порядку), номера не повторяются. В каждой строке 
второго файла записаны 2 натуральных числа через пробел. Требуется вывести в файл out.txt 
суммы чисел из файла in2. txt, каждую с новой строки, по порядку в соответствии с номерами, 
указанными в файле in1.txt. Выводить только те суммы, которые являются квадратами целых чисел. 
Файлы в память целиком не считывать.'''


from math import *
with open('in1.txt', 'r') as input1, open('in2.txt', 'r') as input2, open('out.txt', 'w') as output:
    count1 = count2 = 0
    for i in input1:
        count1 += 1
    for j in input2:
        count2 += 1
    if count1 != count2:
        print("Both the input files don't have the same length")
        exit()
    else:
        input2.seek(0, 0)
        list_of_sums = []
        for line in input2:
            sum = 0
            for num in line.split():
                if ' ' in num:
                    continue
                else:
                    sum += int(num)
            list_of_sums.append(sum)
        new_list = []
        for sums in list_of_sums:
            sr = sqrt(sums)
            if sr * sr == sums:
                new_list.append(sums)
            else:
                continue
        for sums in new_list:
            output.write(str(sums) + '\n')
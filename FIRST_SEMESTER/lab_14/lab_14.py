# Факирзаи Амджад 
# ИУ7И-16Б
# Лаб № 14 (База данных в бинарном файле)

import os
import struct

FORMAT = "10s10s1i"
SIZE = struct.calcsize(FORMAT)
top = "--------------------------------------------------------------\n"\
      "|      name       |       Surname       |       Rating       |"
bottom = "-------------------------------------------------------------"
n = 1

def check_input_num(x):  
        t = input()
        if x == 0:  
            if not t.replace('.', '1').replace('-', '1').isdigit():
                print("Invalid input")
            else:
                if float(t) % 1 == 0:  
                    return int(t)
                else:
                    return float(t)
        if x == 1:  
            if not t.replace('-', '1').isdigit():
                print("Invalid input")
            else:
                return int(t)
        if x == 2:  #
            if not t.isdigit():
                print("Invalid input")
            else:
                return int(t)


def print_menu():
    print()
    print("1.Select a file to work with")
    print("2.Initialize the database")
    print("3.Output the contents of the database")
    print("4.Add a record to the database")
    print("5.Delete an entry from the database(by number in the file)")
    print("6.Search by one field")
    print("7.Search by two fields")
    print("0.Close the program")
    print("Please chose a number: ", end='')


def choose_file():  # Выбор бинарного файла из текущей директории
    print("Select a file from the list:")
    c = 0
    filesList = []
    for files in os.scandir(os.getcwd()):
        if files.is_file() and files.name[-4:] == ".bin" and files.name.count(".") == 1:
            filesList.append(files.name)
            print(f"{c + 1}){filesList[-1]}")
            c += 1
    print("Enter a number: ", end='')
    q = check_input_num(2)
    if q > c or q == 0:
        print(f"{1}<= Number <={c}")
        return
    return filesList[q - 1]


def init_file():
    chosenFile_name = input("Enter the name of the file: ")
    chosenFile = chosenFile_name + ".bin"
    try:
        file = open(chosenFile, "wb")
    except:
        print("Error occured while opening the file")
        return
    print("Enter the number of records in database: ", end='')
    n = check_input_num(2)
    print("Enter the Name, Surname and Rating")
    for i in range(n):
        print(f"Row {i + 1}")
        name = input("Enter the Name: ")
        if len(name) > 10:
            print("Long name")
        if not name.isalpha():
            print("Enter only letters")
            file.close
            return
        Surname = input("Enter the Surname: ")
        if len(Surname) > 10:
            print("Long surname")
        if not Surname.isalpha():
            print("Enter only letters")
            file.close()
            return
        '''for j in range(n):
        Surname = input("Enter the Surname: ")
        if len(Surname) > 10:
            print("Long Surname")
        if not Surname.isalpha():
            print("Enter only letters")
            file.close()
            return'''
        '''print("Enter the Surname: ", end="")
        Surname = check_input_num(2)'''
        print("Enter the Rating: ", end="")
        Rating = check_input_num(1)
        packedS = struct.pack(FORMAT, name.encode(), Surname.encode(), Rating)
        file.write(packedS)
    file.close()


def print_base(chosenFile):
   
    try:
        file = open(chosenFile, "rb")
    except:
        print("Error occured while opening the file")
        return
    #print(chosenFile + ":")
    data = file.read(SIZE)
    for i in range(n):
        print(top)
    while data:
        print(bottom)
        unpData = struct.unpack(FORMAT, data)
        unpName = ''.join(c for c in unpData[0].decode() if c.isalpha())
        unpSurname = ''.join(d for d in unpData[1].decode() if d.isalpha())
        print(f"|{unpName:^17}|{unpSurname:^21}|{unpData[2]:^20}|")
        data = file.read(SIZE)
    print(bottom)
    file.close()


def add_elem(chosenFile):
    try:
        file = open(chosenFile, "rb")
        data = file.read(SIZE)
        q = 0
        fileList = []
        while data:
            q += 1
            fileList.append(data)
            data = file.read(SIZE)
        file.close()
    except:
        print("Error occured while opening the file")
        return
    try:
        file = open(chosenFile, "wb")
    except:
        print("Error occured while opening the file")
        return
    print("Enter the number of row: ", end='')
    loca = check_input_num(2)
    if q == 0:
        if loca != 0:
            print("File path")
            return
    if loca > q:
        print("There is no such line")
        return
    name = input("Enter the name: ")
    if len(name) > 10:
        print("Long name")
    if not name.isalpha():
        print("Only letters")
        file.close()
        return
    Surname = input("Enter the Surname: ")
    if len(Surname) > 10:
        print("Long surname")
    if not Surname.isalpha():
        print("Only letters")
        file.close()
        return
    #print("Enter the Surname: ", end="")
    #Surname = check_input_num(1)
    print("Enter the rating: ", end="")
    Rating = check_input_num(1)
    packedS = struct.pack(FORMAT, name.encode(), Surname.encode(), Rating)
    fileList.insert(loca, packedS)
    for line in fileList:
        file.write(line)
    file.close()
    print_base(chosenFile)


def del_elem(chosenFile):
    print_base(chosenFile)
    try:
        file = open(chosenFile, "rb+")
    except:
        print("Error occurred while opening the file") 
        return
    data = file.read(SIZE)
    q = 0
    fileList = []
    while data:
        q += 1
        fileList.append(data)
        data = file.read(SIZE)
    print("Enter the number of line: ", end='')
    indexDel = check_input_num(2)
    if q == 0:
        print("File path")
        return
    if indexDel > q:
        print("No such file")
        return
    for i in range(indexDel, len(fileList) - 1):
        fileList[i] = fileList[i + 1]
    file = open(chosenFile, "wb")
    for item in fileList:
        file.write(item)
    file.truncate(SIZE * (q - 1))
    file.flush()
    file.close()
    print_base(chosenFile)


def find_one(chosenFile):
    try:
        file = open(chosenFile, "r+b")
    except:
        print("unknow error occured while opening the file")
        return
    print("Enter by which field to search(1-Name, 2-Surname, 3-Rating): ", end='')
    num = check_input_num(2)
    if num != 1 and num != 2 and num != 3:
        print("Invalid input")
        file.close()
        return
    word = input("Enter what to find: ")
    data = file.read(SIZE)
    for i in range(n):
        print(top)
    while data:
        unpData = struct.unpack(FORMAT, data)
        unpName = ''.join(c for c in unpData[0].decode() if c.isalpha())
        unpSurname = ''.join(d for d in unpData[1].decode() if d.isalpha())
        if num != 1:
            if str(unpData[num - 1]) == word:
                print(bottom)
                print(f"|{unpName:^17}|{unpSurname:^21}|{unpData[2]:^20}|")
        if num != 1:
            if unpSurname == word:
                print(bottom)
                print(f"|{unpName:^17}|{unpSurname:^21}|{unpData[2]:^20}|")
        else:
            if unpName == word:
                print(bottom)
                print(f"|{unpName:^17}|{unpSurname:^21}|{unpData[2]:^20}|")
        data = file.read(SIZE)
    print(bottom)
    file.close()


def find_two(chosenFile):
    try:
        file = open(chosenFile, "r+b")
    except:
        print("Error occured while opening the file")
        return
    print("Enter by which field to search(1-Name, 2-Surname, 3-Rating): ", end='')
    num1 = check_input_num(2)
    word1 = input("Enter what to find in the first field: ")
    print("Enter the second pole(1-Name, 2-Surname, 3-Rating): ", end='')
    num2 = check_input_num(2)
    word2 = input("Enter what to find in the second field: ")
    if (num1 != 1 and num1 != 2 and num1 != 3 and num2 != 1 and num2 != 2 and num2 != 3) or num1 == num2:
        print("invalid input")
        file.close()
        return
    data = file.read(SIZE)
    for i in range(n):
        print(top)
    while data:
        unpData = struct.unpack(FORMAT, data)
        unpName = ''.join(c for c in unpData[0].decode() if c.isalpha())
        unpSurname = ''.join(d for d in unpData[1].decode() if d.isalpha())
        '''if num1 != 1 and num2 != 1:
            if unpSurname == word1 and str(unpData[num2 - 1]) == word2 or str(unpData[num1 - 1]) == word1 and unpSurname == word2:
                print(bottom)
                print(f"|{unpName:^17}|{unpSurname:^21}|{unpData[2]:^20}|")
        elif num1 == 1 and num2 != 1:
            if unpName == word1 and unpSurname == word2 or unpSurname == word1 and unpName == word2:
                print(bottom)
                print(f"|{unpName:^17}|{unpSurname:^21}|{unpData[2]:^20}|")
        elif num1 != 1 and num2 != 1:
            if str(unpData[num1 - 1]) == word1 and unpName == word2 or unpName == word1 and str(unpData[num2 - 1]) == word2:
                print(bottom)
                print(f"|{unpName:^17}|{unpSurname:^21}|{unpData[2]:^20}|")'''
        if num1 != 1 and num2 != 1 or num1 != 1 and num2 == 1:
            if unpSurname == word1 and str(unpData[num2 - 1]) == word2 or  unpSurname == word1 and unpName == word2:
                print(bottom)
                print(f"|{unpName:^17}|{unpSurname:^21}|{unpData[2]:^20}|")
        if num1 == 1 and num2 != 1:
            if unpName == word1 and unpSurname == word2 or unpName == word1 and str(unpData[num2 - 1])== word2:
                print(bottom)
                print(f"|{unpName:^17}|{unpSurname:^21}|{unpData[2]:^20}|")
        if num1 != 1 and num2 == 1 or num1 != 1 and num2 != 1:
            if str(unpData[num1 - 1]) == word1 and unpName == word2 or str(unpData[num1 - 1]) == word1 and unpSurname == word2:
                print(bottom)
                print(f"|{unpName:^17}|{unpSurname:^21}|{unpData[2]:^20}|")
        data = file.read(SIZE)
    print(bottom)
    file.close()


chosenFile = "height.bin"
num = -1
while num != 0:
    print_menu()
    num = check_input_num(2)
    if num == 1:
        chosenFile = choose_file()
    if num == 2:
        init_file()
    if num == 3:
        print_base(chosenFile)
    if num == 4:
        add_elem(chosenFile)
    if num == 5:
        del_elem(chosenFile)
    if num == 6:
        find_one(chosenFile)
    if num == 7:
        find_two(chosenFile)
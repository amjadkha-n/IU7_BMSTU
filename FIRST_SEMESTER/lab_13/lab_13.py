# у тао ИУ7-11Б
# Лабораторная работа № 13
import os


def fool_input_num(x):  # Функция защиты от дурака для чисел
    while 1:
        t = input()
        if x == 0:  # Проверка на правильность для дробных чисел
            if not t.replace('.', '1').replace('-', '1').isdigit():
                print("Неверный ввод")
            else:
                if float(t) % 1 == 0:  # Проверка на целое число
                    return int(t)
                else:
                    return float(t)
        if x == 1:  # Проверка на правильность для целых чисел
            if not t.replace('-', '1').isdigit():
                print("Неверный ввод")
            else:
                return int(t)
        if x == 2:  # Проверка на правильность для натуральных чисел
            if not t.isdigit():
                print("Неверный ввод")
            else:
                return int(t)


def menu():
    print("1.Выбрать файл для работы")
    print("2.Инициализировать базу данных")
    print("3.Вывести содержимое базы данных")
    print("4.Добавить базу данных")
    print("5.Поиск по одному полю")
    print("6.Поиск по двум полям")
    print("0.Выход")
    print("Введите пункт: ", end='')


def choose():
    print("Выберите файл из предложенных:")
    c = 0
    filesList = []
    for files in os.scandir(os.getcwd()):
        if os.path.isfile(files):
            if ".py" in files.name:
                continue
            filesList.append(files.name)
            print(f"{c}){filesList[-1]}")
        c += 1
    print(f"Введите номер: ", end='')
    q = fool_input_num(2)
    if q > c - 1 or q < 0:
        print(f'0 <=Надо <= {c - 1}')
    else:
        return filesList[q]


def init_base(chosenFile):
    file = open(chosenFile, "w")
    print("Введите количество записей в базе: ", end='')
    num = fool_input_num(2)
    print("Поочередно вводите имя, номер группы и рост")
    for i in range(num):
        print(f"Строка {i + 1}")
        name = input()
        if len(name) > 10:
            print("Имя должно быть меньше десяти символов")
            file.close()
            return
        if not name.isalpha():
            print("Только буквы")
            file.close()
            return
        group = input()
        if len(group) > 2:
            print("Группа быть меньше двух символов")
            file.close()
            return
        if not group.isdigit():
            print("Только цифры")
            file.close()
            return
        height = input()
        if len(height) > 3:
            print("Рост должен быть меньше трех символов")
            file.close()
            return
        if not height.isdigit():
            print("Только цифры")
            file.close()
            return
        file.write(name + " " * (10 - len(name)) + ";" + group + " " * (2 - len(group)) + ";"
                   + height + " " * (3 - len(height)) + ";" + "\n")
    file.close()


def print_base(chosenFile):
    try:
        print(chosenFile + ":")
        file = open(chosenFile, "r")
        for i in file:
            print(i, end='')
        file.close()
    except FileNotFoundError as a:
        print(a)


def init_new_base(chosenFile):
    file = open(chosenFile, "a")
    print("Введите количество записей в базе: ", end='')
    num = fool_input_num(2)
    print("Поочередно вводите имя, номер группы и рост")
    for i in range(num):
        print(f"Строка {i + 1}")
        name = input()
        if len(name) > 10:
            print("Имя должно быть меньше десяти символов")
            file.close()
            return
        if not name.isalpha():
            print("Только буквы")
            file.close()
            return
        group = input()
        if len(group) > 2:
            print("Группа быть меньше двух символов")
            file.close()
            return
        if not group.isdigit():
            print("Только цифры")
            file.close()
            return
        height = input()
        if len(height) > 3:
            print("Рост должен быть меньше трех символов")
            file.close()
            return
        if not height.isdigit():
            print("Только цифры")
            file.close()
            return
        file.write(name + " " * (10 - len(name)) + ";" + group + " " * (2 - len(group)) + ";"
                   + height + " " * (3 - len(height)) + ";" + "\n")
    file.close()


def add_base():
    newFile = input("Введите название файла: ")
    init_new_base(newFile)


def find_one(chosenFile):
    file = open(chosenFile, "r")
    print("Введите по какому полю искать(1-Имя, 2-Группа, 3-Рост): ", end='')
    num = fool_input_num(2)
    word = input("Введите, что нужно найти: ")
    if num != 1 and num != 2 and num != 3:
        print("Неверный ввод")
        file.close()
        return
    for i in file:
        str1 = i.split(";")
        if str1[num - 1].find(word) != -1:
            print(i, end='')
    file.close()


def find_two(chosenFile):
    file = open(chosenFile, "r")
    print("Введите по какому полю искать(1-Имя, 2-Группа, 3-Рост): ", end='')
    num1 = fool_input_num(2)
    word1 = input("Введите, что нужно найти в первом поле: ")
    print("Введите второе поле(1-Имя, 2-Группа, 3-Рост): ", end='')
    num2 = fool_input_num(2)
    word2 = input("Введите, что нужно найти во втором поле: ")
    if (num1 != 1 and num1 != 2 and num1 != 3 and num2 != 1 and num2 != 2 and num2 != 3) or num1 == num2:
        print("Неверный ввод")
        file.close()
        return
    for i in file:
        str1 = i.split(";")
        if str1[num1 - 1].find(word1) != -1 and str1[num2 - 1].find(word2) != -1:
            print(i, end='')
    file.close()


ch = -1
chosen_File = "height.txt"
while ch != 0:
    menu()
    ch = fool_input_num(2)
    if ch == 0:
        break
    if ch == 1:
        chosen_File = choose()
    if ch == 2:
        init_base(chosen_File)
    if ch == 3:
        print_base(chosen_File)
    if ch == 4:
        init_new_base(chosen_File)
    if ch == 5:
        find_one(chosen_File)
    if ch == 6:
        find_two(chosen_File)
    print()
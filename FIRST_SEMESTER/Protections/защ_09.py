'''# python program to remove the main diagonal of the matrix and decrease the size 
# of the row by one
n = int(input("Please enter the length of the matrix: "))

M = []
for i in range(n):
    a = []
    for j in range(n):
        a.append(int(input(f"Please enter the element of the {i + 1} row and {j + 1} column: ")))
    M.append(a)

for i in range(n):
    for j in range(n):
        print(f"{M[i][j]:^4.3g}", end = " ")
    print()
j = 0
New_M = []

for i in range(len(M)):
    for j in range(i, len(M) - 1):
        M[j][i] = M[j + 1][i]
M.pop(-1)
for i in range(len(M)):
    for j in range(len(M[i])):
        print(" ", M[i][j], end = " ")
    print()'''

"""
Справка: текстовый процессор, в отличие от текстового редактора, который
позволяет только набирать текст, - программа для форматирования и
оформления документов, включая выравнивание, разметку и т.д.
Написать программу для выполнения некоторых операций с текстом. Вводить текст не
требуется, он должен быть задан в исходном тексте программы в виде списка строк
(при выводе на экран каждый элемент этого списка должен начинаться с новой
строки). В качестве текста в программе следует указать фрагмент литературного
произведения из 5-7 предложений, который разбить на 7-10 строк.
Программа должна позволять с помощью меню выполнить следующие действия:
1. Выровнять текст по левому краю.
2. Выровнять текст по правому краю.
3. Выровнять текст по ширине.
4. Удаление всех вхождений заданного слова.
5. Замена одного слова другим во всём тексте.
6. Вычисление арифметических выражений над целыми числами внутри текста
(умножение и деление).
7. Самое короткое слово в предложении, на самом длинном предложении.
Текст следует разбить по строкам так, чтобы предложения не заканчивались в концах
строк (никакая строка, кроме последней, не должна оканчиваться точкой).

"""

# text = ["Александр Пушкин начал писать свои первые произведения уже в семь лет. В годы учебы в Лицее он",
#         "прославился, когда прочитал свое стихотворение Гавриилу Державину. Пушкин первым из",
#         "русских писателей начал зарабатывать литературным трудом. Он создавал не только лирические",
#         "стихи, но и сказки, историческую прозу и произведения в поддержку  революционеров,",
#         "за вольнодумство поэта даже отправляли в ссылки. Александр Пушкин родился в обедневшей",
#         "дворянской семье 12/2 июня 257*7 года. В раннем детстве он был молчаливым",
#         "и малоподвижным ребенком."]

text = ["Reviled for his   brutality yet    honored as one of   the founding fathers of Haiti",
        "Jean-Jacques      Dessalines was second in command under    Toussaint L’Overture during the Haitian Revolution. ",
        "and was the general      who emerged 10 / 2 after    L’Overture’s capture",
        "to lead 5 * 0 the   insurgents in         declaring Haitian       independence on January 1, 1804",
        "Like L’Overture.          Dessalines was born into slavery in the French colony of Saint Domingue",
        "Born to Congolese parents.   5 * 20 Dessalines was originally given the name Duclos",
        "after the    plantation’s owner. ",
        "He later    adopted the surname      Dessalines after        the free black land",
        "owner.   who purchased 1000 / 10   him and from     whom he escaped."]

# The longest string


def max_length(text):
    mx = 0
    for line in range(len(text)):
        if len(text[line]) > mx:
            mx = len(text[line])
    return mx

# Text preparation for different operations


def normal(text):
    for line in range(len(text)):
        text[line] = ' '.join(text[line].split())

# Align text to the right


def align_right(text):
    normal(text)
    mx = max_length(text)
    for i in range(len(text)):
        delta = mx - len(text[i])
        for j in range(delta):
            text[i] = " " + text[i]


# Align the text to width
window_width = max_length(text)


def align_width(text):
    normal(text)
    mx = max_length(text)
    for i in range(len(text)):
        spaces = 0
        for j in range(len(text[i])):
            if text[i][j] == ' ':
                spaces = spaces + 1
        delta = mx - len(text[i])
        if spaces != 0:
            modulo = delta % spaces
            delta = delta // spaces
            j = 0
            length = len(text[i])
            while j < length:
                if text[i][j] == ' ':
                    for k in range(delta):
                        text[i] = text[i][:j] + " " + text[i][j:]
                    if modulo > 0:
                        text[i] = text[i][:j] + " " + text[i][j:]
                        j = j + 1
                        length = length + 1
                        modulo = modulo - 1
                    j = j + delta
                    length = length + delta
                j = j + 1

# Left-align text


def align_left(text):
    normal(text)
    mx = max_length(text)
    for i in range(len(text)):
        delta = mx - len(text[i])
        for j in range(delta):
            text[i] = text[i] + " "

#
# def delete_word(text, word):
#     normal(text)
#     word = word.lower()
#     indices = []
#     for i in range(len(text)):
#         # check if the word has a comma or period
#         if text[i][-1] == "," or text[i][-1] == ".":
#             if text[i][:-1].lower() == word:
#                 indices.append(i)
#                 if i !=0:
#                     text[i-1] = text[i-1] + text[i][-1]
#         else:
#             if text[i].lower() == word:
#                 indices.append(i)
#     for i in indices[::-1]:
#         del text[i]
#     if len(indices) == 0:
#         print("The word does not exist in the text")

# Deletes all occurrences of a given word


def swap_word(text, old, new):
    old = " " + old + " "
    for i in range(len(text)):
        text[i] = " " + text[i] + " "
        text[i] = text[i].replace(old, " " + new + " ")
    old = old[1:-1]
    old = " " + old + '"'
    for i in range(len(text)):
        text[i] = text[i].replace(old, " " + new + '"')
    old = old[1:-1]
    old = '"' + old + " "
    for i in range(len(text)):
        text[i] = text[i].replace(old, '"' + new + " ")
    old = old[1:-1]
    old = " " + old + "."
    for i in range(len(text)):
        text[i] = text[i].replace(old, " " + new + ".")
    old = old[1:-1]
    old = " " + old + ","
    for i in range(len(text)):
        text[i] = text[i].replace(old, " " + new + ",")
    old = old[1:-1]
    old = " " + old + ":"
    for i in range(len(text)):
        text[i] = text[i].replace(old, " " + new + ":")
    old = old[1:-1]
    old = old.capitalize()
    new = new.capitalize()
    old = " " + old + "."
    for i in range(len(text)):
        text[i] = text[i].replace(old, " " + new + ".")
    old = old[1:-1]
    old = " " + old + ","
    for i in range(len(text)):
        text[i] = text[i].replace(old, " " + new + ",")
    old = old[1:-1]
    old = " " + old + ":"
    for i in range(len(text)):
        text[i] = text[i].replace(old, " " + new + ":")
    old = old[1:-1]
    old = " " + old + " "
    for i in range(len(text)):
        text[i] = text[i].replace(old, " " + new + " ")
    old = old[1:-1]
    old = " " + old + '"'
    for i in range(len(text)):
        text[i] = text[i].replace(old, " " + new + '"')
    old = old[1:-1]
    old = '"' + old + " "
    for i in range(len(text)):
        text[i] = text[i].replace(old, '"' + new + " ")
    normal(text)


# Calculate arithmetic haloes
def evaluate(text):
    for i in range(len(text)):
        j = 1
        while j < len(text[i]) - 1:
            if text[i][j] == "*" or text[i][j] == "/":
                number1 = ""
                number2 = ""
                # Number to the left of the sign
                start = j - 1
                if text[i][start] == " ":
                    start = start - 1
                while start >= 0 and text[i][start] in "1234567890":
                    number1 = text[i][start] + number1
                    start = start - 1
                if start >= 0 and text[i][start] == "-":
                    number1 = "-" + number1
                    start = start - 1
                start = start + 1

                # Number to the right of the sign
                end = j + 1
                if text[i][end] == " ":
                    end = end + 1
                if text[i][end] == "-":
                    end = end + 1
                    number2 = "-"
                while end < len(text[i]) and text[i][end] in "1234567890":
                    number2 = number2 + text[i][end]
                    end = end + 1

                # Calculation
                if number1 != "" and number2 != "-" and number2 != "" and number1 != "-":
                    number1 = int(number1)
                    number2 = int(number2)
                    if text[i][j] == "*":
                        answer = number1 * number2
                    if text[i][j] == "/":
                        answer = number1 // number2
                    answer = str(answer)
                    text[i] = text[i][:start] + answer + text[i][end:]
                    j -= (end - start) + 1
                    j += len(answer)
            j += 1


# The shortest word in the longest sentence
def find_shortest(x):
    '''    normal(text)
    max = 0
    for i in range(len(text)):
        if len(text[i]) > max:
            max = len(text[i])
    for i in range(len(text)):
        if len(text[i]) == max:
            words = text[i].split()
            min = len(words[0])
            for j in range(len(words)):
                if len(words[j]) < min:
                    min = len(words[j])
            for j in range(len(words)):
                if len(words[j]) == min:
                    print(words[j])
                    del words[j]
                    break
            text[i] = ""
            for j in range(len(words)):
                text[i] = text[i] + words[j] + " "
            break
    normal(text)
    '''
    sentence  = None
    max_sent = None
    for i in range(len(x)):
        for j in range(len(x[i])):
            if sentence is None and x[i][j] not in '.!?':
                sentence = [x[i][j], i, j, None, None]
            elif x[i][j] not in '.!?':
                if not x[i][j].isalpha():
                    sentence[0] += ' '
                else:
                    sentence[0] += x[i][j]
                sentence[3], sentence[4] = i, j
            elif sentence is not None:
                sentence[3], sentence[4] = i, j
                max_len = max(map(len, sentence[0].split()))
                if max_sent is None or max_len > max_sent[0]:
                    max_sent = (max_len, sentence[1], sentence[2], sentence[3], sentence[4])
                sentence = None
        if sentence is not None:
            sentence[0] += ' '
    if max_sent is None:
        print("Sentence not found")
    else:
        print("Sentence with the longest word")
        if max_sent[3] - max_sent[1] >= 1:
            print(x[max_sent[1]][max_sent[2]:], end = " ")
            x[max_sent[1]] = x[max_sent[1]][:max_sent[2]]
            for i in range(max_sent[1] + 1, max_sent[3]):
                print(x[i], end = " ")
                x[i] = ''
            print(x[max_sent[3]][:max_sent[4] + 1], end = " ")
            x[max_sent[3]] = x[max_sent[3]][max_sent[4] + 1:]
        else:
            print(x[max_sent[1]][max_sent[2]: max_sent[4] + 1])
            x[max_sent[1]] = x[max_sent[1]][:max_sent[2]] + x[max_sent[1]][max_sent[4]:]
        print('\n')
        x = list(filter(lambda q: q, x))

def print_text(text):
    for i in range(len(text)):
        print(text[i])


print_text(text)
print("-----------------")

# Taking user's choice
while True:
    print("1. Выровнять текст по левому краю")
    print("2. Выровнять текст по правому краю")
    print("3. Выровнять текст по ширине.")
    print("4. Удаление всех вхождений заданного слова")
    print("5. Замена одного слова другим во всём тексте.")
    print("6. Вычисление удпление и деление над целыми числами внутри текста")
    print("7. Самое короткое слово в предложении, на самом длинном предложении.")
    print("8. Exit")
    choice = int(input("Введите команду: "))
    print()
    match choice:
        case 1:
            align_left(text)
        case 2:
            align_right(text)
        case 3:
            align_width(text)
        case 4:
            word = input("Слово для удаление: ")
            swap_word(text, word, "")

        case 5:
            word1 = input("Слово, которое будет меняться: ")
            word2 = input("Введите слово, которое на которое заменить: ")
            swap_word(text, word1, word2)
        case 6:
            evaluate(text)
        case 7:
            find_shortest(text)

        case 8:
            break
    print()
    for i in range(len(text)):
        print(text[i])
    print()
    if choice == 8:
        break
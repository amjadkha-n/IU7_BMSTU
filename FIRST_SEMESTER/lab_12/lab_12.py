
# Факирзаи Амджад
# ИУ7И-16Б 
# Лаб № 13 (Текстовый процессор)

# 1. Выровнять текст по левому краю.
# 2. Выровнять текст по правому краю.
# 3. Выровнять текст по ширине.
# 4. Удаление всех вхождений заданного слова.
# 5. Замена одного слова другим во всём тексте.
# 6. Вычисление арифметических выражений над целыми числами внутри текста (сложение и вычитание)
# 7. Найти (вывести на экран) и затем удалить предложение с самым длинным словом.

print()
Text = [
       'The children   were hungry. They looked   out the window. Where     was their',
       '    mother?  2-22 +1 She     walked into      the house.     The children ran   over to here. "Mama, we',
       'are hungry",they   both said.     She said lunch was     coming.    She  walked into the',
       'kitchen. She opened     the can of chicken soup. She   poured the soup   into a pop. She',
       'added water. She put -7 + 9 + 5 -10 -10 the pot on the stove. She made two peanut butter and jelly',
       '  888     sandwiches. She     sliced an apple. The        soup was hot. She    poured into      two bowls. She',
       'put the sandwiches on two     plates. She put apple slices on each plate. She put the bowls',
       'and     8 - 9 + 1 plates on the table. "Thank          you, mummy!" they said. Then they started eating. The',
       'cat and dog watched them eat.']

def left_align(x):
    for i in range(len(x)):
        x[i] = ' '.join(x[i].split())
    return x

def right_align(x):
    x = left_align(x)
    max_len= max(map(len, x))
    for i in range(len(x)):
        x[i] = x[i].rjust(max_len)
    return x

def align_width(x): 
    x = left_align(x)
    max_len = max(map(len, x))
    for i in range(len(x)):
        count = x[i].count(' ')
        if count == 0:
            break
        len_cur_line = len(x[i])
        q = (max_len - len_cur_line) // count
        rem = (max_len - len_cur_line) % count
        line = list(x[i])
        for k in range(len(line)):
            if line[k] == ' ':
                line[k] += ' ' * q
                if rem != 0:
                    line[k] += ' '
                    rem -= 1
        x[i] = ''.join(line)
    return x

def del_word(x):
    word = None
    while word is None:
        word = input("Please enter a word,which needs to be be deleted: ").strip()
        if not word.replace('-', '').isalpha():
            word = None
            print("Invalid input")
    for i in range(len(x)):
        x[i] = ' ' + x[i] + ' '
        for j in ' ("':
            for k in ' .,;:)!?':
                if k != ' ':
                    x[i] = x[i].replace(j + word + k, j + k)
                else:
                    x[i] = x[i].replace(j + word + k, j)
        x[i] = x[i][1:-1]
    if align is not None:
        x = align(x)
    return x

def replace_word(x):
    word_1 = None
    while word_1 is None:
        word_1 = input("Please enter a word, which needs to be replaced: ").strip()
        if not word_1.replace('-', '').isalpha():
            word_1 = None
            print("Invalid input")
    word_2 = None
    while word_2 is None:
        word_2 = input("Please enter a word, which needs to be replaced with: ").strip()
        if not word_2.replace('-', '').isalpha():
            word_2 = None
            print("Invalid input")
    for i in range(len(x)):
        x[i] = ' ' + x[i] + ' '
        for j in ' ("':
            for k in ' .,;:)!?':
                x[i] = x[i].replace(j + word_1 + k, j + word_2 + k)
        x[i] = x[i][1:-1]
    if align is not None:
        x = align(x)
    return x

def calc(x):
       
    for i in range(len(x)):
        j = 1
        while j < len(x[i]) - 1:
            if x[i][j] == "+" or x[i][j] == "-":
                number1 = ""
                number2 = ""
                # Number to the left of the sign
                start = j - 1
                if x[i][start] == " ":
                    start = start - 1
                while start >= 0 and x[i][start] in "1234567890":
                    number1 = x[i][start] + number1
                    start = start - 1
                if start >= 0 and x[i][start] == "-":
                    number1 = "-" + number1
                    start = start - 1
                start = start + 1

                # Number to the right of the sign
                end = j + 1
                if x[i][end] == " ":
                    end = end + 1
                if x[i][end] == "-":
                    end = end + 1
                    number2 = "-"
                while end < len(x[i]) and x[i][end] in "1234567890":
                    number2 = number2 + x[i][end]
                    end = end + 1

                # Calculation
                if number1 != "" and number2 != "-" and number2 != "" and number1 != "-":
                    number1 = int(number1)
                    number2 = int(number2)
                    if x[i][j] == "+":
                        answer = number1 + number2
                    if x[i][j] == "-":
                        answer = number1 - number2
                    answer = str(answer)
                    x[i] = x[i][:start] + answer + x[i][end:]
                    j -= (end - start) + 1
                    j += len(answer)
            j += 1
    if align is not None:
        x = align(x)
    return x
'''
def calc(x):  
    for i in range(len(x)):
        inexpr = False  
        expressions = [] 
        space_count = 0  
        for j in range(len(x[i])):
            if x[i][j].isdigit() and not inexpr:  
                expressions.append([x[i][j], j, 1])
                space_count = 0
                inexpr = True
            elif x[i][j].isdigit() or x[i][j] in '-+' and inexpr: 
                expressions[-1][0] += x[i][j]
                expressions[-1][2] += 1
                expressions[-1][2] += space_count
                space_count = 0
            elif x[i][j] == ' ' and inexpr:
                space_count += 1
            else:
                if len(expressions) != 0:
                    for index in range(len(expressions[-1][0]) - 1, -1, -1):  
                        if expressions[-1][0][index] in '-+':
                            expressions[-1][2] -= 1
                        else:
                            break
                    expressions[-1][0] = expressions[-1][0].strip('-+')
                inexpr = False

        for expr in range(len(expressions) - 1, -1, -1): 
            expr0 = list(map(lambda q: q.split('-'), expressions[expr][0].split('+')))  
            value = 0
            for expr1 in expr0:  
                for index, elem in enumerate(expr1):
                    if index == 0:
                        value += int(elem)
                    else:
                        value -= int(elem)
            expressions[expr][0] = value
            x[i] = list(x[i])
            del x[i][expressions[expr][1]:expressions[expr][1] + expressions[expr][2] - 1]  
            x[i][expressions[expr][1]] = str(expressions[expr][0])
            x[i] = ''.join(x[i])  

    if align is not None:
        x = align(x)

    return x
'''
def del_sent(x):
    if align is not None:
        x = align(x)
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
    '''    max = 0
    for i in range(len(x)):
        if len(x[i]) > max:
            max = len(x[i])
    for i in range(len(x)):
        if len(x[i]) == max:
            words = x[i].split()
            print("checking ", words)
            max = len(words[0])
            for j in range(len(words)):
                if len(words[j]) > max:
                    max = len(words[j])
            for j in range(len(words)):
                if len(words[j]) == max:
                    print(words[j])
                    del words[j]
                    break
            x[i] = ""
            for j in range(len(words)):
                x[i] = x[i] + words[j] + " "
            break '''
    if align is not None:
        x = align(x)
    return x

for i in Text:
    print(i)
print('\n')

align = None
option = None
while True:
    option = None
    while option is None:
        try:
            option = int(input('1 => Align the text to the left (Выровнять текст по левому краю''\n'
                                '2 => Align the text to the right edge (Выровнять текст по правому краю''\n'
                                '3 => Align the text to the width (Выровнять текст по ширине''\n'
                                '4 =>  Deleting the occurence of a given word (Удаление всех вхождений заданного слова ''\n'
                                '5 => Replacing one word with another in entire text(Замена одного слова другим во всём тексте''\n'
                                '6 => Calculation of arithmetic expressions over integers inside the text(Addition and subtraction)''\n'
                                '     Вычисление арифметических выражений над целыми числами внутри текста(сложение вычитание)''\n'
                                '7 => Find(Display) and delete a word or sentence by option(Sentence with the longest word)''\n'
                                '     Найти (вывести на экран) и затем удалить слово или предложение по варианту(Предложение с самым длинным словом)''\n'
                                '0 => Exit (Выход)''\n'
                                'Please select one from the given options: '))
            if option not in (1, 2, 3, 4, 5, 6, 7, 0):
                option = None   
                raise ValueError
        except ValueError:
            print("Invalid option")
    if option == 1:
        Text = left_align(Text)
        align = left_align
    elif option == 2:
        Text = right_align(Text)
        align = right_align
    elif option == 3:
        Text = align_width(Text)
        align = align_width
    elif option == 4:
        Text = del_word(Text)
    elif option == 5:
        Text = replace_word(Text)
    elif option == 6:
        Text = calc(Text)
    elif option == 7:
        Text = del_sent(Text)
    if option == 0:
        break
    print()
    for i in Text:
        print(i)
    print()
    input("Please, press Enter to continue: ")
    print()
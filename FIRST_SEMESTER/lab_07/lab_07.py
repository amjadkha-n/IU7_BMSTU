# Факирзаи Амджад
# ИУ7И-16Б
# lab_07.py
import string
'''
1 => Delete all the even numbers from a list using only one cycle
2 => After each element of an interger, if it is a positive number
    add its doubled value, without using the nested loops
3 => Search for the element with the largest number of english
    consonant letters in the list of rows 
4 => Replacing all lowercase consonants of english letters with
    uppercase ones
'''

option = int(input("Please enter a number between 1 and 4: "))

if option == 1:
  
    list1 = list(map(int, input("Please enter the numbers: ").split()))

    i = 0
    j = 1
    count = 0
    while i < len(list1):
        if list1[i] % 2 == 0:
            if i + j < len(list1):
                if list1[i + j] % 2 == 0:
                    j += 1
                else:
                    list1[i], list1[i + j] = list1[i + j], list1[i]
                    i += 1
                    j = 1
            else:
                count = j
                break
        else:
            i += 1
    print("List after removing the even numbers is")
    for i in range(count):
        list1.pop()
    if len(list1) != 0:
        #for num in list1:
        print(list1, end = ' ')
        print('')
    else:
        print('\nList is empty')


elif option == 2:
    list_1 = [int(x) for x in input("Enter the elements of the list: ").split()]
    count = 0
    for i in list_1:
        if i > 0:
            count += 1
    list_1 = [0] * count + list_1
    i = 0
    while count < len(list_1):
        list_1[i] = list_1[count]
        i += 1
        count += 1
        if list_1[count - 1] > 0:
            list_1[i] = list_1[count - 1] * 2
            i += 1
    print(list_1)


elif option == 3:
    alphabets = string.ascii_letters

    n = int(input("Pelase enter the amount of lists: "))
    lists = []

    for i in range(n):
        lists.append(input("Please enter the string: "))
        ind, max_elem = 0, 0
    for i, lst in enumerate(lists):
        count = 0
        for elem in lst:
            if elem not in 'aeiouAEIOU' and elem in alphabets:
                count += 1
        if count > max_elem:
            max_elem = count
            ind = i
    if count > 0:
       print(lists[ind])
    else:
        print("No rows with consonants in the list")


elif option == 4:
    n = int(input("Please enter the amount lists: "))
    alphabets = string.ascii_letters
    lists = []
    new_list = []
    for i in range(n):
        lists.append(input("Please enter the elements of the list: "))
        for i, lst in enumerate(lists):
            for elem in lst:
                if elem not in 'aeiouAEIOU' and elem in alphabets:
                    elem = elem.upper()
                    new_list += elem  
                else:
                    new_list += elem
    print(new_list)
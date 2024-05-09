# 1 = Add an element to a given place in the list (by index)
#    using any python tools

print("Adding an element in the list by index")
list = list(map(int, input("Please enter the elements of the list: ").split()))
num = int(input("Please enter the number: "))
ind = int(input("Please enter the index number: "))
if ind >= len(list):
    print(f"Please enter the index smaller than {len(list)}")
else:
    list.insert(ind, num)
    print(list)

'''
2 = add an element to a given place in the list (by index)
    algorithmically
'''
print("Adding an element in the list by index algorithmically")
list = list(map(int, input("Please enter the elements of the list: ").split()))
list.append(None)
ind = int(input("Please enter the index number: "))
num = int(input("Please enter the number: "))
i = len(list) - 1
while i > ind - 1:
    list[i] = list[i - 1]
    i -= 1
list[ind] = num
print(list)


# 3 = Remove an element with a given index using any means of python

print("Removing an element from the list by index algorithmically")
list = list(map(int, input("Please enter the elements of the list: ").split()))
ind = int(input("Please enter the index number: "))
for i in range(ind , len(list) - 1):
    list[i] = list[i + 1]
list.pop()
print(list)

# 4 = Remove an element with the specified index algorithmically

print("Removing an element from the list by index")
list = list(map(int, input("Please enter the elements of the list: ").split()))
ind = int(input("Please enter the index number: "))
if ind >= len(list) - 1:
    print(f"Please enter the index less than {len(list - 1)}")
else:
    list.pop(ind)
    print(list)

# 5 = Find the value of kth extremum in the list

	print("Printing the kth extremum value in the list")
list1 = list(map(int, input("Please enter the elements of the list: ").split()))
list_1 = []
for i in range(1, len(list1) - 1):
    if list1[i] > list1[i + 1] and list1[i] > list1[i - 1] or (
        list1[i] < list1[i + 1] and list1[i] < list1[i - 1]):
        list_1.append(list1[i])
k = int(input(f"Please enter the value of k less than {len(list1) - 1}: "))
try:
    print(f"The value of the extremum in the list = {list_1[i - 1]}")
except IndexError:
    print("Not that much of extremums")
input("Press enter to continue")

# 6 = Find the longest continues sequence of odd numbers

n = int(input("Please enter the size of the list: "))
lists = []
for i in range(n):
    elem = int(input(f"Please enter the the {i + 1}th element: "))
    lists.append(elem)
max_seq = []

max_elem = 0
count = 0
i = 0
while i < len(lists):
    if lists[i] % 2 != 0:
        if count == 0:
            max_seq = []
        max_seq.append(lists[i])
        count += 1
        if count > max_elem:
            max_elem = count
            long_seq = max_seq
    else:
        count = 0
    i += 1
print(long_seq) 

# 7 = Minimum even and maximum odd
'''
print("Finding the mimimum even and maximum odd number in the list")
list = list(map(int, input("Please enter the elements of the list: ").split()))
for i in range(len(list)):
    for j in range(i + 1, len(list)):
        if list[i] > list[j]:
            list[i], list[j] = list[j], list[i]
for i in list:
    if i % 2 == 0:
        min = i
        print(f"Minimum even number in the list is {min}")
        break
max = list[0]
for i in range(len(list)):
    if list[i] > max:
        if list[i] % 2 != 0:
            max = list[i]
print(f"Maximum odd number in the list is {max}")
'''
# or

'''n = int(input("Please enter the size of the list: "))
lists = []
for i in range(n):
    elem = int(input(f"Please enter the the {i + 1}th element: "))
    lists.append(elem)
for i in range(len(lists) - 1):
    for j in range(i + 1, len(lists)):
        if lists[i] > lists[j]:
            lists[i], lists[j] = lists[j], lists[i]
print(lists)
for i in range(len(lists) - 1):
    if lists[i] % 2 == 0:
        min_even = lists[i]
        break
for i in range(len(lists) - 1, 1, -1):
    if lists[i] % 2 != 0:
        max_odd = lists[i]
        break
print(f"Min even = {min_even} and Max odd = {max_odd}")'''

# or

n = int(input("Please enter the size of the list: "))
lists = []
for i in range(n):
    elem = int(input(f"Please enter the the {i + 1}th element: "))
    lists.append(elem)
min_even = max_odd = -1
for i in range(len(lists)):
    if lists[i] % 2 == 0 and (min_even == -1 or lists[min_even] > lists[i]):
        min_even = i
    if lists[i] % 2 != 0 and (max_odd == -1 or lists[max_odd] < lists[i]):
        max_odd = i
print(f"Min even = {lists[min_even]} and Max odd = {lists[max_odd]}")

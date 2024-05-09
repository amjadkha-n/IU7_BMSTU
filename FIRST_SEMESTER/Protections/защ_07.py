import string
alphabets = string.ascii_letters
n = int(input("Please enter the amount of lists: "))
lists = []
for i in range(n):
    lists.append(input("Please enter the string: "))
    ind, max_elem = 0, 0
    for i, lst in enumerate(lists):
        count1 = count = 0
        for elem in lst:
            if elem not in 'aeiouAEIOU' and elem in alphabets:
                count += 1
            if elem in 'aeiouAEIOU' and elem in alphabets:
                count1 += 1
        if count > max_elem and (count1 % 2 == 1) > max_elem:
            max_elem = count
            ind = i
print(lists[ind])

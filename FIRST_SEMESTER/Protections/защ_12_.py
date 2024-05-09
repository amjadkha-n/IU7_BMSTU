# finding the longest sentence of the text

Text = [
       'The children   were hungry. They looked   out the window. Where     was their',
       '    mother?  2-22 +1 She     walked into      the house.     The children ran   over to here. "Mama, we',
       'are hungry",they   both said.     She said lunch was     coming.    She  walked into the',
       'kitchen. She opened     the can of chicken soup. She  my name is amjad khan and she lives in gilgit poured the soup   into a pop. She',
       'added water. She put -7 + 9 + 5 -10 -10 the pot on the stove. She made two peanut butter and jelly',
       '  888     sandwiches. She     sliced an apple. The        soup was hot. She    poured into      two bowls. She',
       'put the sandwiches on two     plates. She put apple slices on each plate. She put the bowls',
       'and     8 - 9 + 1 plates on the table. "Thank          you, mummy!" they said. Then they started eating. The',
       'cat and dog watched them eat. ']
for i in Text:
    print(i)
print()
cur_sent = []
max_count = 0
cur_max = []
count = 0

for line in Text:
    for word in line.split():
        if '.' not in word:
            cur_sent.append(word)
            count += 1
        else:
            cur_sent.append(word)
            
            if count > max_count:
                cur_max =  cur_sent
                max_count = count
            cur_sent = []
            count = 0
result = ' '.join(cur_max)
print(result)     
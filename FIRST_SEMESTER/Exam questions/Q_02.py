'''In the file in.txt the lines are written, each one does not exceed 100 
characters in length. The diagonal of the characters in this task is 
considered to be a sequence of characters located in all lines of the 
file so that the character in the next line is one position to the right 
of the character in the previous line. It needs to be rewritten to the 
out file. txt the contents of the source file so that the diagonals of the % characters, 
if any, do not get there. Also, to each line separated by a space, you need to add the 
number of palindrome words longer than one that are present in it. You cannot read the entire file into memory.

'''
with open("in.txt", "r") as f, open('out.txt', 'w') as output:
    for line in f:
        if len(line) > 100:
            print("One of the line's length is exceeding 100 characters")
            exit()
    f.seek(0, 0)
    k = 0
    palindrome_count = [sum(word == word[::-1] and len(word) > 1 for word in line.split())for line in f]
    f.seek(0, 0)
    for i, lines in enumerate(f):
        line = lines.split()
        nwr = ""
        for j in range(len(line)):
            if j < i:
                nwr += line[j] + " "
            elif j > i:
                nwr += line[j] + " "
            else:
                if line[j] != '%':
                    nwr += line[j] + " "
        k += 1
        output.write(nwr.replace('\n', ''))
        output.write(' ')
        output.write(str(palindrome_count[i]) + '\n')    
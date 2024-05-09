'''#Read in.txt file
in_file = open('in.txt', 'r')
in_data = in_file.readlines()
in_file.close()

#Process the file
track_count = [] #list to store the number of characters in each track
for line in in_data:
    track = [] #list to store each continuous track
    for char in line.split():
        if char == '>':
            track.append(char)
        elif char == '<':
            track.append(char)
        elif char == '^':
            track.append(char)
        elif char == 'v':
            track.append(char)
    track_count.append(len(track))

#Create output matrix
out_data = []
for line in in_data:
    out_data.append(line.strip())
out_data.append(' '.join(map(str, track_count)))

#Sort the columns of the matrix in descending order of the found quantities
sorted_data = []
for col in range(len(track_count)):
    max_track = max(track_count)
    max_index = track_count.index(max_track)
    sorted_data.append([line.split()[max_index] for line in out_data])
    track_count[max_index] = 0

#Write the result to the out.txt file
out_file = open('out.txt', 'w')
for line in sorted_data:
    out_file.write(' '.join(line) + '\n')
out_file.close()'''



#open source and destination files
in_file = open("in.txt", "r")
out_file = open("out.txt", "w")

#iterate through the source file
for line in in_file:
    #if the line contains an arithmetic expression
    if line.find("+") != -1 or line.find("-") != -1 or line.find("*") != -1 or line.find("/") != -1:
        #split the expression
        expression = line.split(" ")
        #evaluate the expression
        result = 0
        if expression[2] == "+":
            result = int(expression[1]) + int(expression[3])
        elif expression[2] == "-":
            result = int(expression[1]) - int(expression[3])
        elif expression[2] == "*":
            result = int(expression[1]) * int(expression[3])
        elif expression[2] == "/":
            result = int(int(expression[1]) / int(expression[3]))
        #write the line N times to the destination file
        for i in range(result):
            out_file.write(line.replace("\n", '') + '\n')
    else:
        out_file.write(line)

#close the files
in_file.close()
out_file.close()
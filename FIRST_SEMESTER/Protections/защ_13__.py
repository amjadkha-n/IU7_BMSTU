'''def sent_in_text(Text):
    start = 0
    res = []
    for ind, word in enumerate(Text):
        if word == '.':
            res.append((start, ind + 1))
            start = ind + 1
    return res
file = open("in(1).txt", 'r')
file_out = open("out(1).txt", 'w')

Text = file.read().replace("\n", "")

sen_index = sent_in_text(Text)
New_len = len(sen_index)
for i in range(New_len // 2):
    for j in range(len(sen_index[0])):
        sen_index[i][j], sen_index[New_len - 1 - i][j] = sen_index[New_len - 1 - i][j], sen_index[i][j]
        file_out.write(Text[sen_index[0] : sen_index[1]] + "\n")
file.close()
file_out.close()    '''

in_file = 'in(1).txt' 
out_file = 'out(1).txt' 
  
with open(in_file) as input, open(out_file, 'w') as output: 
    sentences = [] 
  
    for line in input: 
        # Splitting lines into sentences 
        line_sentences = line.split('.') 
  
        # Appending sentences to list 
        sentences += line_sentences[:-1] 
  
    # Reversing sentences 
    reversed_sentences = sentences[::-1] 
  
    # Writing to out_file 
    for s in reversed_sentences: 
        output.write(s.strip() + '.\n')
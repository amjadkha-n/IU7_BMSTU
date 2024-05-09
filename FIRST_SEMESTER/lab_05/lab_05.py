# Факирзаи Амджад
# ИУ7И-16Б
# fifth lab
# x - x / 2 + x / 4 + ... + (-x / 2) ** n + ...

eps = float(input("Please enter the accuracy: "))
step = float(input("Please enter the step: "))
iter = float(input("Please enter the quantity of the iterations: "))
if step < 0:
    print("Can't have negative step")
    exit()
print("-" * 32 + '\n|' + '№'.center(6) + '|' + 't'.center(11) + '|' + 's'.center(11) + '|'
    '\n' + '-' * 32)
n = 0
x = 1
i = 1
sum = 0

while i <= iter:
    term = (-x / 2) ** n
    n += 1
    if abs(term) < eps:
        break
    else:   
        sum += term
        if i <= iter and (i - 1) % step == 0:
            print(f"|{i:^6}|{term:^11.3g}|{sum:^11.3g}|")
        i += 1
           
    
print("-" * 32)
if i == iter + 1:
    print("Given accuracy could not be achieved for the specified iter")
else:
    print(f"Sum of the given infinite series is {sum:.3g}, calculated in {i - 1} iterations")


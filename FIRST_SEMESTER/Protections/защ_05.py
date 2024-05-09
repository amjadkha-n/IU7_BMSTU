
# (-1) ** n * (1 / 2 ** n)

eps = float(input("Please enter the accuracy: "))
step = float(input("Please enter the step: "))
iter = float(input("Please enter the quantity of iterations: "))

if step < 0:
    print("Step can't be negative")
    exit()

print("-" * 32 + '\n|' + '№'.center(6) + '|' + 't'.center(11) + '|' + 's'.center(11) + '|'
    '\n' + '-' * 32)

n = 0
sum = 0
i = 1

while i <= iter:
    term = (-1) ** n * (1 / 2 ** n)
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
    print("Given accuracy couldn't be achieved for the specied iteration")
else:
    print(f"Sum of the infinite sequence is {sum:.3g} calculated in {i - 1}")
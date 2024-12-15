from util import read

hands = list(map(lambda x: tuple(x.split(" ")), read().splitlines()))
winning = [('C','X'), ('A', 'Y'), ('B', 'Z')]
draw = [('A', 'X'), ('B', 'Y',), ('C', 'Z')]
values = {'X': 1, 'Y': 2, 'Z': 3}

total = 0
for hand in hands:
    value = values[hand[1]]
    if hand in winning:
        value += 6
    elif hand in draw:
        value += 3
    total += value
print(total)
    




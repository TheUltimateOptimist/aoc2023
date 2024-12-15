from util import read

hands = list(map(lambda x: tuple(x.split(" ")), read().splitlines()))
winning = {'A': 'C', 'B': 'A', 'C': 'B'} 
loosing = {value: key for key, value in winning.items()}
values = {'A': 1, 'B': 2, 'C': 3}

total = 0
for hand in hands:
    if hand[1] == 'X': total += values[winning[hand[0]]]
    if hand[1] == 'Y': total += 3 + values[hand[0]]
    if hand[1] == 'Z': total += 6 + values[loosing[hand[0]]]
print(total)
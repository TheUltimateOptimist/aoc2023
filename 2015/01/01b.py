from util import read

total = 0
for i, char in enumerate(read()):
    if char == '(': total += 1
    if char == ')': total -= 1
    if total == -1:
        print(i + 1)
        break
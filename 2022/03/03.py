from util import read

lines = read().splitlines()
total = 0
for line in lines:
    left = set(line[:len(line) // 2])
    right = set(line[len(line) // 2:])
    for char in left:
        if char in right and char.islower():
            total += ord(char) - 96
        elif char in right and char.isupper():
            total += ord(char) - 65 + 27
print(total)







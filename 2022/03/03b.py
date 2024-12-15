from util import read

lines = read().splitlines()
total = 0
for a in range(0, len(lines), 3):
    first, second, third = set(lines[a]), set(lines[a + 1]), set(lines[a + 2])
    badge = first.intersection(second, third).pop()
    if badge.islower():
        total += ord(badge) - 96
    elif badge.isupper():
        total += ord(badge) - 65 + 27
print(total)

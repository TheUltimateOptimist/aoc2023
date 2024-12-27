from util import read

count = 0
for line in read().splitlines():
    vowels = line.count('a') + line.count('e') + line.count('i') + line.count('o') + line.count('u')
    if vowels < 3: continue
    for i in range(len(line) - 1):
        if line[i] == line[i + 1]:
            break
    else: continue
    if 'ab' in line or 'cd' in line or 'pq' in line or 'xy' in line:
        continue
    count += 1
print(count)
    
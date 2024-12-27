from util import read

count = 0
for line in read().splitlines():
    first_fulfilled = False
    for a in range(len(line) - 1):
        at = line[a] + line[a + 1]
        for b in range(a + 2, len(line) - 1):
            if line[b] + line[b + 1] == at:
                first_fulfilled = True
                break 
    if not first_fulfilled: continue 
    for i in range(len(line) - 2):
        if line[i] == line[i + 2]:
            break
    else: continue
    count += 1
print(count)
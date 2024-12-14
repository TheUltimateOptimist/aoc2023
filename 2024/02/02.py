from util import read

data = read().splitlines()
safe_reports = 0
for level in data:
    level = list(map(lambda x: int(x), level.split(" ")))
    increasing = level[1] > level[0]
    if level[1] == level[0]:
        continue
    one_unsafe = False
    for i in range(1, len(level)):
        if not (increasing and level[i] > level[i - 1] and level[i] - level[i - 1] <= 3 or (not increasing) and level[i] < level[i - 1] and level[i - 1] - level[i] <= 3):
            break
        if i == len(level) - 1:
            safe_reports += 1
print(safe_reports)

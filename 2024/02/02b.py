from util import read

data = read().splitlines()

safe_reports = 0

def is_safe(level: list[int]) -> bool:
    increasing = level[1] > level[0]
    if level[1] == level[0]:
        return False
    for i in range(1, len(level)):
        if not (increasing and level[i] > level[i - 1] and level[i] - level[i - 1] <= 3 or (not increasing) and level[i] < level[i - 1] and level[i - 1] - level[i] <= 3):
            return False
    return True

for level in data:
    level = list(map(lambda x: int(x), level.split(" ")))
    if is_safe(level): safe_reports += 1
    else: 
        for i in range(len(level)):
            val = level[i]
            del level[i]
            if is_safe(level):
                safe_reports += 1
                break
            level.insert(i, val)
print(safe_reports)
from util import read, analyze_polygon

entries = read().split("\n")
for i in range(len(entries)):
    entries[i] = entries[i].split(" ")

directions: dict[int, tuple[int, int]] = {0: (0, 1), 2: (0, -1), 3: (-1, 0), 1: (1, 0)}

path: list[tuple[int, int]] = [(0, 0)]

outer = 0
current = (0, 0)
for entry in entries:
    direction = directions[int(entry[2][7])]
    count = int(entry[2][2:7], 16)
    outer += count
    current = (current[0] + count*direction[0], current[1] + count*direction[1])
    path.append(current)

print(f"result = {analyze_polygon(path).bothside}")
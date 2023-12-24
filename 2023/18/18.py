from util import read, analyze_polygon

entries = read().split("\n")
for i in range(len(entries)):
    entries[i] = entries[i].split(" ")

directions: dict[str, tuple[int, int]] = {"R": (0, 1), "L": (0, -1), "U": (-1, 0), "D": (1, 0)}

path: list[tuple[int, int]] = [(0, 0)]

outer = 0
current = (0, 0)
for entry in entries:
    direction = directions[entry[0]]
    count = int(entry[1])
    outer += count
    current = (current[0] + count*direction[0], current[1] + count*direction[1])
    path.append(current)

print(f"result = {analyze_polygon(path).bothside}")
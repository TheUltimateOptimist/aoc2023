from util import read

grid = read().split("\n")

ex_rows = set()
ex_cols = set()

# expand rows
for row in range(len(grid)):
    should_expand = True
    for col in range(len(grid[0])):
        if grid[row][col] != ".":
            should_expand = False
            break
    if should_expand:
        ex_rows.add(row)

# expand cols
for col in range(len(grid[0])):
    should_expand = True
    for row in range(len(grid)):
        if grid[row][col] != ".":
            should_expand = False
            break
    if should_expand:
        ex_cols.add(col)

# find galaxies
points: list[tuple[int, int]] = []
rowd = 0
for row in range(len(grid)):
    if row in ex_rows:
        rowd += 999_999
        continue
    cold = 0
    for col in range(len(grid[0])):
        if col in ex_cols:
            cold += 999_999
            continue
        if grid[row][col] == "#":
            points.append((row + rowd, col + cold))

# sum shortest paths
print(points)
result = 0
for i, galaxy in enumerate(points):
    for d in range(i + 1, len(points)):
        destination = points[d]
        result += abs(destination[0] - galaxy[0])
        result += abs(destination[1] - galaxy[1])
print(f"result = {result}")
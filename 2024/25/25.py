from util import read, Grid, pair, dirs

def create(grid: Grid[str], srow: int, dir: pair) -> tuple[int, ...]:
    srow = 0 if grid[pair(0, 0)] == '#' else 6
    dir = dirs.down if srow == 0 else dirs.up
    counts: list[int] = []
    for col in range(5):
        start = pair(srow, col)
        count = 0
        while grid[start + dir] == '#':
            start = start + dir 
            count += 1
        counts.append(count)
    return tuple(counts)
        
grids = list(map(lambda x: Grid.from_input(x), read().split("\n\n")))
locks: list[tuple[int, ...]] = []
keys: list[tuple[int, ...]] = []
for grid in grids:
    if grid[pair(0, 0)] == '#':
        locks.append(create(grid, 0, dirs.down))
    else: keys.append(create(grid, 6, dirs.up))

count = 0
for lock in locks:
    for key in keys:
        for i in range(5):
            if lock[i] + key[i] > 5:
                break
        else: count += 1
print(count)
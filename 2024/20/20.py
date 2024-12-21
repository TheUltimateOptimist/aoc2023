from util import read, dirs, Grid, pair

root_grid = Grid.from_input(read())
start = root_grid.find('S')
end = root_grid.find('E')
assert start is not None

grid = Grid([[-1 for i in range(root_grid.numcols)] for _ in range(root_grid.numrows)])
pos = start
count = 0
grid[pos] = 0
while pos != end:
    count += 1
    for dir in dirs.straight:
        if (pos + dir) not in grid: continue
        if root_grid[pos + dir] == '#': continue
        if grid[pos + dir] >  -1: continue
        grid[pos + dir] = count
        pos = pos + dir
        break

import time
st = time.time()

pos = start
cheats = 0
while pos != end:
    next = pair(0, 0)
    for dir in dirs.straight:
        if (pos + dir) not in grid: continue
        if grid[pos + dir] == grid[pos] + 1:
            next = pos + dir
        if (pos + dir*2) not in grid: continue
        if grid[pos + dir*2] - grid[pos] >= 102:
            cheats += 1
    pos = next

et = time.time()
print((et - st)*1000)
print(cheats)






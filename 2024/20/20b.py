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
    print(pos)
    next = pair(0, 0)
    for dr in range(-20, 21):
        rest = 20 - abs(dr)
        for dc in range(-rest, rest + 1):
            dpos = pos + pair(dr, dc)
            if dpos not in grid: continue
            if grid[dpos] == grid[pos] + 1: next = dpos
            if grid[dpos] != -1 and (grid[dpos] - grid[pos]) >= (100 + abs(dr) + abs(dc)):
                cheats += 1
    pos = next
            
et = time.time()
print((et - st)*1000)
print(cheats)
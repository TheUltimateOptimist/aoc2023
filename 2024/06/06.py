from __future__ import annotations
from util import read, Grid, dirs, rotate90

grid = Grid.from_input(read())
pos = grid.find('^'); assert pos is not None
dir = dirs.up

while (pos + dir) in grid:
    if grid[pos + dir] == '#':
        dir = rotate90(dir)
        continue
    grid[pos] = 'x'
    pos = pos + dir

print(grid.count('x') + 1)
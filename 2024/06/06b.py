from __future__ import annotations
from util import read, Grid, dirs, pair, rotate90

grid = Grid.from_input(read())
start_pos = grid.find('^'); assert start_pos is not None
start_dir = dirs.up

def loops(pos: pair, dir: pair) -> bool:
    seen: set[tuple[pair, pair]] = set()
    while True:
        seen.add((pos, dir))
        if (pos + dir) not in grid:
            return False
        if grid[pos + dir] == '#':
            dir = rotate90(dir)
        elif (pos + dir, dir) in seen:
            return True
        else: pos = pos + dir

count = 0
for pos, val in grid:
    if val != '.': continue
    grid[pos] = '#'
    if loops(start_pos, start_dir):
        count += 1
    grid[pos] = '.'

print(count)






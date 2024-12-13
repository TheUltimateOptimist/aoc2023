from util import read, Grid, dirs

grid = Grid.from_input(read().strip())

count = 0
for pos, c in grid:
    if c != 'X': continue
    for dir in dirs.all:
        if ''.join(grid.get_next(pos, dir, 4)) == 'XMAS':
            count += 1
print(count)
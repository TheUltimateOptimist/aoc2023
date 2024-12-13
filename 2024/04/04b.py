from util import read, Grid

grid = Grid.from_input(read().strip())

count = 0
for pos, c in grid:
    if c == 'A' and ''.join(grid.get_diagonal(pos)) in ('MSSM', 'SSMM', 'MMSS', 'SMMS'):
        count += 1
print(count)
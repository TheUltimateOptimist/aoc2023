from util import read, Grid, pair, dirs

grid = Grid.from_input(read())

def find_destinations(pos: pair, destinations: list[pair]) -> None:
    for dir in dirs.straight:
        if pos + dir in grid and int(grid[pos]) == int(grid[pos + dir]) - 1:
            if grid[pos + dir] == '9':
                destinations.append(pos + dir)
            else:
                find_destinations(pos + dir, destinations)

sum = 0
for pos, value in grid:
    if value != '0': continue
    destinations: list[pair] = list()
    find_destinations(pos, destinations)
    sum += len(destinations)

print(sum)
from util import read, Grid, dirs, pair

grid = Grid.from_input(read())

def get_data(start: pair) -> tuple[int, int]:
    area = 1
    diameter = 0
    char = grid[start]
    grid[start] = f'0{char}'
    for dir in dirs.straight:
        if (start + dir) in grid and grid[start + dir] == char:
            darea, ddiameter = get_data(start + dir)
            area += darea
            diameter += ddiameter
        elif not (start + dir in grid) or not grid[start + dir].endswith(char):
            diameter+=1
    return (area, diameter)

sum = 0
for pos, c in grid:
    if not c.startswith('0'):
        area, diameter = get_data(pos)
        sum += area * diameter
print(sum)

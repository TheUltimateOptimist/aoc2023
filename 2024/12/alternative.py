from util import read, Grid, dirs, pair, corners

grid = Grid.from_input(read())

def get_data(start: pair) -> tuple[int, int, int]:
    char = grid[start]
    grid[start] = f'0{char}'
    area, corners1, corners3 = 1, 0, 0
    for corner in corners.all:
        neighbours = grid.get_by_corner(start, corner, lambda x: x.endswith(char))
        if len(neighbours) == 1: corners1 += 1
        if len(neighbours) == 2 and neighbours[0].a != neighbours[1].a and neighbours[0].b != neighbours[1].b: corners1 += 1
        if len(neighbours) == 3: corners3 += 1
    for dir in dirs.straight:
        if (start + dir) in grid and grid[start + dir] == char:
            narea, ncorners1, ncorners3 = get_data(start + dir)
            area, corners1, corners3 = area + narea, corners1 + ncorners1, corners3 + ncorners3
    return area, corners1, corners3

sum = 0
for pos, c in grid:
    if not c.startswith('0'):
        area, corners1, corners3 = get_data(pos)
        if corners3 % 3 != 0:
            print("fuck")
        sum += area * (corners1 + corners3 // 3) 
print(sum)
from util import read, dirs, Grid, rotate180, pair

input = read().split("\n\n")
grid = Grid.from_input(input[0])
characters = ''.join(input[1].split('\n'))
directions = {'^': dirs.up, '>': dirs.right, 'v': dirs.down, '<': dirs.left}

def move(start: pair, dir: pair) -> pair:
    pos = start
    while (pos + dir) in grid and grid[pos + dir] == 'O':
        pos = pos + dir
    if (pos + dir) in grid and grid[pos + dir] == '.':
        while (pos + dir) != start:
            grid[pos + dir] = grid[pos]
            pos = pos + rotate180(dir)
        grid[start] = '.'
        return start + dir
    return start

pos = grid.find('@'); assert pos is not None
for char in characters:
    direction = directions[char]
    pos = move(pos, direction)

total = 0
for p, char in grid:
    if char == 'O':
        total += 100*p.a + p.b
print(total)
    
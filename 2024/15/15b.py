from util import read, dirs, Grid, rotate180, pair
from typing import Iterable

input = read().split("\n\n")
grid_lines = input[0].splitlines()
grid_data: list[list[str]] = []
for grid_line in grid_lines:
    grid_data.append([])
    for char in grid_line:
        grid_data[-1].append(char if char != 'O' else '[')
        if char == '@': grid_data[-1].append('.')
        else: grid_data[-1].append(char if char != 'O' else ']')
grid = Grid(grid_data)
characters = ''.join(input[1].split('\n'))
directions = {'^': dirs.up, '>': dirs.right, 'v': dirs.down, '<': dirs.left}

def move_vertical(start: pair, dir: pair) -> pair:
    if (start + dir) not in grid or grid[start + dir] == '#':
        return start
    if grid[start + dir] == '.': 
        grid[start + dir] = '@'
        grid[start] = '.'
        return start + dir
    boxes: list[pair] = []
    if grid[start + dir] == '[':
        boxes.append(start + dir)
    elif grid[start + dir] == ']': 
        boxes.append(start + dir + dirs.left)
    index = 0
    while index < len(boxes): 
        box = boxes[index]
        if (box + dir) not in grid or (box + dir + dirs.right) not in grid:
            return start
        if grid[box + dir] == '#' or grid[box + dir + dirs.right] == '#':
            return start
        if grid[box + dir] == ']':
            boxes.append(box + dir + dirs.left)
        if grid[box + dir] == '[':
            boxes.append(box + dir)
        if grid[box + dir + dirs.right] == '[':
            boxes.append(box + dir + dirs.right)
        index += 1
    
    for i in range(len(boxes) - 1, -1, -1):
        box = boxes[i]
        grid[box] = '.'
        grid[box + dirs.right] =  '.'
        grid[box + dir] = '['
        grid[box + dir + dirs.right] = ']'
    grid[start + dir] = '@'
    grid[start] = '.'
    return start + dir
        
def move_horizontal(start: pair, dir: pair) -> pair:
    pos = start
    while (pos + dir) in grid and grid[pos + dir] in ('[', ']'):
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
    if direction in (dirs.left, dirs.right):
        pos = move_horizontal(pos, direction)
    else: pos = move_vertical(pos, direction)

print(grid)

class List[T](list):
    def __init__(self, iterable: Iterable[T] | None = None):
        super().__init__()

some = List()
some.append(4)
print(some[0])



total = 0
for p, char in grid:
    if char == '[':
        total += 100*p.a + p.b
print(total)
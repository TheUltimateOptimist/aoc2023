from util import read, analyze_polygon, to_lines
from enum import Enum

grid = read().split("\n")
width = len(grid[0])
height = len(grid)
srow = 0
scol = 0

for row in range(len(grid)):
    for col in range(len(grid[0])):
        if grid[row][col] == "S":
            srow = row
            scol = col

class Direction(Enum):
    up = (-1, 0)
    down = (1, 0)
    right = (0, 1)
    left = (0, -1)
    stuck = (0, 0)
    finished = (-1, -1)

def nextDirection(goingIn: Direction, row: int, col: int) -> Direction:
    if row < 0 or row > height - 1 or col < 0 or col > width - 1:
        return Direction.stuck
    match grid[row][col]:
        case '.': return Direction.stuck
        case 'S': return Direction.finished
        case '|': return goingIn if goingIn == Direction.down or goingIn == Direction.up else Direction.stuck
        case '-': return goingIn if goingIn == Direction.right or goingIn == Direction.left else Direction.stuck
        case 'L': 
            if goingIn == Direction.down:
                return Direction.right
            elif goingIn == Direction.left:
                return Direction.up
            return Direction.stuck
        case 'J':
            if goingIn == Direction.down:
                return Direction.left
            elif goingIn == Direction.right:
                return Direction.up
            return Direction.stuck
        case '7':
            if goingIn == Direction.right:
                return Direction.down
            elif goingIn == Direction.up:
                return Direction.left
            return Direction.stuck
        case 'F':
            if goingIn == Direction.left:
                return Direction.down
            elif goingIn == Direction.up:
                return Direction.right
            return Direction.stuck
    raise Exception("Unreachable")

coordinates: list[tuple[int, int]] = []

for direction in [Direction.up, Direction.down, Direction.right, Direction.left]:
    steps = 0
    row = srow
    col = scol
    coordinates.append((row, col))
    while direction != Direction.stuck:
        row = direction.value[0] + row
        col = direction.value[1] + col
        coordinates.append((row, col))
        steps += 1
        direction = nextDirection(direction, row, col) 
        if direction == Direction.finished:
            print(f"steps: {steps // 2}")
            print(analyze_polygon(to_lines(coordinates)))
            exit()
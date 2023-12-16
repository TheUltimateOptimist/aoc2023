from util import read
import sys

sys.setrecursionlimit(6000)
grid = read().split("\n")

visited = set()
seen = set()

right = (0, 1)
down = (1, 0)
left = (0, -1)
up = (-1, 0)

def go(direction: tuple[int, int], row: int, col: int):
    if row < 0 or row >= len(grid) or col < 0 or col >= len(grid[0]) or (direction, row, col) in seen:
        return
    seen.add((direction, row, col))
    visited.add(row*len(grid[0]) + col)
    match(grid[row][col]):
        case ".": go(direction, row + direction[0], col + direction[1])
        case "|": go(up, row + up[0], col + up[1]), go(down, row + down[0], col + down[1])
        case "-": go(left, row + left[0], col + left[1]), go(right, row + right[0], col + right[1])
        case "/": go((-direction[1], -direction[0]), row + -direction[1], col + -direction[0])
        case "\\": go((direction[1], direction[0]), row + direction[1], col + direction[0])

go(right, 0, 0)
print(f"result = {len(visited)}")

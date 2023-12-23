from util import read
from sys import setrecursionlimit

setrecursionlimit(6000)

grid = read().split("\n")
start = (0, 1)
end = (len(grid) - 1, len(grid[0]) - 2)
direction = (1, 0)


def get_possible_directions(direction: tuple[int, int], row: int, col: int, stepped_on: set[tuple[int, int]]) -> list[tuple[int, int]]:
    directions: list[tuple[int, int]] = []
    for new_direction in [(0,1), (0, -1), (1, 0), (-1, 0)]:
        nrow = new_direction[0] + row
        ncol = new_direction[1] + col
        if (nrow, ncol) in stepped_on:
            continue
        if new_direction != (-direction[0], -direction[1]) and grid[nrow][ncol] != "#" and nrow >= 0 and nrow < len(grid) and ncol >= 0 and ncol < len(grid[0]):
            directions.append(new_direction)
    return directions

from dataclasses import dataclass

@dataclass
class Way:
    row: int
    col: int
    steps: int
    direction: tuple[int, int]
    stepped_on: set[tuple[int, int]]


ways = [Way(0, 1, 0, direction, set())]
max_steps = 0

while len(ways) > 0:
    for i in range(len(ways) - 1, -1, -1):
        way = ways[i]
        if way.row == len(grid) - 1 and way.col == len(grid[0]) - 2:
            max_steps = max(max_steps, way.steps)
            print(max_steps)
            print(len(ways))
            del ways[i]
            continue 
        possible_directions = get_possible_directions(way.direction, way.row, way.col, way.stepped_on)
        if len(possible_directions) == 0:
            del ways[i]
            continue
        if len(possible_directions) > 1:
            way.stepped_on.add((way.row, way.col))
            for j in range(1, len(possible_directions)):
                direction = possible_directions[j]
                ways.append(Way(direction[0] + way.row, direction[1] + way.col, way.steps + 1, direction, set(way.stepped_on)))
        
        way.direction = possible_directions[0]
        way.row = way.direction[0] + way.row
        way.col = way.direction[1] + way.col
        way.steps += 1

print(f"result = {max_steps}")

# def go(steps: int, direction: tuple[int, int], row: int, col: int):
#     steps += 1
#     if row == len(grid) - 1 and col == len(grid[0]) - 2: # reached end
#         return steps
#     for new_direction in [(0,1), (0, -1), (1, 0), (-1, 0)]:
#         nrow = new_direction[0] + row
#         ncol = new_direction[1] + col
#         if new_direction != (-direction[0], -direction[1]) and grid[nrow][ncol] != "#" and nrow >= 0 and nrow < len(grid) and ncol >= 0 and ncol < len(grid[0]):
#             steps = max(steps, go(steps, new_direction, nrow, ncol))
#     return steps



# print(f"result = {go(0, direction, start[0], start[1])}")

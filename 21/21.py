from util import read

import sys

from collections import deque



grid = read().split("\n")

reached = set()
visited: dict[tuple[int, int], int] = dict() 

start = (0, 0)
for row in range(len(grid)):
    for col in range(len(grid[0])):
        if grid[row][col] == "S":
            start = (row, col)
            break


new_grid = list(grid)

def go(visiting: tuple[int, int], steps: int) -> None:
    if steps > 64 or visiting[0] < 0 or visiting[1] < 0 or visiting[0] >= len(grid) or visiting[1] >= len(grid[0]) or grid[visiting[0]][visiting[1]] == "#":
        return
    updated_steps = False
    for direction in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
        neighbor = (visiting[0] + direction[0], visiting[1] + direction[1])
        if neighbor in visited and visited[neighbor] < steps - 1:
            steps = visited[neighbor] + 1
            updated_steps = True
    if visiting in visited and not updated_steps:
        return
    if steps % 2 == 0:
        reached.add(visiting)
    visited[visiting] = steps
    #line = list(new_grid[visiting[0]])
    #line[visiting[1]] = str(steps if steps < 10 else steps - 10)
    #new_grid[visiting[0]] = "".join(line)
    for direction in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
        go((visiting[0] + direction[0], visiting[1] + direction[1]), steps + 1)

def correct_go(start: tuple[int, int], steps: int) -> None:
    if start[0] < 0 or start[1] < 0 or start[0] >= len(grid) or start[1] >= len(grid[0]) or grid[start[0]][start[1]] == "#":
        return
    if steps == 12:
        reached.add(start)
        line = list(new_grid[start[0]])
        line[start[1]] = "v"
        new_grid[start[0]] = "".join(line)
        return
    for direction in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
        correct_go((start[0] + direction[0], start[1] + direction[1]), steps + 1)

def get_sign(coordinates: tuple[int, int]) -> str:
    return grid[coordinates[0] % len(grid)][coordinates[1] % len(grid[0])]

def another(limit: int):
    queue = deque([(start, 0)])
    visited = set()

    while queue:
        current_node, distance = queue.popleft()

        if current_node not in visited:
            visited.add(current_node)
            for direction in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                new_node = (current_node[0] + direction[0], current_node[1] + direction[1])
                if distance < limit and new_node not in visited and get_sign(new_node) != "#":
                    queue.append((new_node, distance + 1))
    count = 0
    for node in visited:
        if (node[0] - start[0] + node[1] - start[1]) % 2 == limit % 2:
            count += 1
    return count

for i in range(5, 100, 2):
    print(another(i + 2) - another(i))

#go(start, 0)
# print(reached)
# for field in reached:
#     print(field[0] - 5 + field[1] - 5)
print(f"result = {len(reached)}")

# for i in range(len(grid)):
#     print(grid[i])
# print("")
# for i in range(len(new_grid)):
#     print(new_grid[i])

    
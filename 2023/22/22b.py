from util import read
from dataclasses import dataclass

@dataclass
class Brick:
    start: tuple[int, int, int]
    end: tuple[int, int, int]
    name: str

bricks: list[Brick] = []
for i, line in enumerate(read().split("\n")):
    start = tuple(map(lambda x: int(x), line.split("~")[0].split(",")))
    end = tuple(map(lambda x: int(x), line.split("~")[1].split(",")))
    bricks.append(Brick(start, end, chr(65 + i)))

bricks.sort(key=lambda b: (b.start[2], b.end[2]))

def no_brick_overlap(a: Brick, b: Brick) -> bool:
    no_x_overlap = (a.start[0] < b.start[0] and a.end[0] < b.start[0]) or (a.start[0] > b.end[0] and a.end[0] > b.end[0])
    no_y_overlap = (a.start[1] < b.start[1] and a.end[1] < b.start[1]) or (a.start[1] > b.end[1] and a.end[1] > b.end[1])
    return no_x_overlap or no_y_overlap 


# fall down
for i in range(len(bricks)):
    if bricks[i].start[2] <= 1: # already at bottom
        continue
    max_z = 1
    for j in range(i - 1, -1, -1):
        if not no_brick_overlap(bricks[i], bricks[j]):
            max_z = max(max_z, bricks[j].end[2] + 1)
    bricks[i].end = (bricks[i].end[0], bricks[i].end[1], bricks[i].end[2] - bricks[i].start[2] + max_z)
    bricks[i].start = (bricks[i].start[0], bricks[i].start[1], max_z)

holds: dict[int, set[int]] = {i: set() for i in range(len(bricks))}
holded_by: dict[int, set[int]] = {i: set() for i in range(len(bricks))}

for i in range(len(bricks)):
    index = 0
    while index < len(bricks) :#and bricks[index].start[2] <= bricks[i].end[2] + 1:
        if index != i and bricks[index].start[2] == bricks[i].end[2] + 1 and not no_brick_overlap(bricks[index], bricks[i]):
            holded_by[index].add(i)
            holds[i].add(index)
        index += 1

def add_falling(index: int, to: set[int]):
    for value in holds[index]:
        if len(holded_by[value].difference(to)) > 0:
            continue 
        to.add(value)
        add_falling(value, to)

count = 0
for key, value in holds.items():
    can_be_disintegrated = True 
    for index in value:
        if len(holded_by[index]) == 1:
            can_be_disintegrated = False
    if not can_be_disintegrated:
        falling = set()
        falling.add(key)
        add_falling(key, falling)
        count += len(falling) - 1

print(f"result = {count}")
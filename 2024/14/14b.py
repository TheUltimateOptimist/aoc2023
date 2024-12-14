from util import read, pair, dirs
from dataclasses import dataclass

@dataclass
class Robot:
    p: pair
    v: pair

@dataclass
class Quadrant:
    x_greater_equals: int
    x_smaller: int
    y_greater_equals: int
    y_smaller: int

# x = 11
# y = 7
x = 101
y = 103

quadrants = [
    Quadrant(0, x // 2, 0, y // 2),
    Quadrant(x // 2 + 1, x, 0, y // 2),
    Quadrant(x // 2 + 1, x, y // 2 + 1, y),
    Quadrant(0, x // 2, y // 2 + 1, y)
]

lines = read().strip().splitlines()
robots: dict[pair, list[pair]] = dict()
for line in lines:
    pos = pair(*list(map(lambda x: int(x), line.split(" ")[0].split("p=")[1].split(","))))
    vel = pair(*list(map(lambda x: int(x), line.split(" ")[1].split("v=")[1].split(","))))
    if robots.get(pos) is None:
        robots[pos] = [vel]
    else: robots[pos].append(vel)

heuristic: tuple[int, int] = (-1, 0)
for i in range(10000):
    new_robots: dict[pair, list[pair]] = dict()
    for pos, velocities in robots.items():
        for vel in velocities:
            new_pos = pos + vel 
            if new_pos.r < 0:
                new_pos = pair(new_pos.r + x, new_pos.c)
            elif new_pos.r >= x:
                new_pos = pair(new_pos.r - x, new_pos.c)
            if new_pos.c < 0:
                new_pos = pair(new_pos.r, new_pos.c + y)
            elif new_pos.c >= y:
                new_pos = pair(new_pos.r, new_pos.c - y)
            if new_robots.get(new_pos) is None:
                new_robots[new_pos] = [vel]
            else: new_robots[new_pos].append(vel)
    robots = new_robots

    if i == 6751:
        output = ''
        for a in range(y):
            line = ['.' for i in range(x)]
            for b in range(x):
                if robots.get(pair(b, a)) is not None:
                    line[b] = 'X'
            output += ''.join(line)
            output += '\n'
        print(output, end='')

    new_h = 0
    for pos, velocities in robots.items():
        count = 0
        for dir in dirs.straight:
            if robots.get(pos + dir) is not None:
                count -= 1
        new_h += count
    if new_h < heuristic[1]:
        heuristic = (i, new_h)



print(heuristic[0] + 1)
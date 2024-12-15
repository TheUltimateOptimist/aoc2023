from util import read, pair
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

x = 11
y = 7
#x = 101
#y = 103

quadrants = [
    Quadrant(0, x // 2, 0, y // 2),
    Quadrant(x // 2 + 1, x, 0, y // 2),
    Quadrant(x // 2 + 1, x, y // 2 + 1, y),
    Quadrant(0, x // 2, y // 2 + 1, y)
]

lines = read().strip().splitlines()
robots: list[Robot] = []
for line in lines:
    robots.append(
        Robot(
            pair(*list(map(lambda x: int(x), line.split(" ")[0].split("p=")[1].split(",")))),
            pair(*list(map(lambda x: int(x), line.split(" ")[1].split("v=")[1].split(",")))),
        )
    )

for i in range(100):
    for robot in robots:
        new_pos = robot.p + robot.v
        if new_pos.a < 0:
            new_pos = pair(new_pos.a + x, new_pos.b)
        elif new_pos.a >= x:
            new_pos = pair(new_pos.a - x, new_pos.b)
        if new_pos.b < 0:
            new_pos = pair(new_pos.a, new_pos.b + y)
        elif new_pos.b >= y:
            new_pos = pair(new_pos.a, new_pos.b - y)
        robot.p = new_pos

print(robots)

result = 1
for quadrant in quadrants:
    count = 0
    for robot in robots:
        if robot.p.a >= quadrant.x_greater_equals and robot.p.a < quadrant.x_smaller \
        and robot.p.b >= quadrant.y_greater_equals and robot.p.b < quadrant.y_smaller:
            count += 1
    result *= count

print(result)





from util import read
from dataclasses import dataclass

@dataclass(frozen=True)
class Path:
    position: tuple[int, int, int]
    velocity: tuple[int, int, int]

paths: list[Path] = []

for line in read().split("\n"):
    parts = line.split(" @ ")
    position = tuple(map(lambda x: int(x), parts[0].split(", ")))
    velocity = tuple(map(lambda x: int(x), parts[1].split(", ")))
    paths.append(Path(position, velocity))

def calcFunc(path: Path) -> tuple[int, int]:
    m = path.velocity[1] / path.velocity[0]
    b = path.position[1] - m*path.position[0]
    return (m, b)

def calcIntersectionPoint(a: tuple[int, int], b: tuple[int, int]) -> tuple[int, int] | None:
    if a[0] - b[0] == 0:
        return None
    x = (b[1] - a[1]) / (a[0] - b[0])
    y = a[0]*x + a[1]
    #print(f"fa: {a}, fb: {b} -> {(x,y)}")
    return (x, y)

count = 0

for i, path_a in enumerate(paths):
    for j in range(i + 1, len(paths)):
        path_b = paths[j]
        func_a = calcFunc(path_a)
        func_b = calcFunc(path_b)
        intersection = calcIntersectionPoint(func_a, func_b)
        #print(f"a: {path_a.position} y = {func_a[0]}x + {func_a[1]}, b: {path_b.position} y = {func_b[0]}x + {func_b[1]} -> {intersection}")
        if intersection == None or intersection[0] < 200000000000000 or intersection[1] > 400000000000000:
            continue
        if intersection[0] > 400000000000000 or intersection[1] < 200000000000000:
            continue
        if path_a.velocity[0] > 0 and intersection[0] < path_a.position[0] or path_a.velocity[0] < 0 and intersection[0] > path_a.position[0]:
            continue
        if path_b.velocity[0] > 0 and intersection[0] < path_b.position[0] or path_b.velocity[0] < 0 and intersection[0] > path_b.position[0]:
            continue
        count += 1

print(f"result = {count}")
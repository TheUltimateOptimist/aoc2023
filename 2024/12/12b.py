from util import read, Grid, dirs, pair, rotate90, rotate270
from dataclasses import dataclass
grid = Grid.from_input(read())

@dataclass
class Side:
    dir: pair
    root: pair
    a: int 
    c: int

class SideStore:
    def __init__(self) -> None:
        self.sides: list[Side] = []
        self.correction = 0

    def insert(self, pos, dir) -> None:
        a_match: Side | None = None
        c_match: Side | None = None
        for side in self.sides:
            if side.dir == dir:
                if pos == (side.root + rotate90(side.dir) * side.a):
                    a_match = side
                elif pos == (side.root + rotate270(side.dir) * side.c):
                    c_match = side
        if a_match is not None:
            a_match.a += 1
        if c_match is not None:
            c_match.c += 1 
        if a_match is None and c_match is None:
            self.sides.append(Side(dir, pos, 1, 1))
        if a_match is not None and c_match is not None:
            self.correction += 1

    @property
    def count(self) -> int:
        return len(self.sides) - self.correction


def get_data(start: pair, sidestore: SideStore) -> int:
    area = 1
    char = grid[start]
    grid[start] = f'0{char}'
    for dir in dirs.straight:
        if (start + dir) in grid and grid[start + dir] == char:
            area += get_data(start + dir, sidestore)
        elif not (start + dir in grid) or not grid[start + dir].endswith(char):
            sidestore.insert(start, dir)
    return area 

sum = 0
for pos, c in grid:
    if not c.startswith('0'):
        sidestore = SideStore()
        area = get_data(pos, sidestore)
        sum += area * sidestore.count
print(sum)
from __future__ import annotations
import sys
from dataclasses import dataclass
from typing import Callable

def read():
    year = sys.argv[0].split("/")[-3]
    day = sys.argv[0].split("/")[-2]
    filePath = f"{year}/{day}/test.txt"
    if (len(sys.argv) <= 1):
        filePath = f"{year}/{day}/input.txt"
    with open(filePath, "r", encoding="ascii") as file:
        return '\n'.join(map(lambda t: t.strip(), file.read().strip().splitlines()))


def to_lines(points: list[tuple[int, int]]) -> list[tuple[int, int]]:
    if points[0] != points[-1]:
        raise Exception("The given points could not be parsed becuase the first and last one are not identical!")
    lines: list[tuple[int, int]] = []
    lines.append(points[0])
    lines.append(points[1])
    index = 0
    if lines[0][1] != lines[1][1]:
        index = 1
    for i in range(2, len(points)):
        if points[i][0] != lines[-1][0] and index == 0:
            lines[-1] = (points[i][0], lines[-1][1]) 
        elif points[i][0] != lines[-1][0] and index == 1:
            lines.append(points[i])
            index = 0
        elif points[i][1] != lines[-1][1] and index == 1:
            lines[-1] = (lines[-1][0], points[i][1])
        elif points[i][1] != lines[-1][1] and index == 0:
            lines.append(points[i])
            index = 1
    return lines

@dataclass(frozen=True)
class PolygonInfo:
    area: float
    outside: int
    inside: int
    bothside: int

def analyze_polygon(edges: list[tuple[int, int]]) -> PolygonInfo:
    if edges[0] != edges[-1]:
        raise Exception("The given polygon could not be analyzed, because its last and first coordinate is not identical!")
    outer = 0
    for i in range(1, len(edges)):
        if edges[i][0] == edges[i - 1][0]:
            outer += abs(edges[i][1] - edges[i - 1][1])
        elif edges[i][1] == edges[i - 1][1]:
            outer += abs(edges[i][0] - edges[i - 1][0])
        else:
            raise Exception("all edges need to be connected with a straight line!")
    a = 0
    b = 0
    for i in range(len(edges) - 1):
        a += edges[i][0]*edges[i+1][1]
    for i in range(1, len(edges)):
        b += edges[i][0]*edges[i-1][1]
    area = 0.5*abs(a - b)
    inner = 1 + area - outer / 2
    return PolygonInfo(area, outer, int(inner), outer + int(inner))



#############################
# FOR WORKING WITH GRIDS
###########################

@dataclass(frozen=True)
class pair:
    a: int
    b: int

    def __add__(self, other) -> pair:
        return pair(self.a + other.r, self.b + other.c)

    def __sub__(self, other) -> pair:
        return pair(self.a - other.r, self.b - other.c)

    def __mul__(self, other: int) -> pair:
        return pair(self.a*other, self.b*other)

class dirs:
    none = pair(0, 0)
    up = pair(-1, 0)
    right = pair(0, 1)
    down = pair(1, 0)
    left = pair(0, -1)
    lup = pair(-1, -1)
    rup = pair(-1, 1)
    ldown = pair(1, -1)
    rdown = pair(1, 1)

    diagonal = [lup, rup, rdown, ldown]
    straight = [up, right, down, left]
    diagonaln = [none, lup, rup, rdown, ldown]
    straightn = [none, up, right, down, left]
    all = [up, rup, right, rdown, down, ldown, left, lup]
    alln = [none, up, rup, right, rdown, down, ldown, left, lup] 

class corners:
    rup = 0
    rdown = 1
    ldown = 2
    lup = 3

    all = [lup, rup, rdown, ldown]

class Grid[T]:
    def __init__(self, data: list[list[T]]) -> None:
        self.data = data
        self.numrows = len(self.data)
        self.numcols = len(self.data[0])
        self._at = pair(0, 0)

    def __contains__(self, item) -> bool:
        if isinstance(item, pair):
            return item.a >= 0 and item.b >= 0 and item.a < self.numrows and item.b < self.numcols
        return item in self.data

    def __str__(self) -> str:
        output = ""
        for row in self.data:
            for value in row:
                output += str(value)
            output += '\n'
        return output[:-1]

    def find(self, element: T) -> pair | None:
        for row in range(len(self.data)):
            for col in range(len(self.data[0])):
                if self.data[row][col] == element:
                    return pair(row, col)
        return None

    def count(self, element: T) -> int:
        count = 0
        for row in range(len(self.data)):
            for col in range(len(self.data[0])):
                if self.data[row][col] == element:
                    count += 1
        return count

    def get_next(self, start: pair, dir: pair, num: int, skip_first: bool = False) -> list[T]:
        result: list[T] = []
        if skip_first:
            start = start + dir
        while num > 0 and start in self:
            result.append(self[start])
            start = start + dir
            num -= 1
        return result

    def get_diagonal(self, start: pair) -> list[T]:
        result: list[T] = []
        for dir in dirs.diagonal:
            if (start + dir) in self:
                result.append(self[start + dir])
        return result

    def get_straight(self, start: pair) -> list[T]:
        result: list[T] = []
        for dir in dirs.straight:
            if (start + dir) in self:
                result.append(self[start + dir])
        return result

    def get_by_corner(self, start: pair, corner: int, filter: Callable[[T], bool] | None = None) -> list[pair]:
        result: list[pair] = [start]
        direction = dirs.straight[corner]
        for _ in range(3):
            start = start + direction
            if start in self and (filter == None or filter(self[start])): result.append(start)
            direction = rotate90(direction)
        return result

    @classmethod
    def from_input(cls, input: str) -> Grid[str]:
        return Grid(list(map(lambda x: list(x), input.strip().splitlines())))

    def __setitem__(self, at: pair, val: T) -> None:
        self.data[at.a][at.b] = val

    def __getitem__(self, at: pair) -> T:
        return self.data[at.a][at.b]

    def __iter__(self) -> 'Grid[T]':
        self._at = pair(0, 0)
        return self

    def __next__(self) -> tuple[pair, T]:
        if not self._at in self:
            raise StopIteration
        value = self[self._at]
        pos = self._at
        self._at = pair(
            self._at.a + 1 if self._at.b >= self.numcols - 1 else self._at.a,
            self._at.b + 1 if self._at.b < self.numcols - 1 else 0
        )
        return (pos, value)

def rotate90(dir: pair) -> pair:
    '''
    Returns a new Direction object rotated by 90 degrees clockwise.
    '''
    return pair(dir.b, -dir.a)

def rotate180(dir: pair) -> pair:
    '''
    Returns a new Direction object rotated by 180 degrees clockwise.
    '''
    return pair(-dir.a, -dir.b)

def rotate270(dir: pair) -> pair:
    '''
    Returns a new Direction Object rotated by 270 degrees clockwise.
    '''
    return pair(-dir.b, dir.a)

def join(ranges: list[pair]) -> list[pair]:
    new_ranges: list[pair] = []
    ranges.sort(key=lambda p: p.a)
    new_ranges.append(ranges[0])
    for range in ranges[1:]:
        next = new_ranges[-1].b + 1
        if range.a > next:
            new_ranges.append(range)
        elif range.a <= next and range.b > new_ranges[-1].b:
            new_ranges.append(pair(new_ranges.pop().a, range.b))
    return new_ranges

def numbers(text: str) -> list[int]:
    import re
    pattern = r"-?\d+"
    results = re.findall(pattern, text)
    return list(map(lambda x: int(x), results))
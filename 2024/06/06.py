from __future__ import annotations
from util import read
from dataclasses import dataclass
from enum import Enum

@dataclass(frozen=True)
class Direction:
    dx: int
    dy: int

class Directions(Enum):
    up = Direction(0, -1)
    right = Direction(1, 0)
    left = Direction(-1, 0)
    down = Direction(0, 1)

@dataclass(frozen=True)
class Point:
    x: int
    y: int

    def next(self, direction: Direction) -> Point:
        return Point(self.x + direction.dx, self.y + direction.dy)

class Grid[T]:
    def __init__(self, data: list[list[T]]) -> None:
        self.data = data
        self.dimx = len(data[0])
        self.dimy = len(data)

    def in_bounds(self, point: Point) -> bool:
        return point.y >=0 and point.x >= 0 and point.y < len(self.data) and point.x < len(self.data[0])

    def find(self, element: T) -> Point | None:
        for y in range(len(self.data)):
            for x in range(len(self.data[0])):
                if self.data[y][x] == element:
                    return Point(x, y)
        return None

    def count(self, element: T) -> int:
        count = 0
        for y in range(len(self.data)):
            for x in range(len(self.data[0])):
                if self.data[y][x] == element:
                    count += 1
        return count

    @classmethod
    def from_input(cls, input: str) -> Grid[str]:
        return Grid(list(map(lambda x: list(x), input.strip().splitlines())))

    def set(self, at: Point, value: T) -> None:
        self.data[at.y][at.x] = value

    def get(self, at: Point) -> T:
        return self.data[at.y][at.x]

@dataclass(frozen=True)
class Redirecter[T]:
    on: T
    up: Direction
    right: Direction
    down: Direction
    left: Direction

    def next(self, initial: Direction) -> Direction:
        match(initial):
            case Directions.up.value:
                return self.up
            case Directions.right.value:
                return self.right
            case Directions.down.value:
                return self.down
            case Directions.left.value:
                return self.left
            case _: raise Exception("unreachable")


class Runner[T]:
    def __init__(self, grid: Grid[T], redirecters: list[Redirecter] = [], direction: Direction = Directions.up.value, start: Point = Point(0, 0)) -> None:
        self.grid = grid
        self.redirecters = redirecters
        self.direction = direction
        self.position = start

    def next(self) -> Point | None:
        next = self.position.next(self.direction)
        if not self.grid.in_bounds(next):
            return None
        for redirecter in self.redirecters:
            if grid.get(next) == redirecter.on:
                self.direction = redirecter.next(self.direction)
                actual_next = self.position.next(self.direction)
                if not grid.in_bounds(actual_next):
                    return None
                next = actual_next
                break
        self.position = next
        return self.position

    def go_to(self, element: T) -> None:
        for x in range(self.grid.dimx):
            for y in range(self.grid.dimy):
                p = Point(x, y)
                if self.grid.get(p) == element:
                    self.position = p 
                    return
        raise Exception("can't go to defined element\nelement not found")

    def set(self, value: T) -> None:
        grid.set(self.position, value)

    def get(self) -> T:
        return grid.get(self.position)
        

grid = Grid.from_input(read())
redirecter = Redirecter(
    '#',
    up=Directions.right.value,
    right=Directions.down.value,
    down=Directions.left.value,
    left=Directions.up.value
)
runner = Runner(grid, [redirecter])
runner.go_to('^')
runner.set('x')
while runner.next():
    runner.set('x')


print(runner.grid.count('x'))
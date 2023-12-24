import sys

YEAR = "2023"

def read():
    folderName = sys.argv[0].split("/")[-2]
    day = str(int(folderName))
    filePath = f"{YEAR}/{folderName}/test.txt"
    if (len(sys.argv) <= 1):
        filePath = f"{YEAR}/{folderName}/adventofcode.com_{YEAR}_day_{day}_input.txt"
    with open(filePath, "r", encoding="ascii") as file:
        return file.read().strip()

from dataclasses import dataclass

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
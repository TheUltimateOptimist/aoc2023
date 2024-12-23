from util import read, Grid, pair
from itertools import combinations 

grid = Grid.from_input(read())
frequencies: dict[str, list[pair]] = dict()
for pos, value in grid:
    if value == '.': continue
    positions = frequencies.get(value)
    if positions is not None:
        positions.append(pos)
    else: frequencies[value] = [pos]

antinodes = set()
for frequency, antennas in frequencies.items():
    for first, second in combinations(antennas, 2):
        diff = first - second
        while first in grid:
            antinodes.add(first)
            first = first + diff 
        while second in grid:
            antinodes.add(second)
            second = second - diff 

print(len(antinodes))
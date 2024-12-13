from util import read

grid = read().strip().splitlines()
frequencies: dict[str, list[tuple[int, int]]] = dict()
for i, row in enumerate(grid):
    for j, col in enumerate(row):
        if col != '.':
            positions = frequencies.get(col)
            if positions is not None:
                positions.append((i, j))
            else:
                frequencies[col] = [(i, j)]

antinodes: set[tuple[int, int]] = set()
for frequency in frequencies:
    antennas = frequencies.get(frequency)
    for a in range(len(antennas) - 1):
        for b in range(a + 1, len(antennas)):
            first = antennas[a]
            second = antennas[b]
            firstd = (first[0] - second[0], first[1] - second[1])
            secondd = (second[0] - first[0], second[1] - first[1])
            while first[0] >= 0 and first[0] < len(grid) and first[1] >= 0 and first[1] < len(grid[0]):
                antinodes.add(first)
                first = (first[0] + firstd[0], first[1] + firstd[1])
            while second[0] >= 0 and second[0] < len(grid) and second[1] >= 0 and second[1] < len(grid[0]):
                antinodes.add(second)
                second = (second[0] + secondd[0], second[1] + secondd[1]) 

print(len(antinodes))
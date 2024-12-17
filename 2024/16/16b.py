from util import read, pair, Grid, dirs, rotate90, rotate270, rotate180, DataNumber

grid = Grid.from_input(read())

start = grid.find('S'); assert start is not None
opt = 98416

ways = [(start, dirs.right, 0, DataNumber(dirs.straight))]
paths: list[DataNumber[pair]] = []
visited = {}
index = 0
while len(ways) > 0:
    index += 1
    new_ways = []
    for pos, dir, cost, path in ways:
        ecost = visited.get((pos, dir))
        if ecost is not None and ecost < cost:
            continue
        if grid[pos] == 'E':
            if cost == opt:
                path.append(rotate180(dir))
                paths.append(path)
            continue
        left = rotate270(dir)
        right = rotate90(dir)
        if (pos + dir) in grid and grid[pos + dir] in ('.', 'E'):
            new_ways.append((pos + dir, dir, cost + 1, path.copy().append(rotate180(dir))))
        if (pos + right) in grid and grid[pos + right] in ('.', 'E'):
            new_ways.append((pos + right, right, cost + 1001, path.copy().append(left)))
        if (pos + left) in grid and grid[pos + left] in ('.', 'E'):
            new_ways.append((pos + left, left, cost + 1001, path.copy().append(right)))
        visited[(pos, dir)] = cost
    ways = new_ways

end = grid.find('E'); assert end is not None
tiles = set([start])
for path in paths:
    pos = end
    for dir in path:
        tiles.add(pos) 
        pos = pos + dir

print(len(tiles))


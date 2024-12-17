from util import read, Grid, dirs, rotate90, rotate270

grid = Grid.from_input(read())

start = grid.find('S'); assert start is not None

ways = [(start, dirs.right, 0)]
costs = []
visited = {}
index = 0
while len(ways) > 0:
    index += 1
    new_ways = []
    for pos, dir, cost in ways:
        ecost = visited.get((pos, dir))
        if ecost is not None and ecost < cost:
            continue
        if grid[pos] == 'E':
            costs.append(cost)
            continue
        left = rotate270(dir)
        right = rotate90(dir)
        if (pos + dir) in grid and grid[pos + dir] in ('.', 'E'):
            new_ways.append((pos + dir, dir, cost + 1))
        if (pos + right) in grid and grid[pos + right] in ('.', 'E'):
            new_ways.append((pos + right, right, cost + 1001))
        if (pos + left) in grid and grid[pos + left] in ('.', 'E'):
            new_ways.append((pos + left, left, cost + 1001))
        visited[(pos, dir)] = cost

    ways = new_ways
print(min(costs))
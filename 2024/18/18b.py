from util import read, pair, Grid, dirs

d = 70

sparks: list[pair] = []
for line in read().splitlines():
    sparks.append(pair(*list(map(lambda x: int(x), line.split(",")))))

grid_data: list[list[int]] = []
for i in range(d + 1):
    data = []
    for j in range(d + 1):
        data.append(-1)
    grid_data.append(data)
grid = Grid(grid_data)

for i, spark in enumerate(sparks):
    grid[pair(sparks[i].b, sparks[i].a)] = i

def reachable(time: int) -> bool:
    end = pair(d, d)
    visited: set[pair] = set()
    nodes: list[tuple[pair, int]] = [(pair(0, 0), 0)]
    visited.add(pair(0, 0))

    while len(nodes) > 0:
        new_nodes: list[tuple[pair, int]] = []
        for node in nodes:
            for dir in dirs.straight:
                if node[0] + dir == end:
                    return True
                nextpos = node[0] + dir
                if nextpos in grid and (grid[nextpos] == -1 or grid[nextpos] > time) and not nextpos in visited:
                    new_nodes.append((nextpos, node[1] + 1))
                    visited.add(nextpos)
        nodes = new_nodes
    return False

for i in range(len(sparks)):
    print(i)
    if not reachable(i):
        print(i)
        print(f"{sparks[i].a},{sparks[i].b}")
        break

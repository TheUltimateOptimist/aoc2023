from util import read, pair, Grid, dirs

d = 70

sparks: list[pair] = []
for line in read().splitlines():
    sparks.append(pair(*list(map(lambda x: int(x), line.split(",")))))

grid_data: list[list[str]] = []
for i in range(d + 1):
    data = []
    for j in range(d + 1):
        data.append('.')
    grid_data.append(data)
grid = Grid(grid_data)

for i in range(1024):
    grid[pair(sparks[i].b, sparks[i].a)] = '#'

print(grid)
end = pair(d, d)
visited: set[pair] = set()
nodes: list[tuple[pair, int]] = [(pair(0, 0), 0)]
visited.add(pair(0, 0))
opt = 1_000_000

while len(nodes) > 0:
    new_nodes: list[tuple[pair, int]] = []
    for node in nodes:
        for dir in dirs.straight:
            if node[0] + dir == end:
                if node[1] + 1 < opt: 
                    opt = node[1] + 1
                break
            nextpos = node[0] + dir
            if nextpos in grid and grid[nextpos] == '.' and not nextpos in visited:
                new_nodes.append((nextpos, node[1] + 1))
                visited.add(nextpos)
    nodes = new_nodes
print(opt)




    

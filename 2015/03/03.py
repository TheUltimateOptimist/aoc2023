from util import read, pair, dirs

pos = pair(0, 0)
houses: set[pair] = set([pos])
for house in read():
    match house:
        case '^': pos = pos + dirs.up
        case '>': pos = pos + dirs.right
        case 'v': pos = pos + dirs.down
        case '<': pos = pos + dirs.left
    houses.add(pos)

print(len(houses))
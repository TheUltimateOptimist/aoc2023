from util import read, pair, dirs

pos = pair(0, 0)
line = read()
houses: set[pair] = set([pos])

def distribute(offset: int = 0) -> None:
    pos = pair(0, 0)
    for i in range(offset, len(line), 2):
        match line[i]:
            case '^': pos = pos + dirs.up
            case '>': pos = pos + dirs.right
            case 'v': pos = pos + dirs.down
            case '<': pos = pos + dirs.left
        houses.add(pos)

distribute()
distribute(1)

print(len(houses))
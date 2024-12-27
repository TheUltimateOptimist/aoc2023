from util import read, pair

commands: list[tuple[str, pair, pair]] = []
for line in read().splitlines():
    nat = (2, 4)
    if line.startswith('toggle'): nat = (1,3)
    a = pair(*map(lambda x: int(x), line.split(" ")[nat[0]].split(',')))
    b = pair(*map(lambda x: int(x), line.split(" ")[nat[1]].split(',')))
    if line.startswith('turn on'):
        commands.append(('on', a, b))
    elif line.startswith("turn off"):
        commands.append(('off', a, b))
    elif line.startswith('toggle'):
        commands.append(('toggle', a, b))

grid = [[0 for _ in range(1000)] for _ in range(1000)]
for command in commands:
    for r in range(command[1].a, command[2].a + 1):
        for c in range(command[1].b, command[2].b + 1):
            match command[0]:
                case 'on':
                    grid[r][c] += 1
                case 'off': 
                    if grid[r][c] > 0:
                        grid[r][c] -= 1
                case 'toggle': 
                    grid[r][c] += 2

print(sum(map(lambda row: sum(row), grid)))









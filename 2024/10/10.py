from util import read

grid = read().splitlines()

def find_destinations(r: int, c: int, destinations: set[tuple[int, int]]) -> None:
    for (dr, dc) in [(-1, 0), (0, 1), (1, 0), (0, -1)]:
        rnew = r + dr
        cnew = c + dc
        if rnew >= 0 and cnew >= 0 and rnew < len(grid) and cnew < len(grid[0]):
            if grid[r][c] == str(int(grid[rnew][cnew]) - 1):
                if grid[rnew][cnew] == '9':
                    destinations.append((rnew, cnew))
                else:
                    find_destinations(rnew, cnew, destinations)

sum: int = 0
for r in range(len(grid)):
    for c in range(len(grid[0])):
        if grid[r][c] == '0':
            destinations: list[tuple[int, int]] = list() 
            find_destinations(r, c, destinations)
            print(destinations)
            sum += len(destinations)

print(sum)




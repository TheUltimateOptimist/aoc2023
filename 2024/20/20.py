from util import read, dirs, Grid, pair

grid = Grid.from_input(read())

start = grid.find('S')
end = grid.find('E')

def get_fastest_without_cheating() -> int:
    assert start is not None
    paths: list[tuple[pair, int]] = [(start, 0)]
    visited: dict[pair, int] = dict()
    visited[start] = 0
    while len(paths) > 0:
        new_paths: list[tuple[pair, int]] = []
        for path, cost in paths:
            if path == end:
                return cost
            for dir in dirs.straight:
                if path + dir in grid and grid[path + dir] != '#' and ((path + dir) not in visited.keys() or  visited[path + dir] > cost + 1):
                    new_paths.append((path + dir, cost + 1))
                    visited[path + dir] = cost + 1
        paths = new_paths
    raise Exception("Unreachable")

fastest = get_fastest_without_cheating()

def get_cheats_more_100() -> int:
    count = 0
    assert start is not None
    paths: list[tuple[pair, int, pair | None]] = [(start, 0, None)]
    visited: set[tuple[pair, pair | None]] = set() 
    visited.add((start, None))
    while len(paths) > 0:
        new_paths: list[tuple[pair, int, pair | None]] = []
        for path, cost, cheat in paths:
            print(cost)
            if path == end:
                if cheat is not None:
                    count += 1
                continue
            if cost >= fastest - 1 - 99: continue
            for dir in dirs.straight:
                if path + dir not in grid: continue
                if grid[path + dir] == '#' and cheat is not None: continue
                if (path + dir, cheat) in visited: continue
                if grid[path + dir] == '#' and cheat is None:
                    new_paths.append((path + dir, cost + 1, path + dir))
                elif grid[path + dir] != '#' and (path + dir, cheat) not in visited: 
                    new_paths.append((path + dir, cost + 1, cheat))
                    visited.add((path + dir, cheat))
        paths = new_paths
    return count

print(get_cheats_more_100())






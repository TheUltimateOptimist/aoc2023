from util import Grid, pair, dirs, read
from functools import lru_cache

numpad = Grid[str]([['7', '8', '9'], ['4', '5', '6'], ['1', '2', '3'], ['', '0', 'A']])
dirpad = Grid[str]([['', '^', 'A'], ['<','v','>']])
dirmappings = {dirs.right: '>', dirs.down: 'v', dirs.left: '<', dirs.up: '^', dirs.none: ''}

def create_mappings(grid: Grid[str], mappings: dict[tuple[str, str], list[str]]) -> dict[tuple[str, str], list[str]]:
    for spos, sval in grid:
        for dpos, dval in grid:
            if sval == '' or dval == '': continue
            diff = dpos - spos
            paths: list[str] = []
            if diff.a != 0 and grid[spos + pair(diff.a, 0)] != '':
                paths.append(abs(diff.a)*dirmappings[diff.dirs()[0]] + abs(diff.b)*dirmappings[diff.dirs()[1]] + 'A')
            if diff.b != 0 and grid[spos + pair(0, diff.b)] != '':
                paths.append(abs(diff.b)*dirmappings[diff.dirs()[1]] + abs(diff.a)*dirmappings[diff.dirs()[0]] + 'A')
            if diff.a == 0 and diff.b == 0: paths.append('A')
            mappings[(sval, dval)] = paths
    return mappings


mappings = create_mappings(numpad, {})
mappings = create_mappings(dirpad, mappings)

@lru_cache
def min_len(text: str, depth: int) -> int:
    minimum = 0
    prev = 'A'
    for char in text:
        possibilities = mappings[(prev, char)]
        if depth == 0:
            minimum += len(possibilities[0])
        else: minimum += min(map(lambda x: min_len(x, depth - 1), possibilities))
        prev = char
    return minimum

print(sum(map(lambda code: min_len(code, 25)*int(code[:-1]), read().splitlines())))
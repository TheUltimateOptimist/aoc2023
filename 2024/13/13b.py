from util import read, pair
from dataclasses import dataclass
import math
import numpy as np

@dataclass(frozen=True)
class Game:
    p: pair 
    a: pair
    b: pair

games: list[Game] = []
blocks = read().strip().split('\n\n')
for block in blocks:
    parts = block.strip().splitlines()

    games.append(
        Game(
            pair(*list(map(lambda x: int(x), parts[2].split("X=")[1].split(", Y=")))),
            pair(*list(map(lambda x: int(x), parts[0].split("X+")[1].split(", Y+")))),
            pair(*list(map(lambda x: int(x), parts[1].split("X+")[1].split(", Y+")))),
        )
    )

def gcd2r(a: tuple[int, int], b: tuple[int, int]):
    return math.gcd()

tokens =int(0)
for game in games:
    ax, ay, bx, by = game.a.r, game.a.c, game.b.r, game.b.c
    px, py = game.p.r + 10000000000000, game.p.c + 10000000000000
    x = (by*px - bx*py) / (ax*by - ay*bx)
    y = (px - x*ax) / bx
    if x % 1 == y % 1 == 0:
        tokens += int(3*x + y)
print(int(tokens))
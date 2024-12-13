from util import read, pair
from dataclasses import dataclass

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

tokens = 0
for game in games:
    mintokens = 100_000
    for a in range(101):
        for b in range(101):
            if a*game.a.r + b*game.b.r == game.p.r and a*game.a.c + b*game.b.c == game.p.c and (a*3 + b) < mintokens:
                mintokens = a*3 + b
    if mintokens < 100_000:
        tokens += mintokens

print(tokens)


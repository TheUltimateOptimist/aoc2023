from util import read
import math

dimensions: list[tuple[int, ...]] = []
for line in read().splitlines():
    dimensions.append(tuple(map(lambda x: int(x), line.split("x"))))

print(sum(map(lambda dim: min([2*dim[0] + 2*dim[1], 2*dim[0] + 2*dim[2], 2*dim[1] + 2*dim[2]]) + math.prod(dim), dimensions)))
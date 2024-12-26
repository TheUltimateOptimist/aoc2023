from util import read

dimensions: list[tuple[int, ...]] = []
for line in read().splitlines():
    dimensions.append(tuple(map(lambda x: int(x), line.split("x"))))

print(sum(map(lambda dim: 2*dim[0]*dim[1] + 2*dim[1]*dim[2] + 2*dim[2]*dim[0] + min(dim[0]*dim[1], dim[1]*dim[2], dim[2]*dim[0]), dimensions)))

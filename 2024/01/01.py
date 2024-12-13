from util import read
from functools import reduce

lines = read().splitlines()
lista = list(map(lambda x: int(x.split(" ")[0]), lines))
listb = list(map(lambda x: int(x.split(" ")[-1]), lines))
lista.sort()
listb.sort()
print(reduce(lambda x, y: x + abs(listb[y[0]] - y[1]),enumerate(lista), 0))
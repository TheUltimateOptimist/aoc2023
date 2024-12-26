from util import read
from dataclasses import dataclass
from itertools import combinations
import random

length = 45

@dataclass(frozen=True)
class Circuit:
    left: str
    operation: str
    right: str

blocks = read().split('\n\n')
x: list[int] = [0 for _ in range(length)]
y: list[int] = [0 for _ in range(length)]
circuits: dict[str, Circuit] = {}
for line in blocks[0].splitlines():
    index, value = line.split(": ")
    if index.startswith("x"):
        x[int(index[1:])] = int(value)
    elif index.startswith('y'):
        y[int(index[1:])] = int(value)
for line in blocks[1].splitlines():
    circuit, output = line.split(" -> ")
    circuits[output] = Circuit(*circuit.split(" "))

def calculate_bit(output: str) -> int:
    if output.startswith('x'):
        return x[int(output[1:])]
    if output.startswith('y'):
        return y[int(output[1:])]
    circuit = circuits[output]
    left = calculate_bit(circuit.left)
    right = calculate_bit(circuit.right)
    match circuit.operation:
        case 'AND': return left & right
        case 'OR': return left | right
        case 'XOR': return left ^ right
        case _: raise Exception('Unreachable')


def switch(a: str, b: str) -> None:
    save = circuits[a]
    circuits[a] = circuits[b]
    circuits[b] = save

def add() -> int:
    result = 0
    for output in circuits:
        if output.startswith('z'):
            result += calculate_bit(output)*(2**int(output[1:]))
    return result

def reset() -> None:
    global x, y
    x = [0 for _ in range(length)]
    y = [0 for _ in range(length)]


def test_one(a: int, b: int) -> bool:
    reset()
    for i, val in enumerate(reversed(bin(a).split("b")[1])):
        x[i] = int(val)
    for i, val in enumerate(reversed(bin(b).split("b")[1])):
        y[i] = int(val)
    try:
        actual = add()
        return actual == a + b
    except: return False

def test_rand(max: int, n: int) -> bool:
    for _ in range(n):
        first = random.randint(0, max)
        second = random.randint(0, max - first)
        if not test_one(first, second):
            return False 
    return True

errorbits: list[int] = []
faulty_switches: list[str] = []
for bi in range(length):
    if not test_one(2**bi, 0):
        errorbits.append(bi)

keys = list(filter(lambda x: not (x.startswith('x') or x.startswith('y')), circuits.keys()))
for i, errorbit in enumerate(errorbits):
    max = 2**errorbits[i + 1] - 1 if i + 1 < len(errorbits) else 2**length - 1
    for sa, sb in combinations(keys, 2):
        switch(sa, sb)
        if test_rand(max, 10):
            faulty_switches.extend([sa, sb])
            break
        else: switch(sa, sb)

faulty_switches.sort()
print(','.join(faulty_switches))
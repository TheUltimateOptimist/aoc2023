from util import read
from dataclasses import dataclass

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

result = 0
for output in circuits:
    if output.startswith('z'):
        result += calculate_bit(output)*(2**int(output[1:]))
print(result)


    

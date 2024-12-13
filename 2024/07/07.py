from util import read
from dataclasses import dataclass

@dataclass(frozen=True)
class Equation:
    value: int
    inputs: list[int]

lines = read().splitlines()
equations: list[Equation] = []
for line in lines:
    equations.append(
        Equation(
            int(line.split(":")[0]),
            list(map(lambda x: int(x), line.strip().split(" ")[1:]))
        )
    )

sum = 0
for equation in equations:
    values = [equation.inputs[0]]
    for i in range(1, len(equation.inputs)):
        new_values: list[int] = []
        for j in range(len(values)):
            new_values.append(values[j] + equation.inputs[i])
            new_values.append(values[j] * equation.inputs[i])
            new_values.append(int(str(values[j]) + str(equation.inputs[i])))
        values = new_values
    if equation.value in values:
        sum += equation.value
print(sum)


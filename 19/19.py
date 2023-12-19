from util import read
from dataclasses import dataclass

@dataclass(frozen=True)
class Condition:
    comparison: str | None
    continuation: str

def evaluate_conditions(conditions: list[Condition], part: dict[str, int]) -> str:
    for i in range(len(conditions) - 1):
        letter = conditions[i].comparison[0]
        if eval(str(part[letter]) + conditions[i].comparison[1:]):
            return conditions[i].continuation
    return conditions[-1].continuation
    
workflow_lines = read().split("\n\n")[0].split("\n")
parts_lines = read().split("\n\n")[1].split("\n")

# construct workflows
workflows: dict[str, list[Condition]] = {}
for line in workflow_lines:
    name = line.split("{")[0]
    definition_str = line.split("{")[1][0:-1]
    conditions: list[Condition] = []
    condition_texts = definition_str.split(",")
    for i in range(len(condition_texts) - 1):
        comparison, continuation = condition_texts[i].split(":")
        conditions.append(Condition(comparison, continuation))
    conditions.append(Condition(None, condition_texts[len(condition_texts) - 1]))
    workflows[name] = conditions

# construct parts
parts: list[dict[str, int]] = [] 
for line in parts_lines:
    part: dict[str, int] = {}
    values = line[1:-1].split(",")
    for value in values:
        part[value.split("=")[0]] = int(value.split("=")[1])
    parts.append(part)

total = 0
for part in parts:
    conditions: list[Condition] | None = workflows["in"]
    while conditions != None:
        continuation = evaluate_conditions(conditions, part)
        match (continuation):
            case "R": conditions = None
            case "A": total += sum(part.values());conditions = None
            case _: conditions = workflows[continuation]

print(f"total = {total}")





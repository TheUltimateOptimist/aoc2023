from util import read
from dataclasses import dataclass

keys = ["x", "m", "a", "s"]
GREATER = 0
SMALLER = 4001

@dataclass(frozen=True)
class Workflow:
    terminators: list[str]
    comparisons: list[tuple[str, int | None, int | None]]

def addComparison(range: dict[str, tuple[int, int]], new: tuple[str, int | None, int | None]):
    new_comparison = (new[1] if new[1] is not None else GREATER, new[2] if new[2] is not None else SMALLER)
    to = new[0]
    if new_comparison[0] > range[to][0]:
        range[to] = (new_comparison[0], range[to][1])
    if new_comparison[1] < range[to][1]:
        range[to] = (range[to][0], new_comparison[1])

def invert(comparison: tuple[str, int | None, int | None]) -> tuple[str, int | None, int | None]:
    greater = comparison[2]
    smaller = comparison[1]
    if greater is not None:
        greater -= 1
    if smaller is not None:
        smaller += 1
    return (comparison[0], greater, smaller)
    
workflow_lines = read().split("\n\n")[0].split("\n")
parts_lines = read().split("\n\n")[1].split("\n")

# construct workflows
workflows: dict[str, Workflow] = {}
for line in workflow_lines:
    name = line.split("{")[0]
    definition_str = line.split("{")[1][0:-1]
    comparisons: list[tuple[str, int | None, int | None]] = []
    terminators: list[str] = []
    comparison_texts = definition_str.split(",")
    for i in range(len(comparison_texts) - 1):
        comparison, continuation = comparison_texts[i].split(":")
        terminators.append(continuation)
        if ">" in comparison:
            to, num = comparison.split(">")
            comparisons.append((to, int(num), None))
        else: 
            to, num = comparison.split("<")
            comparisons.append((to, None, int(num)))
    terminators.append(comparison_texts[-1]) 
    workflows[name] = Workflow(terminators, comparisons)

accepted_ranges: list[dict[str, tuple[int, int]]] = []

def register(workflow: Workflow, range: dict[str, tuple[int, int]]):
    for i, terminator in enumerate(workflow.terminators):
        if i < len(workflow.terminators) - 1:
            new_range = dict(range)
            addComparison(new_range, workflow.comparisons[i])
            addComparison(range, invert(workflow.comparisons[i]))
            if terminator == "A":
                accepted_ranges.append(new_range)
            elif terminator != "R":
                register(workflows[terminator], new_range)
        elif terminator == "A":
            accepted_ranges.append(range)
        elif terminator != "R":
            register(workflows[terminator], range)

range = {}
for key in keys:
    range[key] = (GREATER, SMALLER)
register(workflows["in"], range)

# count
result = 0
for range in accepted_ranges:
    product = 1
    for key in keys:
        product *= range[key][1] - range[key][0] - 1
    result += product
print(f"result = {result}")
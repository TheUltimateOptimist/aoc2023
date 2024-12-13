from util import read

def evaluate(text: str) -> int:
    pattern = r"mul\(\d{1,3},\d{1,3}\)"
    import re

    sum = 0
    matches: list[str] = re.findall(pattern, text)
    for match in matches:
        a, b = list(map(lambda x: int(x), match.split("mul(")[1].split(")")[0].split(",")))
        sum += a*b
    return sum

sum = 0
parts = read().split("don't()")
sum += evaluate(parts[0])
for part in parts[1:]:
    text = ''.join(part.split("do()")[1:])
    sum += evaluate(text)

print(sum)
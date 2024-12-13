from util import read

pattern = r"mul\(\d{1,3},\d{1,3}\)"
import re

sum = 0
matches: list[str] = re.findall(pattern, read())
for match in matches:
    a, b = list(map(lambda x: int(x), match.split("mul(")[1].split(")")[0].split(",")))
    sum += a*b
print(sum)

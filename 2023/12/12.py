from util import read

def minify(chars: str) -> str:
    new_str = ""
    seen_dot = False
    for i in range(len(chars)):
        if chars[i] == "." and len(new_str) > 0:
            seen_dot = True
        elif chars[i] == "#" or chars[i] == "?":
            if seen_dot:
                new_str += "."
            new_str += chars[i]
            seen_dot = False
    return new_str

def isStartValid(chars: str, counts: list[int]) -> bool:
    is_complete = not "?" in chars
    chars = minify(chars.split("?")[0])
    sections = chars.split(".")
    if is_complete and len(sections) != len(counts):
        return False
    for i, section in enumerate(sections):
        if i >= len(counts):
            return False
        if is_complete and len(section) !=  counts[i]:
            return False
        if i < len(sections) - 1 and len(section) != counts[i]:
            return False
        if i == len(sections) - 1 and len(section) > counts[i]:
            return False
    return True

lines = read().split("\n")

def countLine(chars: str, counts: list[int]) -> int:
    count = chars.count("?")
    if count == 0:
        return 0
    sum = 0
    if isStartValid(chars.replace("?", "#", 1), counts):
        if count > 1:
            sum += countLine(chars.replace("?", "#", 1), counts)
        else:
            sum += 1 
    if isStartValid(chars.replace("?", ".", 1), counts):
        if count > 1:
            sum += countLine(chars.replace("?", ".", 1), counts)
        else:
            sum += 1 
    return sum
 
sum = 0
for line in lines:
    chars = minify(line.split(" ")[0])
    counts = list(map(lambda x: int(x), line.split(" ")[1].split(",")))
    sum += countLine(chars, counts)

print(f"result = {sum}")
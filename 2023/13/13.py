from util import read

patterns = read().split("\n\n")

def find_vertical_reflection(pattern: list[str]) -> int | None:
    for i in range(0, len(pattern[0]) - 1):
        left = i
        right = i + 1
        wrong_count = 0
        while left >= 0 and right < len(pattern[0]):
            for j in range(len(pattern)):
                if pattern[j][left] != pattern[j][right]:
                    wrong_count += 1 
                    if wrong_count > 1:
                        break
            if wrong_count > 1:
                break
            left -= 1
            right += 1
        if wrong_count == 1:
            return i + 1
    return None
            
def find_horizontal_reflection(pattern: list[str]) -> int | None:
    for i in range(0, len(pattern) - 1):
        top = i
        bottom = i + 1
        wrong_count = 0
        while top >= 0 and bottom < len(pattern):
            for k in range(len(pattern[0])):
                if pattern[top][k] != pattern[bottom][k]:
                    wrong_count += 1
                    if wrong_count > 1:
                        break
            if wrong_count > 1:
                break
            top -= 1
            bottom += 1
        if wrong_count == 1:
            return i + 1
    return None

sum = 0
for pattern in patterns:
    pattern_lines = pattern.split("\n")
    hor = find_horizontal_reflection(pattern_lines)
    ver = find_vertical_reflection(pattern_lines)
    if hor is not None:
        sum += 100*hor
    if ver is not None:
        sum += ver

print(f"result = {sum}")

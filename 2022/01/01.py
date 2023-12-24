from util import read

elves = read().split("\n\n")
max_cal = 0
for elve in elves:
    nums = list(map(lambda x: int(x), elve.split("\n")))
    calories = sum(nums)
    max_cal = max(max_cal, calories)
print(f"result = {max_cal}")
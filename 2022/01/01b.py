from util import read

elves = read().split("\n\n")
calories: list[int] = []
for elve in elves:
    nums = list(map(lambda x: int(x), elve.split("\n")))
    calories.append(sum(nums))
calories.sort()

print(f"result = {sum(calories[-3:])}")
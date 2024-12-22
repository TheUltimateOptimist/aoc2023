from util import read

numbers = list(map(lambda x: int(x), read().splitlines()))
conversions = (lambda x: x*64, lambda x: x // 32, lambda x: x*2048)
sequences: dict[tuple[int, int, int, int], tuple[int, int]] = dict()

def next_number(number: int) -> int:
    for conversion in conversions:
        value = conversion(number)
        number = value ^ number
        number = number % 16777216
    return number

for k, number in enumerate(numbers):
    queue: list[int] = []
    for i in range(2000):
        next = next_number(number)
        diff = (next % 10) - (number % 10)
        if len(queue) == 4: 
            queue = queue[1:]
        queue.append(diff)
        if len(queue) == 4:
            entry = sequences.get(tuple(queue))
            if entry is None: sequences[tuple(queue)] = (next % 10, k)
            elif entry[1] != k: sequences[tuple(queue)] = (entry[0] + next % 10, k)
        number = next

maxsequence: tuple[int, int, int, int] = (0, 0, 0, 0)
max = 0
for sequence, entry in sequences.items():
    if entry[0] > max:
        max = entry[0]
        maxsequence = sequence

print(maxsequence, max)
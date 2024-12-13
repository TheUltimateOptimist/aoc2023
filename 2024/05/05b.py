from util import read

rulelines = read().strip().split("\n\n")[0].strip().splitlines()
orderlines = read().strip().split("\n\n")[1].strip().splitlines()

rules = []
for ruleline in rulelines:
    a, b = ruleline.split("|")
    rules.append((int(a), int(b)))

orders: list[list[int]] = []
for orderline in orderlines:
    orders.append(list(map(lambda x: int(x), orderline.split(","))))

ruleset = [[0 for _ in range(100)] for __ in range(100)]
for rule in rules:
    ruleset[rule[0]][rule[1]] = 1 

print(ruleset[47][13])

for i in range(100):
    for j in range(100):
        print(ruleset[i][j], end='')
    print("")


def is_valid(order: list[int]) -> bool:
    for a in range(len(order) - 1):
        for b in range(a + 1, len(order)):
            if ruleset[order[b]][order[a]]:
                return False
    return True


from functools import cmp_to_key

def compare(x: int, y: int) -> int:
    if x == y: return 0
    if ruleset[x][y]:
        return 1
    return -1

import time
start = time.time()
sum = 0
for order in orders:
    if not is_valid(order):
        order.sort(key=cmp_to_key(compare))
        sum += order[len(order)//2]
end = time.time()
print((end - start)*1000, end='')
print("ms")
print(sum)
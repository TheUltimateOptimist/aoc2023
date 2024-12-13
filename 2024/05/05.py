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

sum = 0
for order in orders:
    if is_valid(order):
        sum += order[len(order)//2]
print(sum)
    
from util import read
from itertools import combinations

connections = list(map(lambda x: tuple(x.split("-")), read().splitlines()))
mappings: dict[str, list[str]] = {}
for connection in connections:
    first_partners = mappings.get(connection[0])
    second_partners = mappings.get(connection[1])
    if first_partners is None:
        mappings[connection[0]] = [connection[1]]
    else: first_partners.append(connection[1])
    if second_partners is None:
        mappings[connection[1]] = [connection[0]]
    else: second_partners.append(connection[0])

groups: set[tuple[str, ...]] = set()
for computer, connected_computers in mappings.items():
    for partnera, partnerb in combinations(connected_computers, 2):
        if partnerb in mappings[partnera]:
            group = [computer, partnera, partnerb]
            group.sort()
            groups.add(tuple(group))

count = 0
for group in groups:
    for computer in group:
        if computer.startswith("t"):
            count += 1
            break
print(count)
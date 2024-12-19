from util import read

maxlen = 0
blocks = read().split('\n\n')
towels: set[str] = set()
designs: list[str] = []
for towel in blocks[0].strip().split(", "):
    if len(towel) > maxlen:
        maxlen = len(towel)
    towels.add(towel)
for design in blocks[1].strip().splitlines():
    designs.append(design)
    
def representations_count(design: str) -> int:
    count = 0
    starts: dict[int, int] = {0: 1}
    while len(starts.keys()) > 0:
        new_starts: dict[int, int] = dict() 
        for start in starts.keys():
            for i in range(1, maxlen + 1):
                if start + i < len(design) and design[start:start + i] in towels:
                    if start + i in new_starts.keys():
                        new_starts[start + i] += starts[start]
                    else: new_starts[start + i] = starts[start]
                elif start + i == len(design) and design[start:start + i] in towels:
                    count += starts[start]
        starts = new_starts
    return count

print(sum(map(lambda design: representations_count(design), designs)))
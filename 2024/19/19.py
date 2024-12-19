from util import read

# parse input
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
    
def can_be_represented(design: str) -> bool:
    starts: set[int] = set([0]) 
    while len(starts) > 0:
        new_starts:  set[int] = set()
        for start in starts:
            for i in range(1, maxlen + 1):
                if start + i < len(design) and design[start:start + i] in towels:
                    new_starts.add(start + i)
                elif start + i == len(design) and design[start:start + i] in towels:
                    return True
        starts = new_starts
    return False

count = 0
for design in designs:
    if can_be_represented(design):
        count += 1
print(count)
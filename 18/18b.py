from util import read

entries = read().split("\n")
for i in range(len(entries)):
    entries[i] = entries[i].split(" ")

directions: dict[int, tuple[int, int]] = {0: (0, 1), 2: (0, -1), 3: (-1, 0), 1: (1, 0)}

path = [(0, 0)]

outer = 0
current = (0, 0)
for entry in entries:
    direction = directions[int(entry[2][7])]
    count = int(entry[2][2:7], 16)
    outer += count
    current = (current[0] + count*direction[0], current[1] + count*direction[1])
    path.append(current)


# shoelace forumula or gausche trapezformel
a = 0
b = 0
for i in range(len(path) - 1):
    a += path[i][0]*path[i+1][1]
for i in range(1, len(path)):
    b += path[i][0]*path[i-1][1]

# pick's theorem
area = 0.5*abs(a - b)
inner = 1 + area - outer / 2
print(f"result = {round(outer + inner)}")
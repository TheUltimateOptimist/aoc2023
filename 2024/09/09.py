from util import read
from dataclasses import dataclass
from collections import deque

@dataclass(frozen=True)
class File:
    id: int
    size: int

@dataclass(frozen=True)
class Space:
    size: int

line = read().strip()
objects = deque[File | Space](maxlen=len(line))

id = 0
for i, char in enumerate(line):
    if i % 2 == 0:
        objects.append(File(id, int(char)))
        id += 1
    elif char != '0':
        objects.append(Space(int(char)))

print(objects)
sum = 0
pos = 0
try:
    while True:
        object = objects.popleft()
        print(object)
        if isinstance(object, File):
            for i in range(object.size):
                sum += object.id*pos
                pos += 1
        elif isinstance(object, Space):
            other = objects.pop()
            if isinstance(other, Space):
                other = objects.pop()
            assert isinstance(other, File)
            if other.size < object.size:
                objects.appendleft(Space(object.size - other.size))
            if other.size > object.size:
                objects.appendleft(File(other.id, object.size))
                objects.append(File(other.id, other.size - object.size))
            if other.size <= object.size:
                objects.appendleft(other) 
except IndexError as e:
    print(sum)




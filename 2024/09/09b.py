from util import read
from dataclasses import dataclass

import time
start = time.time()

@dataclass(frozen=True)
class File:
    id: int
    pos: int
    size: int

@dataclass(frozen=True)
class Space:
    pos: int
    size: int
    maxsize: int

def printfs(fs: list[Space | File], length: int | None = None):
    if length is None:
        length = fs[-1].pos + fs[-1].size
    output = list(length*'.')
    for entry in fs:
        if isinstance(entry, File):
            for i in range(entry.size):
                output[entry.pos + i] = f'{entry.id}'
    print(''.join(output))

line = read().strip()
fs: list[File | Space] = [] 

id = 0
pos = 0
for i, char in enumerate(line):
    if line[i] == '0': continue
    if i % 2 == 0:
        fs.append(File(id, pos,int(char)))
        id += 1
    else: fs.append(Space(pos ,int(char), int(char)))
    pos += int(char)


jump_list: list[int] = [0 for i in range(10)]

index = len(fs) - 1
previousid: int | None = None
while index >= 0:
    object = fs[index]
    if isinstance(object, File) and (previousid == None or object.id == previousid - 1):
        previousid = object.id
        sindex = jump_list[object.size]
        while sindex < index:
            second = fs[sindex]
            if isinstance(second, Space) and second.size >= object.size:
                fs[index] = File(object.id, second.pos + (second.maxsize - second.size), object.size)
                fs[sindex] = Space(second.pos, second.size - object.size, second.maxsize)
                break
            sindex += 1
        jump_list[object.size] = sindex
    index -= 1

sum = 0
for entry in fs:
    if isinstance(entry, File):
        for i in range(entry.size):
            sum += (entry.pos + i)*entry.id

end = time.time()
print((end - start)*1000)
print(sum)
    

'''
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
                tail.appendleft(File(0, other.size))
                other = objects.pop()
            assert isinstance(other, File)
            if other.size < object.size:
                objects.appendleft(File(0, object.size - other.size))
            if other.size <= object.size:
                objects.appendleft(other) 
            if other.size > object.size:
                tail.appendleft(other)
except IndexError as e:
    while len(tail) > 0:
        element = tail.popleft()
        for i in range(element.size):
            sum += element.id*pos
            pos += 1
    print(sum)
'''
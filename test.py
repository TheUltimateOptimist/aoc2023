from typing import Callable
import time
test = 902384098092384082304098
print(bin(test))

def perf(func: Callable[[], None]):
    start = time.time()
    for _ in range(1000):
        func()
    end = time.time()
    print(f"{(end - start)*1000}ms")

@perf
def first():
    value = test
    while value > 0:
        last = value % 4
        value = value // 4

@perf
def second():
    value = test
    while value > 0:
        last = value & 1
        value = value >> 2
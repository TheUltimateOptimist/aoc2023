from util import read

blocks = read().split('\n\n')
registerlines = blocks[0].splitlines()
a = int(registerlines[0].split(' ')[-1])
b = int(registerlines[1].split(' ')[-1])
c = int(registerlines[2].split(' ')[-1])
p = list(map(lambda x: int(x), blocks[1].split(': ')[-1].split(',')))
print(a, b, c)
print(p)
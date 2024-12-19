from util import read

def run(prog, a, b, c):
    ip= 0
    while ip>=0 and ip<len(prog):
        lit, combo = prog[ip+1], [0,1,2,3,a,b,c,99999][prog[ip+1]]
        match prog[ip]:
            case 0: a = int(a / 2**combo)       # adv
            case 1: b = b ^ lit                 # bxl
            case 2: b = combo % 8               # bst
            case 3: ip = ip if a==0 else lit-2  # jnz
            case 4: b = b ^ c                   # bxc
            case 5: return combo % 8       # out
            case 6: b = int(a / 2**combo)       # bdv
            case 7: c = int(a / 2**combo)       # cdv
        ip+=2
    raise Exception("unreachable")

blocks = read().split('\n\n')
registerlines = blocks[0].splitlines()
p = list(map(lambda x: int(x), blocks[1].split(': ')[-1].split(',')))

values: list[int] = [6]
for i in range(len(p) - 2, -1, -1):
    new_values: list[int] = []
    for val in values:
        for a in range(val*8, (val + 1)*8):
            if run(p, a, 0, 0) == p[i]:
                new_values.append(a)
    values = new_values
print(min(values))

# a = a
# b = 0
# c = 0
# b = a % 8
# b = b ^ 3
# c = int(a / 2**b)
# b = b ^ 5
# a = int(a / 8)
# b = b ^ c
# out = b % 8

# c = int(a / 2**(a % 8 ^ 3))
# out = ((a % 8) ^ 3 ^ 5 ^ int(a / 2**(a % 8 ^ 3))) % 8
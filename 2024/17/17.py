from util import read

def run(prog, a, b, c):
    ip, out = 0, []
    while ip>=0 and ip<len(prog):
        lit, combo = prog[ip+1], [0,1,2,3,a,b,c,99999][prog[ip+1]]
        match prog[ip]:
            case 0: a = int(a / 2**combo)       # adv
            case 1: b = b ^ lit                 # bxl
            case 2: b = combo % 8               # bst
            case 3: ip = ip if a==0 else lit-2  # jnz
            case 4: b = b ^ c                   # bxc
            case 5: out.append(combo % 8)       # out
            case 6: b = int(a / 2**combo)       # bdv
            case 7: c = int(a / 2**combo)       # cdv
        ip+=2
    return out

blocks = read().split('\n\n')
registerlines = blocks[0].splitlines()
a = int(registerlines[0].split(' ')[-1])
b = int(registerlines[1].split(' ')[-1])
c = int(registerlines[2].split(' ')[-1])
p = list(map(lambda x: int(x), blocks[1].split(': ')[-1].split(',')))

print(','.join(map(lambda x: str(x), run(p, a, b, c))))
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
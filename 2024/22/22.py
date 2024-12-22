from util import read

numbers = list(map(lambda x: int(x), read().splitlines()))
conversions = (lambda x: x*64, lambda x: x // 32, lambda x: x*2048)

def next_number(number: int) -> int:
    for conversion in conversions:
        value = conversion(number)
        number = value ^ number
        number = number % 16777216
    return number

sum = 0
for number in numbers:
    for i in range(2000):
        number = next_number(number)
    sum += number
print(sum)
    
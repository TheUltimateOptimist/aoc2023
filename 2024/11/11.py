from util import read

numbers = list(map(lambda x: (int(x), 1), read().strip().split(" ")))

for i in range(75):
    numbers.sort()
    for i in range(1, len(numbers)):
        if numbers[i][0] == numbers[i - 1][0]:
            numbers[i - 1] = (numbers[i][0], numbers[i - 1][1] + numbers[i][1])
            numbers[i] = (0, 0)
    newnumbers = []
    for (number, count) in numbers:
        as_str = str(number)
        if count == 0:
            continue
        elif len(as_str) % 2 == 0:
            firstnumber = int(as_str[:(len(as_str)//2)])
            secondnumber = int(as_str[(len(as_str)//2):])
            newnumbers.append((firstnumber, count))
            newnumbers.append((secondnumber, count))
        elif number == 0:
            newnumbers.append((1, count))
        else:
            newnumbers.append((number*2024, count))
        numbers = newnumbers

sum = 0
for number in numbers:
    sum += number[1]

print(sum)
from util import read

text = read()
for i in range(len(text) - 13):
    chars = ""
    all_distinct = True
    for j in range(14):
        if text[i + j] in chars:
            all_distinct = False
            break
        chars += text[i + j]
    if all_distinct:
        print(f"result = {i + 14}")
        exit(0)
from util import read

text = read()
for i in range(len(text) - 3):
    chars = ""
    all_distinct = True
    for j in range(4):
        if text[i + j] in chars:
            all_distinct = False
            break
        chars += text[i + j]
    if all_distinct:
        print(f"result = {i + 4}")
        exit(0)
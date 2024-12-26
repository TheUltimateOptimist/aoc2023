import hashlib

input = "iwrupvqb"
value = 0
while True:
    value += 1
    in_bytes = f"{input}{value}".encode('utf-8')
    hash = hashlib.md5(in_bytes)
    if hash.hexdigest().startswith('000000'):
        print(value)
        break
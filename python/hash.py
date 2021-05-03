import hashlib

total = 1_000_000_000
i = 0
while i < total:

    if i % 10_000 == 0:
        print(i, end = "\r")

    v = (str(i)).encode()
    h = hashlib.sha256(v).hexdigest()

    for l in range(10, 6, -1):
        for digit in range(0, 10):
            digits = str(digit) * l
            if digits in h:
                print(f"\n{i} -> {h} ({l})")
                break

    i = i + 1

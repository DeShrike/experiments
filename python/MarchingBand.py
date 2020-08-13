# see https://www.youtube.com/watch?v=5GZ5IqxAt30

# 24 peaple = 8
# 6 people = 4

def count_arrangements(people):
    factors = []
    for f in range(people):
        if people % (f + 1) == 0:
            factors.append(f + 1)
    return len(factors)


if __name__ == "__main__":
    for p in range(500000):
        a = count_arrangements(p)
        if a == 64:
            print(f"{p} = {a} arrangements")

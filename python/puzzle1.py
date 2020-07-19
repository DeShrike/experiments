import itertools

def Run():
    n = [str(x) for x in range(10)]
    for x in itertools.product(n, repeat = 3):
        a = int(x[0] + x[1] + x[2])
        b = int(x[2] + x[2] + x[2])
        # print(f"a = {a}   b = {b}")
        if a * 3 == b and a != 0:
             print(x)
             break

if __name__ == "__main__":
    Run()

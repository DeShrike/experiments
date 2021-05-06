import math

C = 2.920050977316

def Next(v):
    return math.floor(v) * ( v - math.floor(v) + 1)

def main():
    val = C
    for i in range(1000):
        print(val, math.floor(val))
        val = Next(val)

if __name__ == "__main__":
    main()


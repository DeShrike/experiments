import time
import math
from timeit import default_timer as timer


BRIGHTRED = u"\u001b[31;1m"
BRIGHTGREEN = u"\u001b[31;2m"
RESET = u"\u001b[0m"

numbers = 1_000_000


def sqrt(c, iterations):

    x = c / 2
    for i in range(iterations):
        x = (x + (c / x)) / 2

    return x


def main():

    for i in range(1, 20):

        print(f"{i} Iterations - ", end = "", flush = True)

        starte = time.time()

        for c in range(1, numbers + 1):
            e = sqrt(c, i)

        ende = time.time()
        ellapsede = ende - starte

        print("Estimate: %s%.5f%s seconds" % (BRIGHTRED, ellapsede, RESET), end = "", flush = True)

        startr = time.time()

        for c in range(1, numbers + 1):
            r = math.sqrt(c)

        endr = time.time()
        ellapsedr = endr - startr

        print(" - Real: %s%.5f%s seconds" % (BRIGHTRED, ellapsedr, RESET))


if __name__ == "__main__":
    main()

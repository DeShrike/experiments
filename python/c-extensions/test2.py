from math import floor, ceil
from math import log, log2
import HelloC

print(HelloC.version())

MAX_ITER = 4000

def mandelbrot(c):
    z = 0
    n = 0
    while abs(z) <= 2 and n < MAX_ITER:
        z = z*z + c
        n += 1

    if n == MAX_ITER:
        return MAX_ITER

    return n + 1 - log(log2(abs(z)))


if __name__ == "__main__":
    num = (-0.7566200055026008 + 0.07014891260475625j)

    p = mandelbrot(num)
    c = HelloC.mandelpixel(num, MAX_ITER)

    print(p)
    print(c)


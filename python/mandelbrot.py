from PIL import Image, ImageDraw
from collections import defaultdict
from math import floor, ceil
from math import log, log2
from math import cos, sin
import time
import HelloC

# pip install pillow

BRIGHTRED = u"\u001b[31;1m"
RESET = u"\u001b[0m"
INVERSE = u"\u001b[5m"

MAX_ITER = 80

def mandelbrot(c):
    # print(c, MAX_ITER)
    z = 0
    n = 0
    while abs(z) <= 2 and n < MAX_ITER:
        z = z*z + c
        n += 1

    if n == MAX_ITER:
        return MAX_ITER

    return n + 1 - log(log2(abs(z)))

def linear_interpolation(color1, color2, t):
    # print(color1, color2, t)
    return color1 * (1 - t) + color2 * t

# Image size (pixels)
WIDTH = 80 * 20
HEIGHT = 60 * 20

# Plot window
RE_START = -2
RE_END = 1
IM_START = -1
IM_END = 1

RE_START = -1.626692418761012107006
RE_END = -1.626692285018467823818
IM_START = -0.023244112148589365033
IM_END = -0.023244011841681152642
MAX_ITER = 5000

def run():
    histogram = defaultdict(lambda: 0)
    values = {}
    for x in range(0, WIDTH):
        print(f"Column {x}/{WIDTH}   ", end = "\r")
        for y in range(0, HEIGHT):
            # print(f"Calculating  ({x},{y})", end = "\r")
            # Convert pixel coordinate to complex number
            rr = RE_START + (x / WIDTH) * (RE_END - RE_START)
            ii = IM_START + (y / HEIGHT) * (IM_END - IM_START)
            c = complex(rr, ii)
            # Compute the number of iterations
            # m = mandelbrot(c)
            m = HelloC.mandelpixel(c, MAX_ITER)
            # print(m)
            values[(x, y)] = m
            if m < MAX_ITER:
                histogram[floor(m)] += 1

    print("Calculating Histogram             ", end = "\r")

    total = sum(histogram.values())
    hues = []
    h = 0
    for i in range(MAX_ITER):
        h += histogram[i] / total
        hues.append(h)
    hues.append(h)

    im = Image.new('HSV', (WIDTH, HEIGHT), (0, 0, 0))
    draw = ImageDraw.Draw(im)

    print("Coloring Pixels                ", end = "\r")

    for x in range(0, WIDTH):
        for y in range(0, HEIGHT):
            m = values[(x, y)]
            # The color depends on the number of iterations
            hue = 255 - int(255 * linear_interpolation(hues[floor(m)], hues[ceil(m)], m % 1))
            saturation = 255
            value = 255 if m < MAX_ITER else 0
            # Plot the point
            draw.point([x, y], (hue, saturation, value))

    print("Saving Image                  ", end = "\r")

    im.convert('RGB').save('mandelbrot.png', 'PNG')

    print("                              ", end = "\r")

if __name__ == "__main__":
    print("%s *** MANDELBROT *** %s" % (INVERSE, RESET))
    start = time.time()
    run()
    end = time.time()
    ellapsed = end - start
    print("Ellapsed: %s%.5f%s seconds" % (BRIGHTRED, ellapsed, RESET))
    pixels = WIDTH * HEIGHT
    pixels_per_second = pixels / ellapsed
    print("%s%.5f%s pixels per seconds" % (BRIGHTRED, pixels_per_second, RESET))


import time
import random
from canvas import Canvas

def SmoothStart2(t):
    return t * t

def SmoothStart3(t):
    return t * t * t

def SmoothStop2(t):
    return 1 - ((1 - t) * (1 - t))

def SmoothStop3(t):
    return 1 - ((1 - t) * (1 - t) * (1 - t))

def Crossfade(a, b, t):
    return (1 - t) * a(t) + t * b(t)

def Mix(a, b, weightB, t):
    return (1 - weightB) * a(t) + weightB * b(t)

def Scale(fa, t):
    return t * fa(t)

def ReverseScale(fa, t):
    return (1 - t) * fa(t)

def Arch2(t):
    return t * (1 - t)

def SmoothStartArch3(t):
    return (t * t) * (1 - t)

def BellCurve6(t):
    return SmoothStop3(t) * SmoothStart3(t)

def NormalizedBezier3(B, C, t):
    s = 1.0 - t
    t2 = t * t
    s2 = s * s
    t3 = t2 * t
    return (3.0 * B * s2 * t) + (3.0 * C * s * t2) + (t3)

def RangeMap(value, inStart, inEnd, outStart, outEnd, tweenFunction):
    out = value - inStart
    out /= (inEnd - inStart)
    out = tweenFunction(out)
    out *= (outEnd - outStart)
    return out + outStart

def main():
    print("Creating")
    width = 500
    height = 500
    canvas = Canvas(width, height)

    co0 = [255, 255, 255]
    co1 = [255, 0, 0]
    co2 = [0, 255, 0]
    co3 = [0, 0, 255]
    co4 = [0, 255, 255]
    co5 = [255, 0, 255]
    co6 = [255, 255, 0]

    print("Drawing")
    for x in range(width):
        y = RangeMap(x, 0, width, height, 0, SmoothStart2)
        canvas.set_pixel(int(x), int(y), co1)

        y = RangeMap(x, 0, width, height, 0, SmoothStart3)
        canvas.set_pixel(int(x), int(y), co2)

        y = RangeMap(x, 0, width, height, 0, SmoothStop2)
        canvas.set_pixel(int(x), int(y), co3)

        y = RangeMap(x, 0, width, height, 0, SmoothStop3)
        canvas.set_pixel(int(x), int(y), co4)

        y = RangeMap(x, 0, width, height, 0, Arch2)
        canvas.set_pixel(int(x), int(y), co5)

        y = RangeMap(x, 0, width, height, 0, SmoothStartArch3)
        canvas.set_pixel(int(x), int(y), co6)

        y = RangeMap(x, 0, width, height, 0, BellCurve6)
        canvas.set_pixel(int(x), int(y), co0)

    print("Saving")
    canvas.save_PNG("tween.png")

if __name__ == "__main__":
    main()

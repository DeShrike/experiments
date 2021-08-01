import time
import board
import neopixel
import signal
import random

# Choose an open pin connected to the Data In of the NeoPixel strip,
# i.e. board.D18
# NeoPixels must be connected to D10, D12, D18 or D21 to work.
pixel_pin = board.D18

# The number of NeoPixels
num_pixels = 26

# The order of the pixel colors - RGB or GRB.
# Some NeoPixels have red and green reversed!
# For RGBW NeoPixels, simply change the ORDER to RGBW or GRBW.
ORDER = neopixel.GRB

pixels = neopixel.NeoPixel(
    pixel_pin, num_pixels, brightness=0.1, auto_write=False, pixel_order=ORDER
)

cancel = False

def sigint_handler(signal, frame):
    global cancel
    print("SIGINT - Wait...")
    cancel = True

def cleanup():
    print("Cleanup")
    pixels.fill((0, 0, 0))
    pixels.show()

class Dot():
    def __init__(self):
        self.pos = 0
        self.dpos = 1
        self.last_pos = 0
        self.r = random.randint(0, 255)
        self.g = random.randint(0, 255)
        self.b = random.randint(0, 255)
        self.dr = random.randint(1, 10)
        self.dg = random.randint(1, 10)
        self.db = random.randint(1, 10)

    def advance(self):
        self.r = (self.r + self.dr) % 255
        self.g = (self.g + self.dg) % 255
        self.b = (self.b + self.db) % 255
        self.last_pos = self.pos
        self.pos += self.dpos
        if self.pos < 0:
            self.pos = 1
            self.dpos *= -1

        if self.pos >= num_pixels:
            self.pos = num_pixels - 2
            self.dpos *= -1

    def current_color(self):
        return (self.r, self.g, self.b)

def main():

    dots = [Dot(), Dot(), Dot(), Dot()]
    dots[0].pos = num_pixels - 1
    dots[0].dpos = -1

    dots[1].pos = num_pixels // 2
    dots[1].dpos = -1

    dots[2].pos = num_pixels // 2
    dots[2].dpos = 1

    while cancel == False:
        for dot in dots:
            pixels[dot.last_pos] = (0, 0, 0)
        pixels.show()

        time.sleep(0.01)

        for dot in dots:
            pixels[dot.pos] = dot.current_color()
        pixels.show()

        for dot in dots:
            dot.advance()

        time.sleep(0.1)

    cleanup()

if __name__ == "__main__":
    signal.signal(signal.SIGINT, sigint_handler)
    print("Press Ctrl-C to stop")
    main()

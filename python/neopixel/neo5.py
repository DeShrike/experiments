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
num_pixels = 13

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
    print("SIGINT")
    cancel = True

def cleanup():
    print("Cleanup")
    pixels.fill((0, 0, 0))
    pixels.show()

def main():
    pos = 0
    dpos = 1
    last_pos = 0
    r = random.randint(0, 255)
    g = random.randint(0, 255)
    b = random.randint(0, 255)
    dr = random.randint(1, 10)
    dg = random.randint(1, 10)
    db = random.randint(1, 10)

    while cancel == False:
        pixels[last_pos] = (0, 0, 0)
        pixels.show()
        time.sleep(0.01)
        pixels[pos] = (r, g, b)
        pixels.show()

        print(f"{pos} = ({r}, {g}, {b})")

        r = (r + dr) % 255
        g = (g + dg) % 255
        b = (b + db) % 255
        last_pos = pos
        pos += dpos
        if pos < 0:
            pos = 1
            dpos *= -1

        if pos >= num_pixels :
            pos = num_pixels - 2
            dpos *= -1

        time.sleep(0.1)

    cleanup()

if __name__ == "__main__":
    signal.signal(signal.SIGINT, sigint_handler)
    main()

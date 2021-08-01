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
num_pixels = 12

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
    template = [(255,0,0), (0,255,0), (0,0,255), (0,255,255), (255,0,255), (255,255,0)]
    pattern = []
    for i in range(num_pixels):
        pattern.append(template[i % len(template)])

    while cancel == False:
        for i in range(num_pixels):
            pixels[i] = pattern[i]
        pixels.show()

        c = pattern.pop(0)
        pattern.append(c)

        time.sleep(0.25)

    cleanup()

if __name__ == "__main__":
    signal.signal(signal.SIGINT, sigint_handler)
    main()

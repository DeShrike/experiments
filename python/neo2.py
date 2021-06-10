from rpi_ws281x import *

LED_COUNT = 18 * 12
LED_PIN = 18

LED_FREQ_HZ = 800_000
LED_DMA = 10
LED_BRIGHTNESS = 125  # 0 - 255
LED_INVERT = False
LED_CHANNEL = 0

help(PixelStrip)

quit()

strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL)
strip.begin()

for x in range(LED_COUNT):
    strip.setPixelColor(x, Color(255, 0, 0))

strip.show()


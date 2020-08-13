import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

# PWM pins: 7,11,12,13,15,16,18,22

GPIO.setup(11, GPIO.OUT)
servo1 = GPIO.PWM(11, 50) # pin number 11, 50hz pulse

# start PWM with 0 (pulse off)

servo1.start(0)
print("Waiting")
time.sleep(2)

print("Rotating 180° in 10 steps)")

# for angle between 0 and 180:
# cycle = 2 + (angle / 18)

duty = 2
# Loop for duty values from 2 to 12 (0 to 180°)
while duty <= 12:
    servo1.ChangeDutyCycle(duty)
    time.sleep(0.3)
    servo1.ChangeDutyCycle(0)
    time.sleep(0.7)
    duty = duty + 1

time.sleep(2)

# turn back 90°
servo1.ChangeDutyCycle(7)
time.sleep(0.3)
servo1.ChangeDutyCycle(0)
time.sleep(1.7)

# turn back to 0°

servo1.ChangeDutyCycle(2)
time.sleep(0.5)
servo1.ChangeDutyCycle(0)

# Clean up
servo1.stop()
GPIO.cleanup()


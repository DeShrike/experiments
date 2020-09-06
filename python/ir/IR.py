import RPi.GPIO as GPIO
from datetime import datetime

DATAPIN = 16

def getBinary():
   num1s = 0
   binary = 1
   command = []
   previousValue = 0
   value = GPIO.input(DATAPIN)
   while value:
      value = GPIO.input(DATAPIN)

   startTime = datetime.now()
   while True:
      if previousValue != value:
         now = datetime.now()
         pulseTime = now - startTime
         startTime = now
         command.append( { previousValue, pulseTime.microseconds } )

      if value:
         num1s += 1
      else:
         num1s = 0

      if num1s > 10000:
         break

      previousValue = value
      value = GPIO.input(DATAPIN)

   for (typ, tme) in command:
      if typ == 1:
         if tme > 1000:
            binary = binary * 10 + 1
         else:
            binary = binary * 10

   if len(str(binary)) > 34:
      binary = int(str(binary)[:34])

   return binary


def main():
   GPIO.setmode(GPIO.BCM)
   GPIO.setup(DATAPIN, GPIO.IN)

   code  = getBinary()
   print(code)

if __name__ == "__main__":
   main()


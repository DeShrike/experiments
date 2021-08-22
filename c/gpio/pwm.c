#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>

// only P1 and P26 work for PWM0 at the same time!
// P23 and P24(?) = PWM1

// (PWM0)  1 = WiringPi, 18 = BCM, 12 = Board
// (PWM0) 26 = WiringPi, 12 = BCM, 32 = Board

// (PWM1) 23 = WiringPi, 13 = BCM, 33 = Board
// (PWM1) 24 = WiringPi, 19 = BCM, 35 = Board (Not on Pi Zero ?)

// #define PWM_PIN  23     // If you use wiringPiSetup
#define PWM_PIN  13     // If you use wiringPiSetupGpio

int main(void)
{
  printf("Raspberry Pi wiringPi PWM test program\n");

  if (wiringPiSetupGpio() == -1)  // setup wih Broadcom numbering
  {
    printf("wiringPiSetupGpio() failed\n");
    exit(1);
  }

  //if (wiringPiSetup() == -1)  // setup with WiringPi numbering
  //{
  //  printf("wiringPiSetup() failed\n");
  //  exit(1);
  //}

  // set pin to PWM
  pinMode(PWM_PIN, PWM_OUTPUT);

  // https://raspberrypi.stackexchange.com/questions/75979/pwm-with-wiringpi-library-and-c-in-order-to-blink-an-led-at-a-given-frequency

  // set the PWM mode to Mark Space
  pwmSetMode(PWM_MODE_MS);

  pwmWrite(PWM_PIN, 0);

  // set the clock divisor to reduce the 19.2 Mhz clock
  // to something slower, 5 Khz.
  // Range of pwmSetClock() is 2 to 4095.
  int hertz = 7000;
  int divider = 19200000 / hertz;
  printf("Hertz: %d | Divider: %d \n", hertz, divider);
  pwmSetClock(divider);  // 19.2 Mhz divided by 3840 is 5 Khz.

  // set the PWM range which is the value for the range counter
  // which is decremented at the modified clock frequency.
  // in this case we are decrementing the range counter 5,000
  // times per second since the clock at 19.2 Mhz is being
  // divided by 3840 to give us 5 Khz.
  pwmSetRange(hertz / 2);  // range is 2500 counts to give us half second.

  delay(100);   // delay a moment to let hardware settings settle.

  {
    int i;
    int list[] = {50, 500, 1024, 2500, -1};

    for (i = 0; list[i] > 0; i++)
    {
      // range for the value written is 0 to 1024.
      pwmWrite(PWM_PIN, list[i]);  // set the Duty Cycle for this range.

      // delay 5 seconds to watch the LED flash due to the PWM hardware.
      printf(" PWM Duty Cycle %d\n", list[i]);
      delay(5000);
    }
  }

  // cleanup the environment. set each pin to low
  // and set the mode to INPUT. These steps make sure
  // the equipment is safe to manipulate and prevents
  // possible short and equipment damage from energized pin.
  pinMode(PWM_PIN, INPUT);
  digitalWrite (PWM_PIN, LOW);

  return 0;
}

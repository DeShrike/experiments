#include <stdio.h>
#include <wiringPi.h>

// git clone git://git.drogon.net/wiringPi
// cd wiringPi
// git pull origin
// ./build

// gcc -lwiringPi
// gcc -lwiringPiDev

/*
For LED:
gpio -g mode 18 output
gpio -g write 18 1
gpio -g write 18 0

For buttons:
gpio -g mode 17 up
gpio -g read 17
0 = pressed : 1 = released

*/

const int pwmPin = 18;  // PWM LED
const int ledPin = 23;  // Regular LED
const int btnPin = 17;  // Active-low button

const int pwnValue = 75;  // to set brightness

int main()
{
   wiringPiSetupGpio();  // setup wih Broadcom numbering
   pinMode(pwmPin, PWM_OUTPUT);
   pinMode(ledPin, OUTPUT);
   pinMode(btnPin, INPUT);

   pullUpDnControl(btnPin, PUD_UP); // Enable pull-up resistor on button

   printf("Blinker is running! Press Ctrl+C to quit. \n");

   while(1)
   {
      if (digitalRead(btnPin))
      {
         pmwWrite(pwmPin, pwmValue);
         digitalWrite(ledPin, LOW);
      }
      else
      {
         pwmWrite(pwmPin, 1024 - pwmValue);
         // blink
         digitalWrite(ledPin, HIGH);
         delay(75);
         digitalWrite(ledPin, LOW);
         delay(75);
      }
   }

   return 0;
}

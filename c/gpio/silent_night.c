// compile and run using (requires root access):
// sudo apt install pigpio

#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// GPIO19 is PWM1
#define BeepPin 13

//FREQUENCIES
#define cL 129
#define cLS 139
#define dL 146
#define dLS 156
#define eL 163
#define fL 173
#define fLS 185
#define gL 194
#define gLS 207
#define aL 219
#define aLS 228
#define bL 232

#define c 261
#define cS 277
#define d 294
#define dS 311
#define e 329
#define f 349
#define fS 370
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466

#define cH 523
#define cHS 554
#define dH 587
#define dHS 622
#define eH 659
#define fH 698
#define fHS 740
#define gH 784
#define gHS 830
#define aH 880
#define aHS 910
#define bH 933

#define delay(x) usleep((x)*1000)

#define _SOFT

// This function generates the square wave that makes the
// piezo speaker sound at a determinated frequency.
void beep(unsigned int note, unsigned int duration)
{
    gpioHardwarePWM(BeepPin, note, 500000);
    usleep(duration*1000);
    gpioHardwarePWM(BeepPin, 0, 0);
    usleep(20*1000);
}

void play()
{
  beep( f, 750 ); // si-
  beep( g, 250 );
  beep( f, 500 ); // lent

  beep( d, 1500 ); // night

  beep( f, 750 ); // ho-
  beep( g, 250 );
  beep( f, 500 ); // ly

  beep( d, 1500 ); // night

  beep( cH, 1000 ); // all
  beep( cH, 500 ); // is

  beep( a, 1500 ); // calm

  beep( aS, 1000 ); // all
  beep( aS, 500 ); // is

  beep( f, 1000 ); // bright
  delay( 500 );

  beep( g, 1000 ); // round
  beep( g, 500 ); // you

  beep( aS, 750 ); // vir-
  beep( a, 250 );
  beep( g, 500 ); // gin

  beep( f, 750 ); // moth-
  beep( g, 250 ); // er
  beep( f, 500 ); // and

  beep( d, 1000 ); // child
  delay( 500 );

  beep( g, 1000 ); // ho-
  beep( g, 500 ); // ly

  beep( aS, 750 ); // in-
  beep( a, 250 ); // fant
  beep( g, 500 ); // so

  beep( f, 750 ); // ten-
  beep( g, 250 ); // der
  beep( f, 500 ); // and

  beep( d, 1500 ); // mild

  beep( cH, 1000 ); // sleep
  beep( cH, 500 ); // in

  beep( dHS, 750 ); // heav-
  beep( cH, 250 ); // en-
  beep( a, 500 ); // ly

  beep( aS, 1500 ); // peace
  beep( dH, 1500 );

  beep( aS, 500 ); // Sleep
  beep( f, 500 );
  beep( d, 500 ); // in

  beep( f, 750 ); // heav-
  beep( dS, 250 ); // en-
  beep( c, 500 ); // ly

  beep( bL, 1500 ); // peace
}

int main(void)
{
  if (gpioCfgClock(5, 1, 0)) return -1;

  if (gpioInitialise() < 0) return -1;

  // Play Silent Night
  play();

  return 0;
}

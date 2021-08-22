DEBUG  = -O3
CC     = gcc
CFLAGS = $(DEBUG) -Wall
LIBS   = -lwiringPi -lpthread
LIBS2  = -lpigpio -lrt -lpthread

all: buttons pwm silent_night

buttons: buttons.o
	$(CC) -o $@ buttons.o $(LIBS)

buttons.o: buttons.c
	$(CC) -c $(CFLAGS) buttons.c

silent_night: silent_night.o
	$(CC) -o $@ silent_night.o $(LIBS2)

silent_night.o: silent_night.c
	$(CC) -c $(CFLAGS) silent_night.c

pwm: pwm.o
	$(CC) -o $@ pwm.o $(LIBS)

pwm.o: pwm.c
	$(CC) -c $(CFLAGS) pwm.c

rmbin:
	rm buttons
	rm pwm
	rm silent_night

clean:
	rm *.o

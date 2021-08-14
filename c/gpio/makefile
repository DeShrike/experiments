DEBUG  = -O3
CC     = gcc
CFLAGS = $(DEBUG) -Wall
LIBS   = -lwiringPi -lpthread

all: buttons pwm

buttons: buttons.o
	$(CC) -o $@ buttons.o $(LIBS)

buttons.o: buttons.c
	$(CC) -c $(CFLAGS) buttons.c

pwm: pwm.o
	$(CC) -o $@ pwm.o $(LIBS)

pwm.o: pwm.c
	$(CC) -c $(CFLAGS) pwm.c

rmbin:
	rm buttons
	rm pwm

clean:
	rm *.o

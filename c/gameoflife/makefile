CC=gcc
AR=ar

all: life

rmbin:
	rm life

###################################00

life: life.o
	$(CC) -o life life.o

life.o: life.c
	$(CC) -c -O3 life.c

###################################00

clean:
	rm *.o

###################################00

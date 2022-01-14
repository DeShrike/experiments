CC=gcc
AR=ar
CFLAGS=-Wall -Wextra -O3

all: png

rmbin:
	rm png

###################################00

png: main.o crc.o
	$(CC) -o png main.o crc.o

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

crc.o: crc.c crc.h
	$(CC) -c crc.c $(CFLAGS)

###################################00

clean:
	rm *.o

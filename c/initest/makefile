CC=gcc
AR=ar

all: initest

rmbin:
	rm initest

initest: initest.o config.o ini.o
	$(CC) -o initest initest.o config.o ini.o

initest.o: initest.c initest.h config.h
	$(CC) -c -Wall -O3 initest.c

config.o: config.c config.h initest.h
	$(CC) -c -Wall -O3 config.c

ini.o: ini.c ini.h
	$(CC) -c -Wall -O3 ini.c

clean:
	rm *.o

CC=gcc
AR=ar

all: yamltest

rmbin:
	rm yamltest

yamltest: yamltest.o
	$(CC) -o yamltest yamltest.o -l yaml

yamltest.o: yamltest.c
	$(CC) -c -Wall -O3 yamltest.c

clean:
	rm *.o

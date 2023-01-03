CC = gcc
CFLAGS = -O3


all: example.so

example.so: example.c
	$(CC) -fPIC -shared  $(CFLAGS)  -o example.so example.c

clean:
	rm *.o

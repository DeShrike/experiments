all: test

test: test.o add.o
	gcc -O3 -o test test.o add.o

test.o: test.c
	gcc -O3 -c test.c

add.o: add.s
	as -o add.o add.s

clean:
	rm *.o test

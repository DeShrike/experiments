all: test1

test1: test1.o
	gcc -o test1 test1.o

test1.o: test1.s
	as -o test1.o test1.s

clean:
	rm *.o

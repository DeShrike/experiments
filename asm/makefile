all: test1 stars

test1: test1.o
	gcc -o test1 test1.o

test1.o: test1.s
	as -o test1.o test1.s

stars: stars.o
	gcc -o stars stars.o

stars.o: stars.s
	as -o stars.o stars.s

clean:
	rm *.o

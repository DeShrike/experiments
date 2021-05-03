all: test1 stars hello primes

debughello:
	as -g -o hello.o hello.s
	ld -o hello hello.o
	gdb hello
#	gdb commands: 
#		list
#		run
#		b 13		add breakpoint
#		delete 13
#		continue
#		info r		show registers
#		disassemble main

hello: hello.o
#	gcc -o hello hello.o -nostdlib -static
	ld -o hello hello.o

hello.o: hello.s
	as -o hello.o hello.s

primes.o: primes.s
	as -o primes.o primes.s

primes: primes.o
	ld -o primes primes.o

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

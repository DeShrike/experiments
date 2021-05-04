all: test compare

test: test.o add.o
	gcc -O3 -o test test.o add.o

test.o: test.c
	gcc -O3 -c test.c

add.o: add.s
	as -o add.o add.s

compare: compare.o sum_arr_asm.o
	gcc -O3 -o compare compare.o sum_arr_asm.o

compare.o: compare.c
	gcc -O3 -c compare.c

sum_arr.o: sum_arr_asm.s
	as -o sum_arr_asm.o sum_arr_asm.s

clean:
	rm *.o test compare

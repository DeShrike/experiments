CC=gcc
AR=ar

all: test

test: test.o libbasic.a
	$(CC) -o test -L . test.o -lbasic

test.o: test.c
	$(CC) -c test.c

libbasic.a: add.o mult.o factorial.o
	$(AR) rs libbasic.a add.o mult.o factorial.o

add.o: add.c
	$(CC) -c add.c

mult.o: mult.c
	$(CC) -c mult.c

factorial.o: factorial.c
	$(CC) -c factorial.c

clean:
	rm *.o

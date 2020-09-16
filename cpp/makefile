CC=c++

all: hello mem

mem: mem.o
	$(CC) -o mem mem.o -lm

mem.o: mem.cpp
	$(CC) -c mem.cpp

hello: hello.o
	$(CC) -o hello hello.o -lm

hello.o: hello.cpp
	$(CC) -c hello.cpp

clean:
	rm *.o

CC=c++

all: hello

hello: hello.o
	$(CC) -o hello hello.o -lm

hello.o: hello.cpp
	$(CC) -c hello.cpp 

clean:
	rm *.o

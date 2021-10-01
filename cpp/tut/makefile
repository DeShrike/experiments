CC=c++

all: tut1 tut2 tut3 tut4 tut5

rmbin:
	rm tut1
	rm tut2
	rm tut3
	rm tut4
	rm tut5

tut1: tut1.o
	$(CC) -o tut1 tut1.o

tut1.o: tut1.cpp tut1.hpp
	$(CC) -c -O3 tut1.cpp

tut2: tut2.o
	$(CC) -o tut2 tut2.o

tut2.o: tut2.cpp tut2.hpp
	$(CC) -c -O3 tut2.cpp

tut3: tut3.o
	$(CC) -o tut3 tut3.o

tut3.o: tut3.cpp tut3.hpp
	$(CC) -c -O3 tut3.cpp

tut4: tut4.o
	$(CC) -o tut4 tut4.o

tut4.o: tut4.cpp tut4.hpp
	$(CC) -c -O3 tut4.cpp

tut5: tut5.o
	$(CC) -o tut5 tut5.o

tut5.o: tut5.cpp tut5.hpp
	$(CC) -c -O3 tut5.cpp

clean:
	rm *.o

CC=c++

all: main

rmbin:
	rm main

main: main.o libTarga.o lightFunctions.o matrixFunctions.o nv_algebra.o objectFunctions.o rayFunctions.o
	$(CC) -o main main.o libTarga.o lightFunctions.o matrixFunctions.o nv_algebra.o objectFunctions.o rayFunctions.o

main.o: main.cpp
	$(CC) -c main.cpp

libTarga.o: libTarga.cpp libTarga.h
	$(CC) -c libTarga.cpp

lightFunctions.o: lightFunctions.cpp lightFunctions.h
	$(CC) -c lightFunctions.cpp

matrixFunctions.o: matrixFunctions.cpp matrixFunctions.h
	$(CC) -c matrixFunctions.cpp

nv_algebra.o: nv_algebra.cpp nv_algebra.h nv_math.h
	$(CC) -c nv_algebra.cpp

objectFunctions.o: objectFunctions.cpp objectFunctions.h
	$(CC) -c objectFunctions.cpp

rayFunctions.o: rayFunctions.cpp rayFunctions.h
	$(CC) -c rayFunctions.cpp

clean:
	rm *.o

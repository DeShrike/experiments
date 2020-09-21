CC=c++

all: main

rmbin:
	rm main

main: main.o camera.o color.o image.o ray.o shape.o vector.o
	$(CC) -o main main.o camera.o color.o image.o ray.o shape.o vector.o -lm

main.o: main.cpp
	$(CC) -c main.cpp

camera.o: camera.cpp camera.hpp
	$(CC) -c camera.cpp

color.o: color.cpp color.hpp
	$(CC) -c color.cpp

image.o: image.cpp image.hpp
	$(CC) -c image.cpp

ray.o: ray.cpp ray.hpp
	$(CC) -c ray.cpp

shape.o: shape.cpp shape.hpp
	$(CC) -c shape.cpp

vector.o: vector.cpp vector.hpp
	$(CC) -c vector.cpp

clean:
	rm *.o

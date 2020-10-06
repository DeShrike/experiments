CC=c++

all: connect4

rmbin:
	rm connect4

connect4: connect4.o player.o ai.o human.o grid.o board.o keyboard.o
	$(CC) -o connect4 connect4.o player.o ai.o human.o grid.o board.o keyboard.o -lm

connect4.o: connect4.cpp ai.hpp player.hpp human.hpp grid.hpp board.hpp
	$(CC) -c connect4.cpp

player.o: player.cpp player.hpp board.hpp
	$(CC) -c player.cpp

ai.o: ai.cpp ai.hpp player.hpp board.hpp
	$(CC) -c ai.cpp

human.o: human.cpp player.hpp board.hpp keyboard.hpp
	$(CC) -c human.cpp

grid.o: grid.cpp grid.hpp
	$(CC) -c grid.cpp

board.o: board.cpp board.hpp grid.hpp
	$(CC) -c board.cpp

keyboard.o: keyboard.cpp keyboard.hpp
	$(CC) -c keyboard.cpp

clean:
	rm *.o

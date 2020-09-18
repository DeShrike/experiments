CC=c++

all: hello mem cardorder fact

rmbin:
	rm hello
	rm cardorder
	rm mem
	rm fact

fact: fact.o factorial.o
	$(CC) -o fact fact.o factorial.o -lm

fact.o: fact.cpp factorial.hpp
	$(CC) -c fact.cpp

cardorder: cardorder.o permutations.o factorial.o
	$(CC) -o cardorder cardorder.o permutations.o factorial.o  -lm

cardorder.o: cardorder.cpp permutations.hpp
	$(CC) -c cardorder.cpp

factorial.o: factorial.cpp factorial.hpp
	$(CC) -c factorial.cpp

permutations.o: permutations.cpp permutations.hpp factorial.hpp
	$(CC) -c permutations.cpp

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

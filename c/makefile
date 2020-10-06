CC=gcc
AR=ar

all: forktest pipetest oserver_host pthread test1 test2 test3 test4 numtest ansitest speedtest filetest testpin branchless doomfire clock plasma bunny lines chartest kbhit

rmbin:
	rm forktest
	rm pipetest
	rm oserver_host
	rm pthread
	rm test1
	rm test2
	rm test3
	rm test4
	rm numtest
	rm ansitest
	rm speedtest
	rm filetest
	rm testpin
	rm branchless
	rm doomfire
	rm clock
	rm plasma
	rm bunny
	rm lines
	rm chartest
	rm kbhit

###################################00

kbhit: kbhit.o
	$(CC) -o kbhit kbhit.o

kbhit.o: kbhit.c
	$(CC) -c kbhit.c

###################################00

chartest: chartest.o
	$(CC) -o chartest chartest.o

chartest.o: chartest.c
	$(CC) -c chartest.c

###################################00

forktest: forktest.o
	$(CC) -o forktest forktest.o

forktest.o: forktest.c
	$(CC) -c forktest.c

###################################00

pipetest: pipetest.o
	$(CC) -o pipetest pipetest.o

pipetest.o: pipetest.c
	$(CC) -c pipetest.c

###################################00

oserver_host: oserver.o oserver_host.o
	$(CC) -o oserver_host oserver_host.o oserver.o

oserver.o: oserver.c oserver.h
	$(CC) -c oserver.c

oserver_host.o: oserver_host.c oserver.h
	$(CC) -c oserver_host.c

###################################00

pthread: pthread.o
	$(CC) -lpthread -o pthread pthread.o

pthread.o: pthread.c
	$(CC) -c pthread.c

###################################00

test4: test4.o
	$(CC) -o test4 test4.o

test4.o: test4.c
	$(CC) -c test4.c

###################################00

test3: test3.o
	$(CC) -o test3 test3.o

test3.o: test3.c
	$(CC) -c -O3 test3.c

###################################00

test2: test2.o
	$(CC) -o test2 test2.o

test2.o: test2.c
	$(CC) -c test2.c

###################################00

test1: test1.o
	$(CC) -o test1 test1.o

test1.o: test1.c
	$(CC) -c test1.c

###################################00

numtest: numtest.o
	$(CC) -o numtest numtest.o

numtest.o: numtest.c
	$(CC) -c numtest.c

###################################00

speedtest: speedtest.o
	$(CC) -o speedtest speedtest.o -lm

speedtest.o: speedtest.c
	$(CC) -c -O3 speedtest.c

###################################00

ansitest: ansitest.o
	$(CC) -o ansitest ansitest.o

ansitest.o: ansitest.c
	$(CC) -c ansitest.c

###################################00

blinker: blinker.o
	$(CC) -o blinker blinker.o -l wiringPi

blinker.o: blinker.c
	$(CC) -c blinker.c

###################################00

filetest: filetest.o
	$(CC) -o filetest filetest.o

filetest.o: filetest.c
	$(CC) -c filetest.c

###################################00

testpin: testpin.o
	$(CC) -o testpin testpin.o

testpin.o: testpin.c
	$(CC) -c testpin.c

###################################00

branchless: branchless.o
	$(CC) -o branchless branchless.o

branchless.o: branchless.c
	$(CC) -c branchless.c

###################################00

doomfire: doomfire.o
	$(CC) -o doomfire doomfire.o -lm

doomfire.o: doomfire.c
	$(CC) -c doomfire.c

###################################00

lines: lines.o
	$(CC) -o lines lines.o -lm

lines.o: lines.c
	$(CC) -c lines.c

###################################00

clock: clock.o
	$(CC) -o clock clock.o -lm

clock.o: clock.c
	$(CC) -c clock.c

###################################00

plasma: plasma.o
	$(CC) -o plasma plasma.o -lm

plasma.o: plasma.c
	$(CC) -c -O3 plasma.c

###################################00

bunny: bunny.o
	$(CC) -o bunny bunny.o

bunny.o: bunny.c
	$(CC) -c bunny.c

###################################00

clean:
	rm *.o

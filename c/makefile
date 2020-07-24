CC=gcc

speedtest: speedtest.c
	$(CC) -o speedtest speedtest.c -lm

ansitest: ansitest.c
	$(CC) -o ansitest ansitest.c

blinker: blinker.c
	$(CC) -o blinker blinker.c -l wiringPi

filetest: filetest.c
	$(CC) filetest.c -o filetest

testpin: testpin.c
	$(CC) testpin.c -o testpin

branchless: branchless.c
	$(CC) branchless.c -o branchless

doomfire: doomfire.c
	$(CC) -o doomfire doomfire.c -lm

clock: clock.c
	$(CC) -o clock clock.c -lm

plasma: plasma.c
	$(CC) -o plasma plasma.c -lm

bunny: bunny.c
	$(CC) -o bunny bunny.c

clean:
	rm *.o

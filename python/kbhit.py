from select import select
import sys


oflags = termios.tcgetattr(fd)[3]
oflags = oflags | termios.ECHO  # turn on
oflags = oflags & ~termios.ECHO  # turn off


for i in range(100_000):
    if i % 1000 == 0:
        print(i, end = " ")
    if select([sys.stdin], (), (), 0)[0]:
        keystroke = sys.stdin.read(1)
        print(" ")
        print(keystroke)
        break

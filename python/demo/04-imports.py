import time
from sys import winver, getwindowsversion
from math import *

def main():
    print(time.asctime())
    print(winver)
    print(getwindowsversion().platform_version)
    print(pi)
    print(tau)

if __name__ == "__main__":
    main()

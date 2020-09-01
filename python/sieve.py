import sys

# Sieve

class recursionlimit:
    def __init__(self, limit):
        self.limit = limit
        self.old_limit = sys.getrecursionlimit()

    def __enter__(self):
        sys.setrecursionlimit(self.limit)

    def __exit__(self, type, value, tb):
        sys.setrecursionlimit(self.old_limit)

def nats(n):
   yield n
   yield from nats(n + 1)

def sieve(s):
   n = next(s)
   yield n
   yield from sieve(i for i in s if i % n != 0)

if __name__ == "__main__":
   with recursionlimit(2000):
      p = sieve(nats(2))
      for i in range(200):
         a = next(p)
         print(a)

   print("ResursionLimit", sys.getrecursionlimit())

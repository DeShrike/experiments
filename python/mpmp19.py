# https://www.youtube.com/watch?v=tBXGIXEV7tI
from primetest import *

primecount = 1_000_000
primes = []

def CalcPrimes():
	primes.append(2)
	current = 3
	while len(primes) < primecount:
		if is_prime(current):
			primes.append(current)
			print(f"Found {len(primes)} primes so far", end = "\r")
		current += 2
	print("")

def Main():
	print(f"Calculating {primecount} primes")
	CalcPrimes()
	print("Do MPMP19")
	total = 0
	for i in range(primecount):
		total += primes[i] * primes[i]
		if total % (i + 1) == 0:
			print("Solution: ", (i + 1))

if __name__ == "__main__":
	Main()

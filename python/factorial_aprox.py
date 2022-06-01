import math
from functools import lru_cache

# N! ~ N**N * e ** (-N) * Sqrt N * sqrt (2 PI)

def approximate(n:int) -> float:
	return (n ** n) * (math.e ** -n) * math.sqrt(n) * math.sqrt(2 * math.pi)

@lru_cache(500)
def factorial(n:int) -> int:
	if n == 1:
		return 1
	return n * factorial(n - 1)

def main(num):
	for n in range(1, num + 1):
		rf = factorial(n)
		af = approximate(n)
		if n <= 10:
			print(f"{n} -> {rf} {af} -> {rf / af}")
		else:
			print(f"{n} -> {rf / af}")


if __name__ == "__main__":
	main(143)

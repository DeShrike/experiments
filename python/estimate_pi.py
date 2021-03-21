from functools import lru_cache
import math
from random import seed
from random import randint

aantal = 1_000_000_000

@lru_cache(maxsize=200000)
def gcd(a:int, b:int) -> int:
	if b > a:
		a, b = b, a

	r = a % b
	if r == 0:
		return b
	return gcd(b, r)

def main():
	total = 0
	coprime_count = 0

	for i in range(aantal):
		a = randint(1, 99999)
		b = randint(1, 99999)
		total += 1
		if gcd(a, b) == 1:
			coprime_count += 1

		if coprime_count == 0:
			continue

		pie = math.sqrt(6 * total / coprime_count)
		if i % 10_000 == 0:
			print(f"{coprime_count} / {total} - Pi = {pie}", end = "\r")

	print("")
	print(f"Pi = {pie}")
	print(gcd.cache_info())

if __name__ == "__main__":
	main()


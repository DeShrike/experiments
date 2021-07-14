import time

prime_count = 10_000

def prime_finder(amount):
	last_print = 0
	primes = [2]
	found = 0
	number = 3
	while found < amount:
		if found > last_print and found % 100 == 0:
			print(f"Found {found} - Last: {primes[-1]}")
			last_print = found

		for x in primes:
			if number % x == 0:
				break
		else:
			primes.append(number)
			found += 1

		number += 2
	return primes

def save_primes(primes):
	print(f"Writing {prime_count} primes")
	with open(f"primes-{prime_count}.txt", "w") as fo:
		last = 0
		for ix, prime in enumerate(primes):
			fo.write(f"{ix + 1}\t{prime}")
			if last + 2 == prime:
				fo.write("\tTWIN")
			fo.write("\n")
			last = prime

def main():
	start = time.time()
	pr = prime_finder(prime_count)
	end = time.time()
	secs = end - start
	mins = secs / 60.0
	print(f"Duration: {secs} seconds / {mins} minutes")
	print(f"Last: {pr[-1]}")

	save_primes(pr)

if __name__ == "__main__":
	main()


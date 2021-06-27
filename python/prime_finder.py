import time

prime_count = 1_000

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


def make_buckets(primes, bucket_size):
	print(f"Making buckets of size {bucket_size}")
	buckets = {}
	for prime in primes:
		b = 0
		while True:
			b += 1
			if b * bucket_size > prime:
				break
		b -= 1
		if b in buckets:
			buckets[b] += 1
		else:
			buckets[b] = 1

	with open(f"buckets-{bucket_size}.txt", "w") as fo:
		for b in buckets:
			van = b * bucket_size
			tot = ((b + 1) * bucket_size) - 1

			# print(f"{b}: {buckets[b]}")
			# print(f"{van}-{tot}: {buckets[b]}")
			fo.write(f"{van}\t{tot}\t{buckets[b]}\n")


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

	make_buckets(pr, 100)
	make_buckets(pr, 1_000)
	make_buckets(pr, 10_000)
	make_buckets(pr, 100_000)

if __name__ == "__main__":
	main()


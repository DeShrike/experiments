from sys import stdout
from math import sqrt
import timeit

class prime_sieve():

	raw_bits = None
	sieve_size = 0

	prime_counts = {
				10: 1,
				100: 25,
				1000: 168,
				10000: 1229,
				100000: 9592,
				1000000: 78498,
				10000000: 1664579,
				100000000: 5761455
		       }

	def __init__(self, limit):
		self.sieve_size = limit
		self.raw_bits = [True] * int((self.sieve_size + 1) / 2)

	def validate_results(self):
		if this.sieve_size in self.prime_counts:
			return self.prime_counts[self.sieve_size] == self.count_primes()

		return False

	def get_bit(self, index):
		if index % 2 == 0:
			return False
		else:
			return self.raw_bits[int(index / 2)]

	def clear_bit(self, index):
		if index % 2 == 0:
			assert("If you're setting even bits, you're sub-optimal for some reason !")
			return False
		else:
			self.raw_bits[int(index / 2)] = False

	def run_sieve(self):
		factor = 3
		q = sqrt(self.sieve_size)

		while factor < q:
			for num in range(factor, self.sieve_size):
				if self.get_bit(num) == True:
					factor = num
					break

			for num in range(factor * 3, self.sieve_size, factor * 2):
				self.clear_bit(num)

			factor += 2

	def count_primes(self):
		return sum(1 for b in self.raw_bits if b)

	def print_results(self, show_results, duration, passes):
		if show_results:
			stdout.write("2, ")

		count = 1
		for num in range(3, self.sieve_size):
			if self.get_bit(num) == True:
				if show_results:
					stdout.write(str(num) + ", ")
				count += 1

		assert(count == self.count_primes())
		stdout.write("\n")
		print(f"Passes: {passes}, Time: {duration}, Avg: {duration/passes}")

def main():
	tStart = timeit.default_timer()
	passes = 0
	while (timeit.default_timer() - tStart < 5):
		print(passes)
		sieve = prime_sieve(1_000_000)
		sieve.run_sieve()
		passes += 1

	tD = timeit.default_timer() - tStart

	sieve.print_results(False, tD, passes)

if __name__ == "__main__":
	main()


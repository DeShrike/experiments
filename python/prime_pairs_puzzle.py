import itertools

# see https://www.youtube.com/watch?v=AXfl_e33Gt4

modes = [
			[2, "Pairs"],
			[3, "Triples"],
			[4, "Quartets"]
		]

primes = []

def is_prime(num: int) -> bool:
	if num <= 3:
		return True
	for i in range(2, num):
		if num % i == 0:
			return False
	return True

def build_primes(num: int):
	global primes
	primes = []
	for i in range(2, num):
		if is_prime(i):
			primes.append(i)
	# print("Primes", num, primes)

def check(numbers, mode) -> bool:
	#print("Trying", numbers)
	take = mode[0]
	# print("X ", len(numbers) - take + 1)
	for i in range(0, len(numbers) - take + 1):
		sum = 0
		# print("XXXXXXXX ", i)
		for s in range(i, i + take):
			# print(f"{numbers[s]} + ", end = "")
			sum = sum + numbers[s]
		# print("")
		if sum not in primes:
			# print(f"{sum} is not prime")
			return False
	return True

def do_test(nums: int, mode):
	build_primes(nums * mode[0])

	numbers = [i for i in range(1, nums + 1)]
	print("start", nums, mode[1])
	count = 0
	last = None
	for perm in itertools.permutations(numbers):
		if check(perm, mode):
			count += 1
			print("Success: ", perm)
			last = perm[:]

	with open("prime_pairs_puzzle.txt", "a") as f:
		f.write(f"{nums}:\t{count} {mode[1]}\t{last}\n")

def main():
	for nums in range(3, 16):
		for mode in modes:
			if nums >= mode[0]:
				do_test(nums, mode)


if __name__ == "__main__":
	main()

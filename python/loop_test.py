import timeit

def with_sum(n = 1_000_000):
	return sum(range(n))

def while_loop(n = 1_000_000):
	i = 0
	s = 0
	while i < n:
		s += i
		i += 1
	return s

def for_loop(n = 1_000_000):
	s = 0
	for i in range(n):
		s += i
	return s

def main():
	for i in range(10):
		print("while loop\t\t", timeit.timeit(while_loop, number = 1))
		print("for loop\t\t", timeit.timeit(for_loop, number = 1))
		print("with sum\t\t", timeit.timeit(with_sum, number = 1))


if __name__ == "__main__":
	main()


import math

numbers = 1_000_000

def sqrt(c, iterations):

	x = c / 2
	for i in range(iterations):
		x = (x + (c / x)) / 2

	return x

def main():

	for i in range(1, 20):

		print(f"{i} Iterations - ", end = "", flush = True)

		diff = 0.0
		maxd = 0.0
		maxn = None

		for c in range(1, numbers + 1):
			e = sqrt(c, i)
			r = math.sqrt(c)

			d = abs(r - e)
			if d > maxd:
				maxd = d
				maxn = c
			diff += d

		print(f"Difference - Max: ({maxn}) {maxd} - Avg: {diff / numbers}")

if __name__ == "__main__":
	main()

import math

iterations = 10

def sqrt(c):

	x = c / 2
	for i in range(iterations):
		x = (x + (c / x)) / 2

	return x

def main():
	while True:
		print("Enter a number: ", end = "")
		c = int(input())
		if c == 0:
			break
		a = sqrt(c)
		r = math.sqrt(c)
		diff = abs(a - r)
		print(f"SQRT({c}) = Estimate = {a}  Math.Sqrt = {r}  - Diff = {diff}")

if __name__ == "__main__":
	main()

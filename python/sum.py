import math

results = []

def calc(lim):
	som = 0
	for n in range(1, lim):
		a = (-1) ** (n + 1)
		b = math.sin(n)
		t = (a * b) / n
		som += t
		if n % 100_000 == 0:
			print(som)
	results.append((lim, som))

calc(1_000)
calc(10_000)
calc(100_000)
calc(1_000_000)
calc(10_000_000)
calc(100_000_000)
calc(1_000_000_000)

for res in results:
	som = res[1]
	lim = res[0]
	print(f"Count: {lim} Som: {som} Error: {abs(0.5 - som)}")

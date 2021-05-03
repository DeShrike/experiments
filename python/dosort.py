import time
import random

start = time.time()
mylist = []

for _ in range(100_000):
	mylist.append(random.randint(0, 100))

mylist.sort()

end = time.time()

print(f"{(end - start) * 1_000}ms")


from primetest import is_prime, is_prime2
import itertools
import random

FILENAME = "shrike_primes.txt"

class unique_element:
    def __init__(self,value,occurrences):
        self.value = value
        self.occurrences = occurrences

def perm_unique(elements):
    eset=set(elements)
    listunique = [unique_element(i,elements.count(i)) for i in eset]
    u=len(elements)
    return perm_unique_helper(listunique,[0]*u,u-1)

def perm_unique_helper(listunique,result_list,d):
    if d < 0:
        yield tuple(result_list)
    else:
        for i in listunique:
            if i.occurrences > 0:
                result_list[d]=i.value
                i.occurrences-=1
                for g in  perm_unique_helper(listunique,result_list,d-1):
                    yield g
                i.occurrences+=1

def find_prime(digits):
	n = ""
	for i in range(digits):
		n += str(random.randint(0, 9))
		num = int(n)
		if num % 2 == 0:
			num += 1
		while is_prime(num) == False:
			num += 2
	return num

#p1 = find_prime(20)
#p2 = find_prime(20)

#print(p1)
#print(p2)

def find_shrike_prime(digit):

	print(f"Testing {digit}")

	digits = []
	for i in range(1, digit + 1):
		digits += [i] * i

	print(digits)

	primes = []
	ix = 0

	for p in perm_unique(digits):
	#for p in itertools.permutations(digits):
		ix += 1
		if ix % 100000 == 0:
			print(f"Testing: {ix}", end = "\r")
		number = int("".join([str(elem) for elem in p]))
		if number % 2 == 0:
			continue
		if number not in primes:
			if is_prime(number):
				primes.append(number)
				# print("Prime !", number)
				return number
	return None

def append_to_file(name, value):
	print(value)
	with open(name, "a") as file:
		file.write(value)
		file.write("\r\n")

if __name__ == "__main__":

	for i in range(1, 10):
		n = find_shrike_prime(i)
		if n is None:
			msg = f"No results for {i}"
		else:
			msg = f"{i} => {n}"
		append_to_file(FILENAME, msg)


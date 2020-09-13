from primetest import is_prime, is_prime2
import itertools
import random

FILENAME = "pandecimal_primes.txt"


def pandecimal_primes():

    digits = [i for i in range(9)]
    for digit_count in range(2, 10):

	    print(digits, "Take", digit_count)

	    for p in itertools.permutations(digits, digit_count):

	        number = int("".join([str(elem) for elem in p]))
	        if number % 2 == 0:
	            continue
	        if is_prime(number):
	            yield number
    
    return None

def append_to_file(name, value):
    with open(name, "a") as file:
        file.write(value)
        file.write("\r\n")

if __name__ == "__main__":

    print("Pandecimal Primes:")
    append_to_file(FILENAME, "Pandecimal Primes:")
    for num in pandecimal_primes():
        print("Prime:", num)
        append_to_file(FILENAME, str(num))


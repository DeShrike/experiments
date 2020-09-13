from primetest import is_prime, is_prime2
import itertools
import random

FILENAME = "primes_a.txt"


def primes_a():

    van = 101
    tot = 999
    primes = []
    for i in range(van, tot, 2):
        if is_prime(i):
            primes.append(i)

    print(f"There are {len(primes)} primes between {van} and {tot}")
    print(primes)

    for a, b in itertools.combinations(primes, 2):
        if is_prime(a) and is_prime(b):
            d = a + b - 1
            if is_prime(d):
                yield a, b
    
    return None

def append_to_file(name, value):
    with open(name, "a") as file:
        file.write(value)
        file.write("\r\n")

if __name__ == "__main__":

    title = "Primes in the form <prime> + <prime> - 1"
    print(title)
    append_to_file(FILENAME, title)
    for num1, num2 in primes_a():
        msg = f"{num1}\t+\t{num2}\t- 1\t{num1 + num2 - 1}"
        print(msg)
        append_to_file(FILENAME, msg)


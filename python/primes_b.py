from primetest import is_prime, is_prime2
import itertools
import random

FILENAME = "primes_b.txt"


def primes_b():

    van = 1
    tot = 9999999
    for i in range(van, tot, 2):
        if i % 9999 == 0:
            print(f"\r{i} = {i / tot * 100:2f} % ", end = "")
        if is_prime(i):
            a = str(i)
            b = "".join(reversed(a))
            c = int(a + b)
            if is_prime(c):
                yield i, c
    
    return None

def append_to_file(name, value):
    with open(name, "a") as file:
        file.write(value)
        file.write("\r\n")

if __name__ == "__main__":

    title = "Primes in the form <abcd...dcba> (palindromes)"
    print(title)
    append_to_file(FILENAME, title)
    for num1, num2 in primes_b():
        msg = f"{num1}\t{num2}"
        print(msg)
        append_to_file(FILENAME, msg)


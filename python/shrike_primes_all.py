from primetest import is_prime, is_prime2
import itertools
import random

FILENAME = "shrike_primes_all.txt"

class unique_element:
    def __init__(self, value, occurrences):
        self.value = value
        self.occurrences = occurrences

def perm_unique(elements):
    eset = set(elements)
    listunique = [unique_element(i, elements.count(i)) for i in eset]
    u = len(elements)
    return perm_unique_helper(listunique, [0] * u, u - 1)

def perm_unique_helper(listunique,result_list,d):
    if d < 0:
        yield tuple(result_list)
    else:
        for i in listunique:
            if i.occurrences > 0:
                result_list[d] = i.value
                i.occurrences -= 1
                for g in  perm_unique_helper(listunique, result_list, d - 1):
                    yield g
                i.occurrences += 1

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

def find_shrike_prime(alphabet):

    print(f"Testing {alphabet}")
    primes = []

    has_odd = False
    digits = []
    for i in reversed(alphabet):
        digits += [i] * i
        if i % 2 == 1:
            has_odd = True

    if has_odd == False:
        return primes
        
    print(digits)

    ix = 0
    lastcount = 0
    for p in perm_unique(digits):
        ix += 1
        if ix % 100000 == 0 or lastcount != len(primes):
            lastcount = len(primes)
            print(f"Testing: {ix}  Found {lastcount}", end = "\r")
        number = int("".join([str(elem) for elem in p]))
        if number % 2 == 0:
            continue
        if number not in primes:
            if is_prime(number):
                primes.append(number)
                # print("Prime !", number)

    return primes

def append_to_file(name, value):
    with open(name, "a") as file:
        file.write(value)

def find_all():
    start = [x for x in range(1,9 + 1)]
    for take in range(1, 9 + 1):
        alphabets = itertools.combinations(start, take)
        for alphabet in alphabets:
            primes_found = find_shrike_prime(alphabet)
            if len(primes_found) == 0:
                msg = f"{alphabet} =>\tNone\n"
                print(msg)
            else:
                primes_found.sort()
                msg = f"{alphabet} =>\t{len(primes_found)}\tprimes\n"
                print("\n", msg, primes_found[0])
                for num in primes_found:
                    msg += f"\t{num}\n"
            append_to_file(FILENAME, msg)


if __name__ == "__main__":

    find_all()

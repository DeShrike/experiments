import random

# Miler-Rabin
# https://www.youtube.com/watch?v=_MscGSN5J6o

witnesses = [2, 3, 5, 7, 10, 11, 13, 23, 31, 73] #, 1662803]

def Test(number: int) -> None:
    n = number - 1
    d = 1
    n //= 2
    while n % 2 == 0:
        d += 1
        n //= 2

    print(f"{number} = 2 ** {d} * {n} + 1")

    # there is something wrong here, I get bad negatives
    for w in witnesses:
        if w <= d + 1:
            continue
        print(f"Witness {w}: ", end = "")
        rest = (w ** n) % number
        print(f"{rest} ", end = "")
        if rest == 1 or rest == number - 1:
            print("MAYBE")
        else:
            print("NOT")
            break

def main():
    while True:
        print("Enter anumber: ", end = "")
        num = input()
        number = int(num)
        if number % 2 == 0:
            break

        print(f"\nTesting if {number} is prime:")
        Test(number)

if __name__ == "__main__":
    main()


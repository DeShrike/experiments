import random
import itertools

def run(n1, n2, n3):
    step_count = 0
    while True:
        step_count += 1
        # print(f"N1: {n1}  N2: {n2}  N3: {n3}")
        m1 = abs(n1 - n2)
        m2 = abs(n2 - n3)
        m3 = abs(n1 - n3)

        n1 = m1
        n2 = m2
        n3 = m3

        if n1 == 0 or n2 == 0 or n3 == 0:
            break
        if step_count > 1000:
            break
    return step_count

def random_run():
    n1 = random.randint(2, 200)
    n2 = random.randint(2, 200)
    n3 = random.randint(2, 200)
    run(n1, n2, n3)

def full_run():
    numbers = [x for x in range(50, 300)]
    largest_count = 0
    largest = None
    aantal = 0
    for x in itertools.product(numbers, repeat = 3):
        aantal += 1
        count = run(x[0], x[1], x[2])
        if aantal % 9999 == 0:
            print(x, count)
        if count > largest_count:
            largest_count = count
            largest = (x[0], x[1], x[2])

    print("Largest")
    print(largest_count, largest)

if __name__ == "__main__":
    random_run()
    full_run()

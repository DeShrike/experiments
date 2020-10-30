import itertools



def main():

    hist = {}
    count = 0
    animals = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    step = 0
    for perm in itertools.permutations(animals, 10):
        step += 1
        if step % 100000 == 0:
            print(f"\r{step}", end = "")
        if perm in hist:
            continue
        hist[perm] = 1
        # hist.append(perm)
        last = -1
        bad = 0
        for p in perm:
           if p == 1 and last == 1:
               bad = 1
               continue
           last = p
        if bad == 0:
            count += 1
            print("")
            print(perm)

    print("")
    print("Count: ", count)

if __name__ == "__main__":
    main()


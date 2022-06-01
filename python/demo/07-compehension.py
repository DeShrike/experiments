def test(a):
    return (a + 1) % 7 == 0

def main():
    squares = [x * x for x in range(10)]
    print(squares)

    twodee = [ [x + y for x in range(5)] for y in range(5) ]
    print(twodee)

    dikt = { f"KEY{x}": x for x in range(10) }
    print(dikt)

    days = ["maandag", "dinsdag", "woensdag", "donderdag", "vrijdag", "zaterdag", "zondag"]
    days_with_r = [day for day in days if "r" in day]
    print(days_with_r)

    print("")
    set1 = set([x for x in range(100) if x * x % 9 == 0])
    print(set1)
    set2 = set([x + 1 for x in range(100) if test(x)])
    print(set2)
    print(set1.intersection(set2))

if __name__ == "__main__":
    main()

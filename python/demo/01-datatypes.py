def main():
    number = 12345
    zweef = 3.141592654
    komplex = 4 + 5j
    zin = "Hello World"
    lijst = ["maandag", "dinsdag", "woensdag", "donderdag", "vrijdag", "zaterdag", "zondag"]
    dikt = { 0: "maandag", 1: "dinsdag", 2: "woensdag", 3: "donderdag", 4: "vrijdag", 5: "zaterdag", 6: "zondag", "other": "Undefined" }
    mytuple = (10, 20, 30)

    lijst[1] = "Dinsdag"
    lijst.append(42)
    
    dikt[1] = "Dinsdag"
    dikt["Lijst"] = mytuple
    dikt[mytuple] = mytuple         # mytuple.__hash__

    print(f"Number: {number}")
    print(f"Number: {number ** 10}")
    print(f"Float: {zweef} {zweef:0.3f}")
    print(f"Complex: {komplex} {komplex * komplex}")
    print(f"String: {zin}")
    print(f"List: {lijst}")
    print(f"List[0]: {lijst[0]}")
    print(f"List[-2]: {lijst[-2]}")
    print(f"List[-2:]: {lijst[-2:]}")
    print(f"List[2:5]: {lijst[2:5]}")
    print(f"Dict: {dikt}")
    print(f"Dict[2]: {dikt[2]}")
    print(f"Tuple: {mytuple}")

    set1 = set()
    for x in range(10):
        set1.add(x * 3)

    set2 = set()
    for x in range(10):
        set2.add(x * 4)

    print("")
    print("intersection:", set1.intersection(set2))
    print("union:", set1.union(set2))
    print("difference:", set1.difference(set2))
    print("difference:", set2.difference(set1))


if __name__ == "__main__":
    main()

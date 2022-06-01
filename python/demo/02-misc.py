def main():
    a = 66
    b = 42

    c = a * b
    d = a ** b
    e = a / b
    f = a // b
    g = a ^ b
    h = a + b

    print("*", c)
    print("**", d)
    print("/", e)
    print("//", f)
    print("^", g)

    if a < b and b < c or d > e:
        pass

    if a < b < c:
        pass

    if g < a > f == h:
        pass

    if f is None:
        pass

    print("")

    z = (123, 987)
    z0, z1 = z
    z0, z1 = z1, z0
    
    print(z0, z1)

if __name__ == "__main__":
    main()

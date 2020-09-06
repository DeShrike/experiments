
def fact(n):
    if n > -1:
        if n == 0:
            return 1
        else:
            return n * fact(n - 1)
    else:
        return None


if __name__ == "__main__":
    tests = [3,4,1,8,12,18,100]
    for t in tests:
       f = fact(t)
       print(f"{t}!= {f}")


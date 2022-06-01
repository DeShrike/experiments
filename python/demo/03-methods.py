def A():
    print("A:")

def B(number):
    print("B:", number)

def C(a, b, c, d = 40):
    print("C:", a, b, c, d)

def D(*args, **kwargs):
    print("D:", "args:", args, "kwargs", kwargs)

def E(a, b):
    print("E:", a, b)

def main():
    A()
    B(10)
    C(10,20,30)
    C(b = 200, a = 100, d = 400, c = 300)
    D(10, 20, 30, x = 10, y = 10)

    e = ("LO", 45)
    E(*e)

if __name__ == "__main__":
    main()

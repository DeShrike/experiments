class Demo():
    def __init__(self, number):
        self.number = number

    def __str__(self):
        return f"Number {self.number}"

    def __repr__(self) -> str:
        return f"Demo({self.number})"

    def __new__(cls, *args, **kwargs):
        print("__new__", cls, *args, **kwargs)
        return super(Demo, cls).__new__(cls)

    def __add__(self, other):
        return Demo(self.number + other.number)

def main():
    a = Demo(42)
    print(a)
    print(str(a))
    print(repr(a))

    print("")

    b = Demo(58)
    print(b)

    c = a + b
    print(c)


if __name__ == "__main__":
    main()

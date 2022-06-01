class Demo:
    def __init__(self, a, b, c, d):
        self.a = a
        self.b = b
        self.c = c
        self.d = d

    @property
    def average(self):
        return ( self.a + self.b + self.c + self.d ) / 4

    @average.setter
    def average(self, x):
        print("Average setter", x)

    def add(self):
        print(__class__.__name__, self.a + self.b + self.c + self.d)

    @classmethod
    def foo(cls):
        print("Foo", cls)

    @staticmethod
    def bar():
        print("Bar")

class Demo2(Demo):
    def add(self):
        print(__class__.__name__, self.a + self.b + self.c + self.d)

class Demo3(Demo):
    def add(self):
        print(__class__.__name__, self.a + self.b + self.c + self.d)

class Demo4(Demo2, Demo3):
    pass


def main():
    a1 = Demo(1, 2, 3, 4)
    a1.add()

    a2 = Demo2(1, 2, 3, 4)
    a2.add()

    a3 = Demo3(1, 2, 3, 4)
    a3.add()

    a4 = Demo4(1, 2, 3, 4)
    a4.add()

    a1.foo()
    a1.bar()

    print("Average:", a1.average)
    a1.average = 10       # Error

if __name__ == "__main__":
    main()

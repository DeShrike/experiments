class Person:
    def __init__(self, name, age):
        self.__name = name
        self.__age = age

    @property
    def Name(self):
        return self.__name

    @Name.setter
    def Name(self, value):
        self.__name = value

    @property
    def Age(self):
        return self.__age

    @Age.setter
    def Age(self, value):
        self.__age = value

    def __repr__(self):
        return f"Person({self.__name}, {self.__age})"

    @staticmethod
    def test():
        print("Hi")

p1 = Person("Make", 20)
print(p1)
p1.Name = "Bob"
print(p1)

Person.test()


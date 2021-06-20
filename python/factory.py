from abc import ABCMeta, abstractstaticmethod

class IPerson(metaclass = ABCMeta):

    @abstractstaticmethod
    def person_method():
        """ Interface Method """

class Student(IPerson):

    def __init__(self, name):
        self.name = name

    def person_method(self):
        print(f"Student {self.name}")

class Teacher(IPerson):

    def __init__(self, name):
        self.name = name

    def person_method(self):
        print(f"Teacher {self.name}")

class PersonFactory():

    @staticmethod
    def create(person_type, name):
        if person_type == "Student":
            return Student(name)
        if person_type == "Teacher":
            return Teacher(name)
        return None



s1 = Student("Bob")
s1.person_method()

t1 = Teacher("Jim")
t1.person_method()

s2 = PersonFactory.create("Student", "John")
s2.person_method()


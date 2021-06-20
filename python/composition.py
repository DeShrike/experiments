from abc import ABCMeta, abstractmethod, abstractstaticmethod

class IDepartment(metaclass = ABCMeta):

    @abstractmethod
    def __init__(self, employees):
        """ implement in child class """
        self.employees = employees

    @abstractstaticmethod
    def print_department():
        """ implement in child class """

class Accounting(IDepartment):

    def __init__(self, employees):
        self.employees = employees

    def print_department(self):
        print(f"Accounting: {self.employees} employees")

class Development(IDepartment):

    def __init__(self, employees):
        self.employees = employees

    def print_department(self):
        print(f"Development: {self.employees} employees")

class ParentDepartment(IDepartment):

    def __init__(self, employees):
        self.employees = employees
        self.base_employees = employees
        self.sub_depts = []

    def add(self, dept):
        self.sub_depts.append(dept)
        self.employees += dept.employees

    def print_department(self):
        print("Parent")
        print(f"Parent Base: {self.base_employees}")
        for dept in self.sub_depts:
            dept.print_department()
        print(f"Total: {self.employees}")


dept1 = Accounting(10)
dept2 = Development(20)

parent = ParentDepartment(5)

parent.add(dept1)
parent.add(dept2)

parent.print_department()


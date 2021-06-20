from abc import ABCMeta, abstractstaticmethod


class IPerson(metaclass = ABCMeta):

    #@abstractstaticmethod
    def get_data():
        """ Implement in child class """

class PersonSingleton(IPerson):

    __instance = None

    @staticmethod
    def current():
        if PersonSingleton.__instance == None:
            PersonSingleton("Bob")
        return PersonSingleton.__instance

    def __init__(self, name):
        if PersonSingleton.__instance != None:
            raise Exeption("Already instanciated")

        self.name = name
        PersonSingleton.__instance = self

    def get_data(self):
        return self.name

p = PersonSingleton("Mike")
print(p.get_data())

p2 = PersonSingleton.current()
print(p2.get_data())

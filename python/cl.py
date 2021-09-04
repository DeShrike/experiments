
def person_init(self, name):
    self.name = name


new_class = type("Person", (), {"__init__": person_init})

print(new_class.__name__)
x = new_class("Jane")
print(x.name)

y = Person("John")
print(y.name)


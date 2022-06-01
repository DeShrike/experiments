import random
import string
from dataclasses import dataclass, field

def generate_id() -> str:
   return "".join(random.choices(string.ascii_uppercase, k=12))

class Person:
   def __init__(self, name: str, address: str):
      self.name = name
      self.address = address

   def __str__(self) -> str:
      return f"{self.name}, {self.address}"

@dataclass(frozen=False)
class Person2:
   name: str
   address: str
   active: bool = True
   #email_addresses: list[str] = field(default_factory=list)
   id: str = field(init=False, default_factory=generate_id)
   _search_string: str = field(init=False, repr=False)

   def __post_init__(self) -> None:
      self._search_string = f"{self.name}{self.address}"

def main() -> None:
   person = Person(name="John", address="Kerkstraat 1")
   print(person)

   person2 = Person2(name="John", address="Kerkstraat 1")
   print(person2)


if __name__ == "__main__":
   main()



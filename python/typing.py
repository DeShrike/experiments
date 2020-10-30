from __future__ import annotations
import shutil

class C:
   def __init__(self, x: int) -> None:
      self.x = x

   def __repr__(self) -> str:
      return f"{type(self).__name__}.make({self.x})"

   @classmethod
   def make(cls, x: int) -> C:
      return cls(x)


def main() -> int:

   width, _ = shutil.get_terminal_size()
   print(" Type Annotations ".center(width, "="))

   print(C.make(42))
   # reveal_type(C.make(666))
   return 0


if __name__ == "__main__":
    exit(main())


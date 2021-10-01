from dataclasses import dataclass, field

@dataclass(order = True)
class Vector2D:

    sort_index: int = field(init = False, repr = False)
    x: float
    y: float = 0.0

    def __post_init__(self):
        self.sort_index = self.x

def main():
    vel = Vector2D(12, 5)
    acc = Vector2D(1.7, 5.9)



    print(vel)
    print(acc)


if __name__ == "__main__":
    main()

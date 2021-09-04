import sys

def main(name):
    print(f"Hello {name}")

if __name__ == "__main__":
    name = sys.argv[1]
    main(name)
    exit(42)


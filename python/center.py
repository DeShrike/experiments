import shutil

def main() -> int:

    width, _ = shutil.get_terminal_size()
    print(" Setup ".center(width, "="))

    return 0


if __name__ == "__main__":
    exit(main())


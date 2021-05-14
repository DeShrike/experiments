from argparse import ArgumentParser

def main():
	ap = ArgumentParser()
	ap.add_argument("name", nargs = "?")
	ap.add_argument("-v", "--verbose", default = False, help = "Increase verbosity")
	ap.add_argument("-n", "--number", type=int, default = 1, help = "A nuber")

	args = ap.parse_args()
	name = (args.name or "World")
	print("Hello, ", name, "!")

if __name__ == "__main__":
	main()


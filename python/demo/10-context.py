def test1():
	with open("10-context.py", "r") as fp:
		while True:
			line = fp.readline()
			if not line:
				break
			print(line)

class DbContext:
	def __init__(self, connectionstring):
		self.connectionstring = connectionstring

	def __enter__(self):
		print("Open DB")
		return self

	def __exit__(self, exc_type, exc_value, exc_tb):
		print("Close DB")

	def foo(self):
		print("SELECT")

def test2():
	with DbContext("connectionstring") as db:
		db.foo()

def main():
	test1()
	test2()


if __name__ == "__main__":
    main()

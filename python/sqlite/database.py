import sqlite3
from book_repository import BookRepository

class Database():

	def __init__(self, filename):
		self.conn = sqlite3.connect(filename)

	def book_repository(self):
		return BookRepository(self.conn)

	def close(self):
		self.conn.close()

if __name__ == "__main__":
	pass

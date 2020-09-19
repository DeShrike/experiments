import sqlite3
from book import Book

class BookRepository():

	def __init__(self, conn):
		self.conn = conn
		self.create_table()

	def create_table(self):
		sql = """
			CREATE TABLE IF NOT EXISTS books (
				id integer PRIMARY KEY,
				title text,
				author text,
				rating integer
			)
		"""
		cursor = self.conn.cursor()
		cursor.execute(sql)
		self.conn.commit()

	def insert_or_update(self, book:Book):
		cursor = self.conn.cursor()
		if book.id == 0:
			sql = """INSERT INTO books (title, author, rating) 
					 VALUES (:title, :author, :rating)"""
			cursor.execute(sql, book.as_dictionary())
		else:
			sql = """UPDATE books 
						SET title = :title, 
							author = :author,
							rating = :rating
				      WHERE id = :id """
			cursor.execute(sql, book.as_dictionary())

		self.conn.commit()

	def select_all(self):
		sql = "SELECT * FROM books"
		cursor = self.conn.cursor()
		cursor.execute(sql)
		row = cursor.fetchone()
		while row is not None:
			b = Book.from_row(row)
			yield b
			row = cursor.fetchone()

		# c.fetchmany(5)
		# c.fetchall()

if __name__ == "__main__":
	pass

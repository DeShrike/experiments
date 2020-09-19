from book import Book
from database import Database

if __name__ == "__main__":
	book1 = Book(0, "Rendez-Vous with Rama", "Arthur C. Clarke", 9)
	book2 = Book(0, "Hyperion", "Dan Simmons", 7)
	book3 = Book(0, "Pushing Ice", "Alastair Reynolds", 8)
	book4 = Book(0, "Severance", "Ma Ling", 8)
	book5 = Book(0, "Rejoice", "Steven Erikson", 6)
	book6 = Book(0, "Never let me go", "Kazuo Ishiguro", 6)
	book7 = Book(0, "Time Travelers Never Die", "Jack McDevitt", 6)
	book8 = Book(0, "Nightfall", "Isaac Asimov", 6)

	books = []
	books.append(book1)
	books.append(book2)
	books.append(book3)
	books.append(book4)
	books.append(book5)
	books.append(book6)
	books.append(book7)
	books.append(book8)

	db = Database("books.db")
	repo = db.book_repository()

	for book in books:
		repo.insert_or_update(book)

	for book in repo.select_all():
		print(book)
		book.rating += 1
		# repo.insert_or_update(book)

	db.close()

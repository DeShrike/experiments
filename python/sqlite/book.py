class Book:

	def __init__(self, id:int, title:str, author:str, rating:int):
		self.id = 0
		self.title = title
		self.author = author
		self.rating = rating

	def __repr__(self):
		return f"Book({self.id}, '{self.title}', '{self.author}', {self.rating})"

	def as_dictionary(self):
		return  {
					"id": self.id,
					"title": self.title, 
					"author": self.author, 
					"rating": self.rating 
				}

	@staticmethod
	def from_row(row):
		b = Book(row[0], row[1], row[2], row[3])
		return b

if __name__ == "__main__":
	pass

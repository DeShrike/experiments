from flask import Flask
import json

app = Flask(__name__)

books = [
	{ "Id": 1, "Title": "Hyperion", "Author": "Dan Simmons" },
	{ "Id": 2, "Title": "Klara and the sun", "Author": "Kazuo Ishiguro" }
]

@app.route("/api/books")
def get_books():
    return json.dumps(books)

@app.route("/api/book/<id>")
def get_book(id):
    return json.dumps(books[int(id)])

app.run(host='0.0.0.0', port=8080)

from flask import Flask, flash, render_template, request, url_for, redirect, send_from_directory

class BaseModel():
    def __init__(self):
        self.mode = "default"
        #self.mode = "dark"
        #self.mode = "nord"

class HomeModel(BaseModel):
    def __init__(self):
        BaseModel.__init__(self)
        pass

class AboutModel(BaseModel):
    def __init__(self):
        BaseModel.__init__(self)
        pass

class PrivacyModel(BaseModel):
    def __init__(self):
        BaseModel.__init__(self)
        pass

class LoginModel(BaseModel):
    def __init__(self):
        BaseModel.__init__(self)
        self.username = ""
        self.password = ""

class BooksModel(BaseModel):
    def __init__(self):
        BaseModel.__init__(self)
        pass

class TestModel(BaseModel):
    def __init__(self):
        BaseModel.__init__(self)
        self.names = []

app = Flask(__name__)
app.secret_key = "random string"

@app.route("/")
def index():
    model = HomeModel()
    return render_template('index.html', model = model)

@app.route("/login", methods = ["POST", "GET"]) 
def login(): 
    model = LoginModel()

    if request.method == "POST":
        model.username = request.form["username"]
        model.password = request.form["password"]
        if model.username == "admin" and model.password == "admin":
            return redirect(url_for("index"))
        else:
            return render_template("login.html", model = model)
    else:
        return render_template("login.html", model = model)

@app.route("/about")
def about():
    model = AboutModel()
    return render_template("about.html", model = model)

@app.route("/privacy")
def privacy():
    model = PrivacyModel()
    return render_template("privacy.html", model = model)

@app.route("/books")
def books():
    model = BooksModel()
    return render_template("books.html", model = model)

@app.route("/test", methods = ["GET", "POST"])
def test():
    model = TestModel()
    model.names = ["Jan", "Bob", "Piet"]
    if request.method == "GET":
        model.names.append("Jane")
        model.names.append("John")
        model.names.append(url_for("hello_name", name = "Ikke"))
        model.names.append(url_for("test2", id = 42))
        model.names.append(url_for("index"))
        model.names.append(url_for("static", filename = 'hello.js'))

    flash("You were successfully logged in")

    return render_template("test.html", model = model)

@app.route("/js/<path:path>")
def send_js(path):
    return send_from_directory("js", path)

@app.route("/css/<path:path>")
def send_css(path):
    return send_from_directory("css", path)

@app.route("/img/<path:path>")
def send_img(path):
    return send_from_directory("img", path)

@app.route("/api/books")
def api_books():
    books = []
    return render_template("books.json", model = books), 201, {"Content-Type" : "application/json"}

@app.route("/hello/<name>")
def hello_name(name):
    return "Hello {}!".format(name)

@app.route("/test2/<int:id>")
def test2(id):
    return "Hello {}!".format(id)

if __name__ == "__main__":
    host = "0.0.0.0"
    port = 8080
    debug = True
    options = None
    app.run(host, port, debug, options)


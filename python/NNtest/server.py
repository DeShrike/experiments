from flask import Flask, flash, render_template, request, url_for, redirect

app = Flask(__name__)
app.secret_key = 'random string'

@app.route('/', methods=['GET', 'POST'])
def index():
    names = ["Jan", "Bob", "Piet"]
    if request.method == "POST":
        names.append("Jane")
        names.append("John")

    names.append(url_for("hello_name", name = "Ikke"))
    names.append(url_for("test2", id = 42))
    names.append(url_for("index"))
    names.append(url_for('static', filename = 'hello.js'))


    flash('You were successfully logged in')

    return render_template('./default.html', names = names)

@app.route('/login',methods = ['POST', 'GET']) 
def login(): 
    if request.method == 'POST' and request.form['username'] == 'admin' :
        return redirect(url_for('success'))
    else:
        return redirect(url_for('index'))

@app.route('/success')
def success():
    return "Hello !"

@app.route('/<name>')
def hello_name(name):
    return "Hello {}!".format(name)

@app.route('/test2/<int:id>')
def test2(id):
    return "Hello {}!".format(name)


if __name__ == '__main__':
    host = "0.0.0.0"
    port = 8080
    debug = False
    options = None
    app.run(host, port, debug, options)


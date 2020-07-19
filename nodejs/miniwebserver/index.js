var connect = require('connect');
var http = require('http');
var app = connect();

var compression = require('compression')
app.use(compression())

var folder  = "/var/www/httpdocs"

var static = require('serve-static');
// app.use(static(__dirname + "/httpdocs"));
app.use(static(folder));

var port = process.env.PORT ||8181;

console.log("Serving from " + folder);
console.log("Listening on port " + port);

http.createServer(app).listen(port);


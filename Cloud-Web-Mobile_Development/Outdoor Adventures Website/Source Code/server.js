/*
 * Write your routing code in this file.  Make sure to add your name and
 * @oregonstate.edu email address below.
 *
 * Name: Brayden Tremper
 * Email: tremperb@oregonstate.edu
 */

var path = require('path');
var express = require('express');
var exphbs = require('express-handlebars'); //so handlebars works
var app = express();
app.set('port', process.argv[2]);

/////
var mysql = require('./dbcon.js');
var bodyParser = require('body-parser');
//var pool = mysql.createPool(require('./dbcon.js'));

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
////

app.engine('handlebars', exphbs({ defaultLayout: 'main' }));
app.set('view engine', 'handlebars');
app.use(express.static('public'));
app.set('mysql', mysql);

/////////////////////
var express = require('express');
var mysql = require('./dbcon.js');
var bodyParser = require('body-parser');

//////////////////////

//No need to edit this one
app.get('/', function (req, res, next) {
  res.status(200).render('mainPage');
});

app.use('/bookTrip', require('./bookTrip.js'));
app.use('/participants', require('./participants.js'));
app.use('/tripInfo', require('./tripInfo.js'));
app.use('/admin', require('./admin.js'));



app.get('*', function (req, res) {
  res.status(404).render('error404');
});

app.listen(app.get('port'), function () {
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});

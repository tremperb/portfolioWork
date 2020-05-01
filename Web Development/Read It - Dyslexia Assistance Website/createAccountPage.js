module.exports = function(){

    var express = require('express');
    var router = express.Router();


    router.post('/', function(req, res){

      var context = {};
      var mysql = req.app.get('mysql');

      /*
      You Can implement the create account here
      */
      var sql = "INSERT INTO userLogin (userName, userPassword) VALUES (?, ?)";
      var inserts = [req.body.usernameInput,  req.body.passwordInput];
      sql = mysql.pool.query(sql, inserts, function(err, result, fields) {
        if(err) {
          res.write(JSON.stringify(err));
          res.end();
        }else {
          console.log("in2");
                sql = mysql.pool.query("SELECT userID FROM userLogin ORDER BY userID DESC LIMIT 1", function(err, result, fields){
                    if(err){
                        console.log(err);
                        res.write(JSON.stringify(err));
                        res.end();
                    }else {
                      newUserId = result[0].userID;
                      console.log("here-->", newUserId);
                      sql = "INSERT INTO userMenu (userID, highlightOne, highlightTwo, highlightThree, blockOne, blockTwo, blockThree, newFont) VALUES(?, ?, ?, ?, ?, ?, ?, ?)";
                      inserts = [newUserId, "red", "blue", "green", "black", "yellow", "green", "Open Dyslexic"];
                      console.log("inserts:", inserts);
                      sql = mysql.pool.query(sql, inserts, function(err, result, fields) {
                          if(err) {
                            res.write(JSON.stringify(err));
                            res.end();
                          }else {
                            res.redirect('/');
                          }

                      });

                    }
                });
        }
      })

    });

    router.get('/', function(req, res){
      var context = {};
      var count = 0;
      //context.jsscripts = ["filterAdmin.js"];
      var mysql = req.app.get('mysql');
      res.status(200).render('createAccount', context);

    });






  return router;
}();

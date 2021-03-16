module.exports = function(){

    var express = require('express');
    var router = express.Router();

    function getCurrentMenu(req, res, mysql, context, done) {
      var id = [req.params.id];

        mysql.pool.query("SELECT * FROM userMenu WHERE userID=" + id, function(err, result, fields){
            if(err){
                console.log(err);
                res.write(JSON.stringify(err));
                res.end();
            }

            context.menuItem = result;

            done();
        });
    }


    router.get('/', function(req, res){
      var context = {};
      var count = 0;
      //context.jsscripts = ["filterAdmin.js"];
      var mysql = req.app.get('mysql');
      res.status(200).render('error404', context);

    });

    router.get('/:id', function(req, res){
      var context = {};
      var count = 0;
      //context.jsscripts = ["filterAdmin.js"];
      var mysql = req.app.get('mysql');
      context.userID = req.params.id;


      getCurrentMenu(req, res, mysql, context, done);

      function done(){
        res.status(200).render('menu', context);
      }

    });

    router.put('/:id', function(req, res) {
      var mysql = req.app.get('mysql');
      var sql = "UPDATE userMenu SET highlightOne=?, highlightTwo=?, highlightThree=?, blockOne=?, blockTwo=?, blockThree=?, newFont=? WHERE userID=?";
      var inserts = [req.body.h1Input, req.body.h2Input, req.body.h3Input, req.body.b1Input, req.body.b2Input, req.body.b3Input, req.body.fontInput, req.params.id];
      sql = mysql.pool.query(sql, inserts, function(err, results, fields) {
        if(err) {
          console.log(err)
          res.write(JSON.stringify(err));
          res.end();
        }else{
          res.status(200);
          res.end();
        }
      });
    });






  return router;
}();

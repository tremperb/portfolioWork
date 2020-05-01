module.exports = function(){

    var express = require('express');
    var router = express.Router();


    function getMenuSettings(req, res, mysql, context, done){
      var id = [req.params.id];
        mysql.pool.query("SELECT * FROM userMenu WHERE userID="+id , function(err, result, fields){
            if(err){
                console.log(err);
                res.write(JSON.stringify(err));
                res.end();
            }
            context.MenuInfo = result;

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


    router.post('/:id', function(req, res) {
      var context = {};
      context.userID = req.params.id;
      context.inputText = req.body.message;
      console.log("Here: ", req.body.message);
      var mysql = req.app.get('mysql');

      getMenuSettings(req, res, mysql, context, done);
      function done(){
        var settings = context.MenuInfo[0];
        console.log(settings.highlightOne);
        //res.redirect('/menu/'+req.params.id);
        res.status(200).render('output', context);

      }
    })

    router.get('/:id', function(req, res){
      var context = {};
      var count = 0;
      //context.jsscripts = ["filterAdmin.js"];
      var mysql = req.app.get('mysql');
      context.userID = req.params.id;
      res.status(200).render('mainPage', context);

    });






  return router;
}();

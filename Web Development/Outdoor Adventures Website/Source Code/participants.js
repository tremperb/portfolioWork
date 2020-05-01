module.exports = function(){

    var express = require('express');
    var router = express.Router();

    function getParticipants(res, mysql, context, done){
        mysql.pool.query("SELECT tripID, participant.participantID, firstName, lastName FROM participantInTrip INNER JOIN participant ON participant.participantID = participantInTrip.participantID", function(err, result, fields){
            if(err){
                console.log(err);
                res.write(JSON.stringify(err));
                res.end();
            }

            context.participants = result;

            done();
        });
    }

    function filterParticipants(req, res, mysql, context, done) {
      var id = [req.params.id];
      mysql.pool.query("SELECT tripID, participant.participantID, firstName, lastName FROM participantInTrip INNER JOIN participant ON participant.participantID = participantInTrip.participantID WHERE tripID="+id, function(err, result, fields){
          if(err){
              console.log(err);
              res.write(JSON.stringify(err));
              res.end();
          }

          context.participants = result;

          done();
      });
    }

    router.get('/', function(req, res){
        var context = {};

        var mysql = req.app.get('mysql');

        getParticipants(res, mysql, context, done);

        function done(){
          res.status(200).render('participants', context);
        }


    });


    router.get('/filter/:id', function(req, res){
        var context = {};
        var count = 0;
        context.jsscripts = ["filterParticipants.js"];
        var mysql = req.app.get('mysql');
        context.tid = [req.params.id];

        filterParticipants(req, res, mysql, context, done)
        function done(){
          count++;
          if(count >= 1) {
            res.status(200).render('filter-participants', context);
          }
        }


    });

    router.delete('/delete/tid/:tid/pid/:pid', function(req, res){
        var mysql = req.app.get('mysql');
        var sql = "DELETE FROM participantInTrip WHERE tripID = ? AND participantID = ?";
        var inserts = [req.params.tid, req.params.pid];
        console.log("tripID", req.params.tid);
        console.log("participantID", req.params.pid);
        sql = mysql.pool.query(sql, inserts, function(err, result, fields){
            if(err){
                console.log(err)
                res.write(JSON.stringify(err));
                res.status(400);
                res.end();
            }else{
                sql = "DELETE FROM packingList WHERE tripID=? AND participantID = ?";
                sql = mysql.pool.query(sql, inserts, function(err, result, fields) {
                  if(err){
                    console.log(err)
                    res.write(JSON.stringify(err));
                    res.status(400);
                    res.end();
                  }else{
                    res.status(202).end();
                  }
                });
            }
        });
    });

    return router;
}();

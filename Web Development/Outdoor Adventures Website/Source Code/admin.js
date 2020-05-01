module.exports = function(){

    var express = require('express');
    var router = express.Router();

    function getSelectedTripInfo(req, res, mysql, context, done){
      var id = [req.params.id];

        mysql.pool.query("SELECT tripType, distanceTraveled, experienceLevel, tripLength FROM trip WHERE tripID=" + id, function(err, result, fields){
            if(err){
                console.log(err);
                res.write(JSON.stringify(err));
                res.end();
            }

            context.selectedTripInfo = result;

            done();
        });
    }

    function getSelectedTripLocation(req, res, mysql, context, done){
      var id = [req.params.id];
      console.log(req.params);
        mysql.pool.query("SELECT destination, maxAltitude, anticipatedAvgTemperature, anticipatedSkyCondition FROM location WHERE tripID=" + id, function(err, result, fields){
            if(err){
                console.log(err);
                res.write(JSON.stringify(err));
                res.end();
            }

            context.selectedTripLocation = result;

            done();
        });
    }


    router.post('/', function(req, res) {
      var mysql = req.app.get('mysql');
      console.log("in1");
      var newTripId;
      var sql = "INSERT INTO trip (tripType, distanceTraveled, experienceLevel, tripLength) VALUES(?, ?, ?, ?)";
      var inserts = [req.body.tripTypeInput, req.body.distanceInput, req.body.levelInput, req.body.tripLengthInput];
      sql = mysql.pool.query(sql, inserts, function(err, result, fields){
              if(err){
                  res.write(JSON.stringify(err));
                  res.end();
              }else{
                console.log("in2");

                sql = mysql.pool.query("SELECT tripID FROM trip ORDER BY tripID DESC LIMIT 1", function(err, result, fields){
                    if(err){
                        console.log(err);
                        res.write(JSON.stringify(err));
                        res.end();
                    }else {
                      newTripId = result[0].tripID;
                      console.log("here-->", newTripId);
                      sql = "INSERT INTO location (tripID, destination, maxAltitude, anticipatedAvgTemperature, anticipatedSkyCondition) VALUES(?, ?, ?, ?, ?)";
                      inserts = [newTripId, req.body.destinationInput, req.body.altitudeInput, req.body.temperatureInput, req.body.skyInput];
                      console.log("inserts:", inserts);
                      sql = mysql.pool.query(sql, inserts, function(err, result, fields) {
                          if(err) {
                            res.write(JSON.stringify(err));
                            res.end();
                          }else {
                            res.redirect('/tripInfo');
                          }

                      });

                    }
                });

              }
          });
    });

    router.get('/', function(req, res){
      var context = {};
      var count = 0;
      console.log("getting");
      //context.jsscripts = ["filterAdmin.js"];
      var mysql = req.app.get('mysql');
      res.status(200).render('admin', context);

    });



router.get('/update/:id', function(req, res){
    var context = {};
    var count = 0;
    context.jsscripts = ["filterAdmin.js"];
    var mysql = req.app.get('mysql');
    context.tid = [req.params.id];
    getSelectedTripInfo(req, res, mysql, context, done);
    getSelectedTripLocation(req, res, mysql, context, done);

    function done(){
      count++;
      if(count >= 2) {
        res.status(200).render('update-trip', context);
      }
    }
});

router.put('/update/:id', function(req, res){
        var mysql = req.app.get('mysql');
        console.log("in update",req.body);
        console.log(req.params.id)
        var sql = "UPDATE trip SET tripType=?, distanceTraveled=?, experienceLevel=?, tripLength=? WHERE tripId=?";
        var inserts = [req.body.typeInput, req.body.distanceInput, req.body.experienceInput, req.body.lengthInput, req.params.id];
        sql = mysql.pool.query(sql,inserts,function(err, results, fields){
            if(err){
                console.log(err)
                res.write(JSON.stringify(err));
                res.end();
            }else{
                sql = "UPDATE location SET destination=?, maxAltitude=?, anticipatedAvgTemperature=?, anticipatedSkyCondition=? WHERE tripId=?";
                inserts = [req.body.destinationInput, req.body.altitudeInput, req.body.temperatureInput, req.body.skyInput, req.params.id];
                sql = mysql.pool.query(sql, inserts, function(err, results, fields) {
                  if(err) {
                    console.log(err)
                    res.write(JSON.stringify(err));
                    res.end();
                  } else {
                    res.status(200);
                    res.end();
                  }
                });
            }
        });
    });

  return router;
}();

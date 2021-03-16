module.exports = function(){

    var express = require('express');
    var router = express.Router();


    function getAvailableTrips(res, mysql, context, done){
        mysql.pool.query("SELECT trip.tripID, tripType, location.destination FROM trip INNER JOIN location ON location.tripID = trip.tripID", function(err, result, fields){
            if(err){
                console.log(err);
                res.write(JSON.stringify(err));
                res.end();
            }

            context.tripOption = result;

            done();
        });
    }

    router.post('/', function(req, res) {
      var mysql = req.app.get('mysql');
      console.log("in1");
      var newTripId;
      var sql = "INSERT INTO participant (firstName, lastName, email, age, phone) VALUES(?, ?, ?, ?, ?)";
      var inserts = [req.body.fnameInput, req.body.lnameInput, req.body.emailInput, req.body.ageInput, req.body.phoneInput];
      sql = mysql.pool.query(sql, inserts, function(err, result, fields){
              if(err){
                  res.write(JSON.stringify(err));
                  res.end();
              }else{
                console.log("in2");

                sql = mysql.pool.query("SELECT participantID FROM participant ORDER BY participantID DESC LIMIT 1", function(err, result, fields){
                    if(err){
                        console.log(err);
                        res.write(JSON.stringify(err));
                        res.end();
                    }else {
                      newParticipantId = result[0].participantID;
                      console.log("here-->", newParticipantId);
                      sql = "INSERT INTO participantInTrip (tripID, participantID) VALUES(?, ?)";
                      inserts = [req.body.tripInput, newParticipantId];
                      console.log("inserts:", inserts);
                      sql = mysql.pool.query(sql, inserts, function(err, result, fields) {
                          if(err) {
                            res.write(JSON.stringify(err));
                            res.end();
                          }else {
                            if(req.body.checkedInput) {
                              sql = "INSERT INTO packingList (participantID, tripID, tripEquipment, clothing, waterAmount, foodMealsAmount) VALUES(?, ?, ?, ?, ?, ?)";
                              inserts = [newParticipantId, req.body.tripInput, req.body.equipmentInput, req.body.clothingInput, req.body.waterInput, req.body.mealsInput];
                              sql = mysql.pool.query(sql, inserts, function(err, result, fields) {
                                if(err) {
                                  res.write(JSON.stringify(err));
                                  res.end();
                                } else{
                                  res.redirect('/participants/filter/' + req.body.tripInput);
                                }
                              });
                            } else {
                              res.redirect('/participants/filter/'+req.body.tripInput);
                            }
                          }

                      });

                    }
                });

              }
          });
    });

    router.get('/', function(req, res){

      var context = {};

      var mysql = req.app.get('mysql');

      getAvailableTrips(res, mysql, context, done);

      function done(){
        res.status(200).render('bookTrip', context);
      }


    });


    return router;
}();

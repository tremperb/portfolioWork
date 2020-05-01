module.exports = function(){

    var express = require('express');
    var router = express.Router();

    function getTrips(res, mysql, context, done){
        mysql.pool.query("SELECT tripID, tripType, distanceTraveled, experienceLevel, tripLength FROM trip", function(err, result, fields){
            if(err){
                console.log(err);
                res.write(JSON.stringify(err));
                res.end();
            }

            context.trip = result;

            done();
        });
    }

    function getLocation(res, mysql, context, done){
        mysql.pool.query("SELECT destID, tripID, destination, maxAltitude, anticipatedAvgTemperature, anticipatedSkyCondition FROM location", function(err, result, fields){
            if(err){
                console.log(err);
                res.write(JSON.stringify(err));
                res.end();
            }

            context.location = result;

            done();
        });
    }

    function getPackingList(res, mysql, context, done){
        mysql.pool.query("SELECT listID, participantID, tripID, tripEquipment, clothing, waterAmount, foodMealsAmount FROM packingList", function(err, result, fields){
            if(err){
                console.log(err);
                res.write(JSON.stringify(err));
                res.end();
            }

            context.packingLists = result;

            done();
        });
    }

    router.get('/', function(req, res){

        var callbackCount = 0;
        var context = {};

        var mysql = req.app.get('mysql');

        getTrips(res, mysql, context, done);
        getLocation(res, mysql, context, done);
        getPackingList(res, mysql, context, done);

        function done(){
            callbackCount++;
            if(callbackCount >= 3){
                res.status(200).render('tripInfo', context);
            }
        }


    });


    return router;
}();

-- Author: Brayden Tremper & Jasmine Snyder
-- Project Group: 24
-- Date: 3/17/2020
-- Data Maniupulation Queries


--
-- Book A Trip Page
--

-- Display Available Trips
SELECT trip.tripID, tripType, location.destination FROM trip INNER JOIN location ON location.tripID = trip.tripID

-- Create a new participant
INSERT INTO participant (firstName, lastName, email, age, phone) VALUES(?, ?, ?, ?, ?)

-- Get that participants ID
SELECT participantID FROM participant ORDER BY participantID DESC LIMIT 1

-- Insert That participant into the trip
INSERT INTO participantInTrip (tripID, participantID) VALUES(?, ?)

-- If desired create packingList
INSERT INTO packingList (participantID, tripID, tripEquipment, clothing, waterAmount, foodMealsAmount) VALUES(?, ?, ?, ?, ?, ?)

--
-- Trip Info Page
--

-- Get tripInfo from trip table
SELECT tripID, tripType, distanceTraveled, experienceLevel, tripLength FROM trip

-- Get tripInfo from location table
SELECT destID, tripID, destination, maxAltitude, anticipatedAvgTemperature, anticipatedSkyCondition FROM location

-- Get tripInfo from packingList table if applicable
SELECT listID, participantID, tripID, tripEquipment, clothing, waterAmount, foodMealsAmount FROM packingList

--
-- Participants Page
--

-- Get all Participants with their corresponding tripID
SELECT tripID, participant.participantID, firstName, lastName FROM participantInTrip INNER JOIN participant ON participant.participantID = participantInTrip.participantID

-- Get participants by filtering tripID
SELECT tripID, participant.participantID, firstName, lastName FROM participantInTrip INNER JOIN participant ON participant.participantID = participantInTrip.participantID WHERE tripID=?

-- Delete the participant in the corresponding trip
DELETE FROM participantInTrip WHERE tripID = ? AND participantID = ?

--
-- Admin Page
--

-- Create a new trip
INSERT INTO trip (tripType, distanceTraveled, experienceLevel, tripLength) VALUES(?, ?, ?, ?)

-- Get the newly created trips id
SELECT tripID FROM trip ORDER BY tripID DESC LIMIT 1

-- Insert the location information based on the selected id
INSERT INTO location (tripID, destination, maxAltitude, anticipatedAvgTemperature, anticipatedSkyCondition) VALUES(?, ?, ?, ?, ?)

--
-- Updating a Trip
--

-- Get current tripInfo
SELECT tripType, distanceTraveled, experienceLevel, tripLength FROM trip WHERE tripID=?

-- Get current tripLocation
SELECT destination, maxAltitude, anticipatedAvgTemperature, anticipatedSkyCondition FROM location WHERE tripID=?

-- Update General Trip if applicable
UPDATE trip SET tripType=?, distanceTraveled=?, experienceLevel=?, tripLength=? WHERE tripId=?

-- Update that trips location if applicable
UPDATE location SET destination=?, maxAltitude=?, anticipatedAvgTemperature=?, anticipatedSkyCondition=? WHERE tripId=?

-- Author: Brayden Tremper & Jasmine Snyder
-- Project Group: 24
-- Date: 3/17/2020
-- Data Definition Queries


--
-- Drop tables if they exist taking into account the order of the foreign keys
--

DROP TABLE IF EXISTS packingList;
DROP TABLE IF EXISTS location;
DROP TABLE IF EXISTS participantInTrip;
DROP TABLE IF EXISTS participant;
DROP TABLE IF EXISTS trip;


--
-- Participant
--


CREATE TABLE `participant`(
	`participantID` int(11) AUTO_INCREMENT NOT NULL,
	`firstName` varchar(255) NOT NULL,
	`lastName` varchar(255) NOT NULL,
	`email` varchar(255) NOT NULL,
	`age` int(11) NOT NULL,
	`phone` varchar(255) NOT NULL,
	PRIMARY KEY (`participantID`)
)ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Insert Values

INSERT INTO `participant` (`participantID`, `firstName`, `lastName`, `email`, `age`, `phone`) VALUES
(1, 'George', 'Washington', 'ogPres@gmail.com', 284, '1111111111'),
(2, 'Harry', 'Potter', 'scarDude420@gmail.com', 22, '5413214321'),
(3, 'Luke', 'Skywalker', 'notAJedi@gmail.com', 65, '5036217892');


--
-- Trip
--

CREATE TABLE `trip`(
	`tripID` int(11) AUTO_INCREMENT NOT NULL,
	`tripType` varchar(255) NOT NULL,
	`distanceTraveled` int(11) NOT NULL,
	`experienceLevel` varchar(255) NOT NULL,
	`tripLength` int(11) NOT NULL,
	PRIMARY KEY (`tripID`)
)ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Insert Values

INSERT INTO `trip` (`tripID`, `tripType`, `distanceTraveled`, `experienceLevel`, `tripLength`) VALUES
(1, 'Hiking', 20, 'high', 5),
(2, 'Exploring', 15, 'low', 10),
(3, 'Rafting', 30, 'mid', 1);


--
-- Packing List
--

CREATE TABLE `packingList`(
	`listID` int(11) AUTO_INCREMENT NOT NULL,
	`participantID` int(11) NOT NULL,
	`tripID` int(11),
	`tripEquipment` varchar(255),
	`clothing` varchar(255),
	`waterAmount` int(11),
	`foodMealsAmount` int(11),
	PRIMARY KEY (`listID`),
	FOREIGN KEY (`tripID`) REFERENCES `trip`(`tripID`),
	FOREIGN KEY (`participantID`) REFERENCES `participant`(`participantID`)
)ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Insert Values

INSERT INTO `packingList` (`listID`, `participantID`, `tripID`, `tripEquipment`, `clothing`, `waterAmount`, `foodMealsAmount`) VALUES
(1, 2, 1, 'Hiking Shoes', 'Jacket', 5, 15),
(2, 3, 1, 'Tent', 'Sweats', 10, 30),
(3, 1, 2, 'Life Jacket', 'Swimwear', 2, 3);


--
-- Location
--

CREATE TABLE `location`(
	`destID` int(11) AUTO_INCREMENT NOT NULL,
	`tripID` int(11) NOT NULL,
	`destination` varchar(255) NOT NULL,
	`maxAltitude` int(11) NOT NULL,
	`anticipatedAvgTemperature` int(11) NOT NULL,
	`anticipatedSkyCondition` varchar(255) NOT NULL,
	PRIMARY KEY (`destID`),
	FOREIGN KEY (`tripID`) REFERENCES `trip`(`tripID`)
)ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Insert Values

INSERT INTO `location` (`destID`, `tripID`, `destination`, `maxAltitude`, `anticipatedAvgTemperature`, `anticipatedSkyCondition`) VALUES
(1, 1, 'Alps', 15000, 40, 'Cloudy'),
(2, 2, 'Yellowstone', 8000, 70, 'Sunny'),
(3, 3, 'Grand Canyon', 3000, 90, 'Sunny');


--
-- Joining Table for Trip and Participants
--

CREATE TABLE `participantInTrip` (
	`tripID` int(11) NOT NULL,
	`participantID` int(11) NOT NULL,
	PRIMARY KEY (`tripID`, `participantID`),
	FOREIGN KEY (`tripID`) REFERENCES `trip` (`tripID`),
	FOREIGN KEY (`participantID`) REFERENCES `participant` (`participantID`)
)ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Insert Values

INSERT INTO `participantInTrip` (`tripID`,`participantID`) VALUES
(2,1),
(1,2),
(1,3);

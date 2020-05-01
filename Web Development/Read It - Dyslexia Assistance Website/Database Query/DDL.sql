-- Database Definition/Table Creation

--
-- User Login
--

DROP TABLE IF EXISTS userMenu;
DROP TABLE IF EXISTS userLogin;


CREATE TABLE `userLogin`(
	`userID` int(11) AUTO_INCREMENT NOT NULL,
	`userName` varchar(255) NOT NULL,
	`userPassword` varchar(255) NOT NULL,
	PRIMARY KEY (`userID`)
)ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- 
-- Insert Values
-- 

INSERT INTO `userLogin` (`userID`, `userName`, `userPassword`) VALUES
(1, 'tremperb', '1234_tremp'),
(2, 'swensonh', '1234_swens'),
(3, 'carlsons', '1234_carl'),
(4, 'raos', '1234_shay'),
(5, 'saechaoj', '1234_saech');



--
-- Menu Table
--

CREATE TABLE `userMenu`(
	`menuID` int(11) AUTO_INCREMENT NOT NULL,
	`userID` int(11) NOT NULL,
	`highlightOne` varchar(255) NOT NULL,
	`highlightTwo` varchar(255) NOT NULL,
	`highlightThree` varchar(255) NOT NULL,
	`blockOne` varchar(255) NOT NULL,
	`blockTwo` varchar(255) NOT NULL,
	`blockThree` varchar(255) NOT NULL,
	`newFont` varchar(255) NOT NULL,
	PRIMARY KEY (`menuID`),
	FOREIGN KEY (`userID`) REFERENCES `userLogin`(`userID`)
)ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- 
-- Insert Values
-- 

INSERT INTO `userMenu` (`menuID`, `userID`, `highlightOne`, `highlightTwo`, `highlightThree`, `blockOne`, `blockTwo`, `blockThree`, `newFont`) VALUES
(1, 1, 'Red', 'Blue', 'Green', 'Black', 'Yellow', 'Green', 'Open Dyslexic'),
(2, 2, 'Red', 'Blue', 'Green', 'Black', 'Yellow', 'Green', 'Open Dyslexic'),
(3, 3, 'Red', 'Blue', 'Green', 'Black', 'Yellow', 'Green', 'Open Dyslexic'),
(4, 4, 'Red', 'Blue', 'Green', 'Black', 'Yellow', 'Green', 'Open Dyslexic'),
(5, 5, 'Red', 'Blue', 'Green', 'Black', 'Yellow', 'Green', 'Open Dyslexic');
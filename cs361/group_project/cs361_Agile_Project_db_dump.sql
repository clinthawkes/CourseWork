-- Authors: Alexander Drath, Serena Tay, Clint Hawkes, Alessio Peterson, Branden Holloway, Samantha Guilbeault
-- CS361 Agile Project Group 05
-- Agile Project Database Dump

-- Dumping database structure for heroku
DROP DATABASE IF EXISTS `heroku_7236e234ae5516f`;
CREATE DATABASE IF NOT EXISTS `heroku_7236e234ae5516f`;
USE `heroku_7236e234ae5516f`;


SET FOREIGN_KEY_CHECKS = 0;
DROP TABLE IF EXISTS `users`;
DROP TABLE IF EXISTS `location`;
DROP TABLE IF EXISTS `facts`;
DROP TABLE IF EXISTS `user_visit_location`;

-- Table structure for table `users`
CREATE TABLE `users` (
    `user_id` int(11) NOT NULL AUTO_INCREMENT,
    `username` varchar(255) NOT NULL,
    `password` varchar(255) NOT NULL,
    PRIMARY KEY (`user_id`),
    UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumping data for table `users`
LOCK TABLES `users` WRITE;
INSERT INTO `users` VALUES (1, 'Alex', 'Drath'), (2, 'Serena', 'Tay'), (3, 'Demo', 'Demo');
UNLOCK TABLES;

-- Table structure for table `location`
CREATE TABLE `location` (
    `loc_id` int(11) NOT NULL AUTO_INCREMENT,
    `loc_name` varchar(255) NOT NULL,
    `loc_address` varchar(255) DEFAULT NULL,
    `loc_city` varchar(255) DEFAULT NULL,
    `loc_state` varchar(255) DEFAULT NULL,
    `loc_zip` varchar(255) DEFAULT NULL,
    `loc_country` varchar(255) NOT NULL,
    `loc_latitude` varchar(255) DEFAULT NULL,
    `loc_longitude` varchar(255) DEFAULT NULL,
    PRIMARY KEY (`loc_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumping data for table `location`
LOCK TABLES `location` WRITE;
INSERT INTO `location` VALUES 
    (1, 'White House', 
    '1600 Pennsylvania Ave NW', 
    'Washington', 'DC', 
    '20500', 'USA', 
    '38.8976', '-77.0365'),
    (2, 'Empire State Building', 
    '20 W 34th St', 
    'New York', 'NY', 
    '10001', 'USA', 
    '40.7484', '-73.9857'),
    (3, 'Mt. Everest', 
    NULL, 
    NULL, NULL, 
    NULL, 'Nepal', 
    '27.988', '86.925');
UNLOCK TABLES;

-- Table structure for table `facts`
CREATE TABLE `facts` (
    `fact_id` int(11) NOT NULL AUTO_INCREMENT,
    `loc_id` int(11) NOT NULL,
    `user_id` int(11) NOT NULL,
    `hf_content` varchar(500) DEFAULT NULL,
    CONSTRAINT `facts_fk_loc_id` FOREIGN KEY (`loc_id`) 
    REFERENCES `location` (`loc_id`) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT `facts_fk_user_id` FOREIGN KEY (`user_id`) 
    REFERENCES `users` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE,
    PRIMARY KEY (`fact_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumping data for table `facts`
LOCK TABLES `facts` WRITE;
INSERT INTO `facts` VALUES 
    (1, 1, 1, "There are 132 rooms, 32 bathrooms, and 6 levels to accommodate all the people who live in, work in, and visit the White House."),
    (2, 1, 1, "The White House requires 570 gallons of paint to cover its outside surface."),
    (3, 2, 2, "The Empire State Building took only one year and 45 days to build, or more than seven million man-hours."),
    (4, 3, 3, "Every corpse on Mt. Everest was once a highly motivated person. Stay Lazy, my friends.");
UNLOCK TABLES;

-- Table structure for table `user_visit_location`
CREATE TABLE `user_visit_location` (
    `user_id` int(11) NOT NULL,
    `loc_id` int(11) NOT NULL,
    `visit_date` timestamp NOT NULL,
    PRIMARY KEY (`user_id`, `loc_id`),
    CONSTRAINT `user_visit_loc_uid` FOREIGN KEY (`user_id`) 
    REFERENCES `users` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT `user_visit_loc_lid` FOREIGN KEY (`loc_id`) 
    REFERENCES `location` (`loc_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumping data for table `user_visit_location`
LOCK TABLES `user_visit_location` WRITE;
INSERT INTO `user_visit_location` VALUES 
    (1, 1, '2020-01-01 10:10:10'), 
    (2, 2, '2020-01-01 10:10:10'), 
    (3, 3, '2020-01-01 10:10:10');
UNLOCK TABLES;



-- Table structure for table `fact_photo`
CREATE TABLE `fact_photo` (
    `photo_id` int(11) NOT NULL AUTO_INCREMENT,
    `fact_id` int(11) NOT NULL,
    `loc_id` int(11) NOT NULL,
    `photo_name` VARCHAR(30),
    `photo_file` BLOB NOT NULL,
    PRIMARY KEY (`photo_id`),
    CONSTRAINT `photo_fact_uid` FOREIGN KEY (`fact_id`) 
    REFERENCES `facts` (`fact_id`) ON DELETE CASCADE ON UPDATE CASCADE,
    CONSTRAINT `photo_loc_lid` FOREIGN KEY (`loc_id`) 
    REFERENCES `location` (`loc_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumping data for table `fact_photo`
LOCK TABLES `fact_photo` WRITE;
INSERT INTO `fact_photo` VALUES 
    (1, 1, 1, "White House", LOAD_FILE("../images/whitehouse.jpg")), 
    (2, 2, 2, "Empire State Building", LOAD_FILE("../images/empirestate.jpg")), 
    (3, 3, 3, "Everest", LOAD_FILE("../images/everest.jpg"));
UNLOCK TABLES;

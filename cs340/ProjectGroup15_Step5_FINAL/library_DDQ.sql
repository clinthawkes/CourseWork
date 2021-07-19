-- MySQL dump 10.16  Distrib 10.1.38-MariaDB, for Linux (x86_64)
--
-- ------------------------------------------------------
-- Server version	10.3.13-MariaDB-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `author`
--

DROP TABLE IF EXISTS `author`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `author` (
  `authorID` int(11) NOT NULL AUTO_INCREMENT,
  `firstName` varchar(25) NOT NULL,
  `lastName` varchar(25) NOT NULL,
  `homeCity` varchar(25) DEFAULT NULL,
  `homeState` varchar(25) DEFAULT NULL,
  PRIMARY KEY (`authorID`)
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `author`
--

LOCK TABLES `author` WRITE;
/*!40000 ALTER TABLE `author` DISABLE KEYS */;
INSERT INTO `author` VALUES (1,'Marijn','Haverbeke',NULL,'NJ'),(2,'Elaine','Marieb',NULL,'NY'),(3,'Katja','Hoehn',NULL,'NJ'),(4,'Jane','Doe','Chicago','IL'),(5,'Jane','Doe','Chicago','IL'),(10,'Joe','Stallano','Cleveland','OH'),(13,'Chris','Kuchman','Poulsbo','WA'),(15,'John','Doe','Miami','FL'),(16,'Katja','Hoehn','',''),(17,'Colonel','Sanders','Chicken','KY'),(18,'Princess','Leia','Aldera','Al');
/*!40000 ALTER TABLE `author` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `book`
--

DROP TABLE IF EXISTS `book`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `book` (
  `ISBN` bigint(20) NOT NULL,
  `title` varchar(100) NOT NULL,
  `publisher` int(11) NOT NULL,
  `location` int(11) DEFAULT NULL,
  PRIMARY KEY (`ISBN`),
  KEY `FK_publisher` (`publisher`),
  KEY `FK_facility` (`location`),
  CONSTRAINT `FK_facility` FOREIGN KEY (`location`) REFERENCES `facility` (`facilityID`),
  CONSTRAINT `FK_publisher` FOREIGN KEY (`publisher`) REFERENCES `publisher` (`publisherID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `book`
--

LOCK TABLES `book` WRITE;
/*!40000 ALTER TABLE `book` DISABLE KEYS */;
INSERT INTO `book` VALUES (1234567891,'How to Win Friends Who Eat Cheese for Lunch',2,1),(9708123456,'How Fried Chicken kept me on the Road',1,4),(9780262033848,'Introduction to Algorithms',2,NULL),(9780735619664,'Test Add',2,1),(9780735619678,'Complete Code',3,1),(9781269921091,'Human Anatomy and Physiology',2,2),(9781479274833,'Elements of Programming Interviews',10,2),(9781593279509,'Eloquent JavaScript',1,1);
/*!40000 ALTER TABLE `book` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `book_author`
--

DROP TABLE IF EXISTS `book_author`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `book_author` (
  `creatorID` int(11) NOT NULL AUTO_INCREMENT,
  `bookID` bigint(20) NOT NULL,
  `authorID` int(11) NOT NULL,
  PRIMARY KEY (`creatorID`),
  KEY `FK_author` (`authorID`),
  KEY `FK_book_author` (`bookID`),
  CONSTRAINT `FK_author` FOREIGN KEY (`authorID`) REFERENCES `author` (`authorID`),
  CONSTRAINT `FK_book_author` FOREIGN KEY (`bookID`) REFERENCES `book` (`ISBN`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `book_author`
--

LOCK TABLES `book_author` WRITE;
/*!40000 ALTER TABLE `book_author` DISABLE KEYS */;
INSERT INTO `book_author` VALUES (21,1234567891,10),(22,9708123456,17),(23,1234567891,18);
/*!40000 ALTER TABLE `book_author` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `customer` (
  `customerID` int(11) NOT NULL AUTO_INCREMENT,
  `firstName` varchar(25) NOT NULL,
  `lastName` varchar(25) NOT NULL,
  `streetAddress` varchar(50) NOT NULL,
  `city` varchar(25) NOT NULL,
  `state` varchar(2) NOT NULL DEFAULT 'OR',
  `zip` varchar(5) NOT NULL,
  PRIMARY KEY (`customerID`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (10,'Joe','Stallano','111 road street','Mayfield','OH','44113'),(11,'Clint','Eastwood','501 Booker St.','Culver City','CA','93549'),(14,'Lloyd','Christmas','66 Pretty Bird Dr','Providence','RI','02902');
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `facility`
--

DROP TABLE IF EXISTS `facility`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `facility` (
  `facilityID` int(11) NOT NULL AUTO_INCREMENT,
  `branch` varchar(25) NOT NULL,
  `streetAddress` varchar(100) NOT NULL,
  `city` varchar(25) NOT NULL,
  `state` varchar(2) NOT NULL DEFAULT 'OR',
  `capacity` int(11) DEFAULT NULL CHECK (`capacity` <= 10000000),
  PRIMARY KEY (`facilityID`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `facility`
--

LOCK TABLES `facility` WRITE;
/*!40000 ALTER TABLE `facility` DISABLE KEYS */;
INSERT INTO `facility` VALUES (1,'Portland Main','1200 Broadway St','Portland','OR',22000),(2,'Portland South','12897 Main St','Portland','OR',73000),(3,'Portland North','111 street road','Cleveland','OH',10000),(4,'Outreach','456 Something St','Corvallis','OR',13500),(5,'Death Star','Level 17','Detention Block AA-23','TK',25413);
/*!40000 ALTER TABLE `facility` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `loan`
--

DROP TABLE IF EXISTS `loan`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `loan` (
  `loanID` int(11) NOT NULL AUTO_INCREMENT,
  `bookID` bigint(20) NOT NULL,
  `customerID` int(11) NOT NULL,
  `loanDate` date NOT NULL DEFAULT current_timestamp(),
  `dueDate` date NOT NULL,
  PRIMARY KEY (`loanID`),
  KEY `customerID` (`customerID`),
  KEY `FK_book` (`bookID`),
  CONSTRAINT `FK_book` FOREIGN KEY (`bookID`) REFERENCES `book` (`ISBN`),
  CONSTRAINT `FK_customer` FOREIGN KEY (`customerID`) REFERENCES `customer` (`customerID`) ON DELETE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `loan`
--

LOCK TABLES `loan` WRITE;
/*!40000 ALTER TABLE `loan` DISABLE KEYS */;
INSERT INTO `loan` VALUES (10,9780735619678,11,'2019-08-05','2019-08-19'),(13,9780735619678,10,'2019-08-06','2019-08-20'),(14,9781479274833,14,'2019-08-06','2019-08-20'),(15,9781269921091,10,'2019-08-06','2019-08-20'),(17,9781269921091,10,'2019-08-08','2019-08-22'),(18,9781269921091,10,'2019-08-08','2019-08-22'),(19,9708123456,14,'2019-08-08','2019-08-22'),(20,9708123456,14,'2019-08-08','2019-08-22');
/*!40000 ALTER TABLE `loan` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`cs340_hawkesc`@`%`*/ /*!50003 TRIGGER dateinsert BEFORE INSERT ON loan FOR EACH ROW SET NEW.dueDate = DATE_ADD(CURRENT_TIMESTAMP(), INTERVAL 14 DAY) */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `publisher`
--

DROP TABLE IF EXISTS `publisher`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `publisher` (
  `publisherID` int(11) NOT NULL AUTO_INCREMENT,
  `companyName` varchar(50) NOT NULL,
  `owner` varchar(50) DEFAULT NULL,
  `city` varchar(25) DEFAULT NULL,
  `state` varchar(2) NOT NULL,
  PRIMARY KEY (`publisherID`)
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `publisher`
--

LOCK TABLES `publisher` WRITE;
/*!40000 ALTER TABLE `publisher` DISABLE KEYS */;
INSERT INTO `publisher` VALUES (1,'No Starch Press',NULL,NULL,'CA'),(2,'Pearson',NULL,NULL,'MA'),(3,'Microsoft Press','Microsoft','Redmond','WA'),(5,'something publisher','bob smith','orange','IA'),(10,'Elemental','','New York','NY'),(11,'Ten Speed Press','','Portland','OR'),(12,'Penguin Classics','Tom Hardy','Los Angeles','CA'),(13,'Haynes','','','');
/*!40000 ALTER TABLE `publisher` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2019-08-15 17:55:15

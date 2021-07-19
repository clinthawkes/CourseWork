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
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `author`
--

LOCK TABLES `author` WRITE;
/*!40000 ALTER TABLE `author` DISABLE KEYS */;
INSERT INTO `author` VALUES 
(1,'Marijn','Haverbeke',NULL,'NJ'),
(2,'Elaine','Marieb',NULL,'NY'),
(3,'Katja','Hoehn',NULL,'NJ'),
(4,'Jane','Doe','Chicago','IL'),
(5,'Jane','Doe','Chicago','IL'),
(6,'Steve','McConnell','',''),
(9,'William','Baxter','','');
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
  `location` int(11) NOT NULL,
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
INSERT INTO `book` VALUES 
(9780735619678,'Complete Code',3,1),
(9781269921091,'Human Anatomy and Physiology',2,2),
(9781593279509,'Eloquent JavaScript',1,1);
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
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `book_author`
--

LOCK TABLES `book_author` WRITE;
/*!40000 ALTER TABLE `book_author` DISABLE KEYS */;
INSERT INTO `book_author` VALUES 
(1,9781593279509,1),
(3,9781269921091,3),
(4,9780735619678,6),
(6,9781269921091,2);
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
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES 
(1,'Clint','Hawkes','123 Lois Ln','Corvallis','OR','97330'),
(2,'Guy','Montag','451 Fahrenheit Dr','Corvallis','OR','97330'),
(3,'Joseph','Stallano','1014 Real Rd','Corvallis','OR','97330'),
(4,'Jonathan','Doedeer','360 Lookout Dr','Corvallis','OR','97330'),
(8,'Raegyn','Hawkes','444 Nice Rd','Schertz','TX','78154');
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
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `facility`
--

LOCK TABLES `facility` WRITE;
/*!40000 ALTER TABLE `facility` DISABLE KEYS */;
INSERT INTO `facility` VALUES 
(1,'Portland Main','1200 Broadway St','Portland','OR',97035),
(2,'Portland South','12897 Main St','Portland','OR',97230);
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
  CONSTRAINT `loan_ibfk_2` FOREIGN KEY (`customerID`) REFERENCES `customer` (`customerID`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `loan`
--

LOCK TABLES `loan` WRITE;
/*!40000 ALTER TABLE `loan` DISABLE KEYS */;
INSERT INTO `loan` VALUES 
(1,9781593279509,2,'2019-07-25','2019-08-08'),
(4,9780735619678,1,'0000-00-00','2019-08-18'),
(5,9780735619678,2,'0000-00-00','2019-08-18'),
(7,9780735619678,1,'2019-08-05','2019-08-19');
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
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `publisher`
--

LOCK TABLES `publisher` WRITE;
/*!40000 ALTER TABLE `publisher` DISABLE KEYS */;
INSERT INTO `publisher` VALUES 
(1,'No Starch Press',NULL,NULL,'CA'),
(2,'Pearson',NULL,NULL,'MA'),
(3,'Microsoft Press','Microsoft','Redmond','WA');
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

-- Dump completed on 2019-08-05 16:51:55

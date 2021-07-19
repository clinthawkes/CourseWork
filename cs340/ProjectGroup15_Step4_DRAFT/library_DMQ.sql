/* This will add a new author to the author table */
INSERT INTO author(firstName, lastName, homeCity, homeState) 
values(:fromFirstName, :fromLastName, :fromHomeCity, :fromHomeState);

/* This will add a new customer to the customer table */
INSERT INTO customer(firstName, lastName, streetAddress, city, state, zip)
values(:fromFirstName, :fromLastName, :fromStreetAddress, :fromCity, :fromState, :fromZip);

/* This will add a new facility to the facility table */
INSERT INTO facility(branch, streetAddress, city, state, zip, capacity)
values(:fromBranch, :fromStreetAddress, :fromCity, :fromState, :fromZip, :fromCapacity);

/* This will add a new publisher to the publisher table */
INSERT INTO publisher(companyName, owner, city, state, zip)
values(:fromCompanyName, :fromOwner, :fromCity, :fromState);

/* This will add a new entry to the loan table */
INSERT INTO loan(bookID, customerID) 
values(:fromBookID_dropDown, :fromCustomerID_dropDown);

/* This will add a new entry to the book table */
INSERT INTO book(ISBN, title, publisher, location)
values(:fromISBN, :fromTitle, :fromPublisher_dropDown, :fromLocation_dropDown);

/* This will associate a book to an author */
INSERT INTO book_author(bookID, authorID) 
values(:fromBookID_dropDown, :fromAuthorID_dropDown);

/* Return all the books and their IDs for the book drop down */
SELECT ISBN, title FROM book;

/* Return all the authors and their IDs for the drop down */
SELECT authorID, firstName, lastName FROM author;

/* Return all the publishers with their IDs for the drop down */
SELECT publisherID, companyName FROM publisher;

/* Return all the facilites with their IDs for the drop down */
SELECT facilityID, branch FROM facility;

/* Return all the cutomers with their IDs for the drop down */
SELECT customerID, firstName, lastName FROM customer;

/* Returns a customer's book loans using customer's first and last name */
SELECT c.customerID, firstName, lastName, ISBN, title, loanDate FROM customer c INNER JOIN
loan l ON l.customerID = c.customerID INNER JOIN book b ON b.ISBN = l.bookID WHERE
c.firstName = :input_from_form_fName AND c.lastName = :input_from_form_lName 
ORDER BY loanDate;

/* Gets all customers in ascending order of last name */
SELECT * FROM customer ORDER BY lastName;

/* Gets all books with the author, publisher and location info */
SELECT ISBN, title, a.firstName, a.lastName, companyName, branch FROM facility f INNER JOIN
book b ON b.location = f.facilityID INNER JOIN book_author ba ON ba.bookID = b.ISBN INNER JOIN
author a ON a.authorID = ba.authorID INNER JOIN publisher p ON p.publisherID = b.publisher
GROUP BY ISBN ORDER BY title;

/* Gets all books written by the specified author */
SELECT ISBN, title, a.firstName, a.lastName, companyName, branch FROM facility f INNER JOIN
book b ON b.location = f.facilityID INNER JOIN book_author ba ON ba.bookID = b.ISBN INNER JOIN
author a ON a.authorID = ba.authorID INNER JOIN publisher p ON p.publisherID = b.publisher
WHERE a.firstName = :input_from_user GROUP BY ISBN ORDER BY title;

/* Updates a customer's information */
UPDATE customer SET firstName = :fNameInput, lastName = :lNameInput, 
streetAddress = :streetAddressInput, city = :cityInput, state = :stateInput, zip = :zipInput 
WHERE customerID = :customerID_From_Customer_form;

/* Removes a customer from the customer table */
DELETE FROM customer WHERE customerID = :ID_From_Customer_Form;
    


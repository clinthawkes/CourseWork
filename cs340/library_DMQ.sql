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

/* Returns all authors */
SELECT * FROM author;

/* Returns book title, publisher and location */
SELECT ISBN, title, publisher.companyName, facility.branch FROM book INNER JOIN publisher 
ON publisher.publisherID = book.publisher INNER JOIN facility ON facility.branch = book.location;

/* Returns loan information  */
SELECT loanID, title, lastName, lastName, loanDate, dueDate FROM customer c INNER JOIN
loan l ON l.customerID = c.customerID INNER JOIN book b ON b.ISBN = l.bookID 

/* Gets all customers */
SELECT * FROM customer;

/* Gets all facilities */
SELECT * FROM facility;

/* Gets all publisher */
SELECT * FROM publisher;

/* Updates a customer's information */
UPDATE customer SET firstName = :fNameInput, lastName = :lNameInput, 
streetAddress = :streetAddressInput, city = :cityInput, state = :stateInput, zip = :zipInput 
WHERE customerID = :customerID_From_Customer_form;

/* Removes a customer from the customer table */
DELETE FROM customer WHERE customerID = :ID_From_customer_table;



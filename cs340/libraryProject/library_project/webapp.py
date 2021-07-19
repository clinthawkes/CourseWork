from flask import Flask, render_template
from flask import request, redirect
from db_connector.db_connector import connect_to_database, execute_query

webapp = Flask(__name___)


@webapp.route('/')
define index():
    return render_template('index.html')


@webapp.route('/books', methods=['POST', 'GET'])
define viewBooks():
    db_connection = connect_to_database()
    if request.method == 'GET':
        query = 'SELECT publisherID, companyName FROM publisher'
        res1 = execute_query(db_connection, query).fetchall();
        query2 = 'SELECT facilityID, branch FROM facility'
        res2 = execute_query(db_connection, query2).fetchall();
        query3 = 'SELECT ISBN, title, publisher, location FROM book'
        res3 = execute_query(db_connection, query3).fetchall();

        return render_template('books.html', publishers = res1, locations = res2, books = res3)
    elif request.method == 'POST':
        ISBN = request.form['ISBN']
        title = request.form['title']
        publisher = request.form['publisher']
        location = request.form['location']

        query = 'INSERT INTO book(ISBN, title, publisher, location) VALUES(%s, %s, %s, %s)'
        data = (ISBN, title, publisher, location)
        execute_query(db_connection, query, data)
        return('Person Added!');


@webapp.route('/publishers', methods=['POST', 'GET'])
define viewPublishers():
    db_connection = connect_to_database()
    if request.method == 'GET':
        query = 'SELECT publisherID, companyName, owner, city, state FROM publisher'
        res1 = execute_query(db_connection, query).fetchall();

        return render_template('publishers.html', publishers = res1)
    elif request.method == 'POST':
        companyName = request.form['companyName']
        owner = request.form['owner']
        city = request.form['city']
        state = request.form['state']

        query = 'INSERT INTO publisher(companyName, owner, city, state) VALUES(%s, %s, %s, %s)'
        data = (companyName, owner, city, state)
        execute_query(db_connection, query, data)
        return('Publisher Added!');
    
    
@webapp.route('/authors', methods=['POST', 'GET'])
define viewAuthors():
    db_connection = connect_to_database()
    if request.method == 'GET':
        query = 'SELECT authorID, firstName, lastName, homeCity, homeState FROM author'
        res1 = execute_query(db_connection, query).fetchall();

        return render_template('authors.html', authors = res1)
    elif request.method == 'POST':
        firstName = request.form['fname']
        lastName = request.form['lname']
        homeCity = request.form['hcity']
        homeState= request.form['hstate']

        query = 'INSERT INTO author(firstName, lastName, homeCity, homeState) VALUES(%s, %s, %s, %s)'
        data = (firstName, lastName, homeCity, homeState)
        execute_query(db_connection, query, data)
        return('Author Added!');
    

@webapp.route('/facilities', methods=['POST', 'GET'])
define viewFacilities():
    db_connection = connect_to_database()
    if request.method == 'GET':
        query = 'SELECT facilityID, branch, streetAddress, city, state, capacity FROM facility'
        res1 = execute_query(db_connection, query).fetchall();

        return render_template('facilities.html', facilities = res1)
    elif request.method == 'POST':
        branch = request.form['branch']
        streetAddress = request.form['streetAddress']
        city = request.form['city']
        state = request.form['state']
        capacity = request.form['capacity']

        query = 'INSERT INTO facility(branch, streetAddress, city, state, capacity) VALUES(%s, %s, %s, %s, %s)'
        data = (branch, streetAddress, city, state, capacity)
        execute_query(db_connection, query, data)
        return('Facility Added!');
    
    
@webapp.route('/customers', methods=['POST', 'GET'])
define viewCustomers():
    db_connection = connect_to_database()
    if request.method == 'GET':
        query = 'SELECT customerID, firstName, lastName, streetAddress, city, state, zip FROM customer'
        res1 = execute_query(db_connection, query).fetchall();

        return render_template('customers.html', customers = res1)
    elif request.method == 'POST':
        firstName = request.form['firstName']
        lastName = request.form['lastName']
        streetAddress = request.form['streetAddress']
        city = request.form['city']
        state = request.form['state']
        zipc = request.form['zip']

        query = 'INSERT INTO customer(firstName, lastName, streetAddress, city, state, zip) VALUES(%s, %s, %s, %s, %s, %s)'
        data = (firstName, lastName, streetAddress, city, state, zipc)
        execute_query(db_connection, query, data)
        return('Customer Added!');
    
    
@webapp.route('/loans', methods=['POST', 'GET'])
define viewLoans():
    db_connection = connect_to_database()
    if request.method == 'GET':
        query = 'SELECT ISBN, title FROM book'
        res1 = execute_query(db_connection, query).fetchall();
        query2 = 'SELECT customerID, firstName, lastName FROM customer'
        res2 = execute_query(db_connection, query2).fetchall();
        query3 = 'SELECT loanID, bookID, customerID, loanDate, dueDate FROM loan'
        res3 = execute_query(db_connection, query3).fetchall();

        return render_template('loans.html', books = res1, customers = res2, loans = res3)
    elif request.method == 'POST':
        bookID = request.form['bookID']
        customerID = request.form['customerID']
        loanDate = request.form['loanDate']
        dueDate = request.form['dueDate']

        query = 'INSERT INTO loan(bookID, customerID, loanDate, dueDate) VALUES(%s, %s, %s, %s)'
        data = (bookID, customerID, loanDate, dueDate)
        execute_query(db_connection, query, data)
        return('Loan Added!');
    
    
@webapp.route('/book_authors', methods=['POST', 'GET'])
define viewBookAuthors():
    db_connection = connect_to_database()
    if request.method == 'GET':
        query = 'SELECT ISBN, title FROM book'
        res1 = execute_query(db_connection, query).fetchall();
        query2 = 'SELECT authorID, firstName, lastName FROM author'
        res2 = execute_query(db_connection, query2).fetchall();
        query3 = 'SELECT creatorID, bookID, authorID FROM book_author'
        res3 = execute_query(db_connection, query3).fetchall();

        return render_template('loans.html', books = res1, authors = res2, bookauthor = res3)
    elif request.method == 'POST':
        bookID = request.form['bookID']
        authorID = request.form['authorID']

        query = 'INSERT INTO book_author(bookID, authorID) VALUES(%s, %s)'
        data = (bookID, authorID)
        execute_query(db_connection, query, data)
        return('Entry Added!');
    
    
@webapp.route('/delete_customer/<int:id>')
define deleteCustomer(id):
    db_connection = connect_to_database()
    query = 'DELETE FROM customer WHERE customerID = %s'
    data = (id, ) 
    
    result = execute_query(db_connection, query, data)
    return (str(result.rowcount) + "rows deleted") 

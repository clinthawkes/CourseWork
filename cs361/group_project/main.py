import os
import sys
import io
import csv
import pymysql
from app import app
from db import mysql
from flask import Flask, Response, render_template, flash, session, request, redirect, url_for
from datetime import datetime
#from flask_mysqldb import MySQL
from werkzeug.security import generate_password_hash, check_password_hash
from flask_session import Session
from utils import *

# random string generator to encrypt the cookie
SECRET_KEY = os.urandom(32)
app.config['SECRET_KEY'] = SECRET_KEY

# Configure session to use filesystem
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)


@app.route('/')
@app.route('/index')
@check_user_login
def index(username, user_id):
    """ Route for landing page """

    conn = None
    cursor = None

    try:
        # Get all locations
        conn = mysql.connect()
        cursor = conn.cursor(pymysql.cursors.DictCursor)
        cursor.execute("SELECT loc_id, loc_name FROM location")
        location = cursor.fetchall()

    except Exception as e:
        print(e)

    return render_template('index.html', username=username, location=location)


@app.route('/views/<loc_id>', methods=['POST'])
@check_user_login
def views(username, user_id, loc_id):
    """ Route for location views page """

    loc_id = request.form['loc_id']
    print(loc_id)

    return render_view(username, loc_id)


@app.route('/addFact', methods=['POST'])
@check_user_login
def addfact(username, user_id):
    """ Route for adding facts """
    if not username:
        return redirect(url_for('login'))

    loc_id = request.form['loc_id']
    hf_content = request.form['textarea1']
    
    conn = mysql.connect()
    cursor0 = conn.cursor(pymysql.cursors.DictCursor)
    cursor0.execute("SELECT user_id FROM `users` WHERE username = %s", (username))
    user_id = cursor0.fetchone()
    cursor0.close() 

    cursor = conn.cursor(pymysql.cursors.DictCursor)
    sql_query = "INSERT INTO `facts`(loc_id, user_id, hf_content) VALUES (%s, %s, %s)"
    cursor.execute(sql_query, (loc_id, user_id['user_id'], hf_content))
    conn.commit()
    cursor.close()
        
    return render_view(username, loc_id)


def render_view(username, loc_id):
    """ Function to get data for views page and render the views template """
    try:
        # Get the location data from the matching loc_id
        conn = mysql.connect()
        cursor = conn.cursor(pymysql.cursors.DictCursor)
        cursor.execute("SELECT loc_id, loc_name, loc_city, loc_country, loc_latitude, loc_longitude FROM location WHERE loc_id=%s", loc_id)
        location = cursor.fetchall()

        # Get the fact data that matches with loc_id
        cursor2 = conn.cursor(pymysql.cursors.DictCursor)
        sql = """
        SELECT facts.hf_content, users.username
        FROM `facts` facts INNER JOIN 
            `users` users
            ON facts.user_id = users.user_id
        WHERE facts.loc_id = %s
        """
        cursor2.execute(sql, loc_id)
        facts = cursor2.fetchall()

    except Exception as e:
        print(e)

    return render_template('views.html', username=username, location=location, facts=facts)


@app.route('/login', methods=['GET', 'POST'])
@check_user_login
def login(username, user_id):
    """ Route for users login """

    if username:
        return redirect(url_for('index'))

    if request.method == 'POST':
        username = request.form['username']
        pw = request.form['password']

        # Get user_id and password matching the username entered
        conn = mysql.connect()
        cursor = conn.cursor(pymysql.cursors.DictCursor)
        cursor.execute('SELECT user_id, password FROM users WHERE username = %s', (username,))
        row = cursor.fetchone()
        cursor.close()

        # If no such username is found
        if not row:
            flash("Please Enter a valid username", "danger")
            return render_template('login.html')

        # Verify password
        elif check_password_hash(row['password'], pw):
            session['user_id'] = row['user_id']
            session['user'] = username
            return redirect(url_for('index'))

        # If incorrect password
        else:
            flash("Please Enter a valid password", "danger")
            return render_template('login.html')

    return render_template('login.html')


@app.route('/signup', methods=['GET', 'POST'])
@check_user_login
def signup(username, user_id):
    """ Route for user registration """
    if username:
        flash("Please logout First", "danger")
        return render_template('signup.html')

    if request.method == 'POST':
        # get user input
        username = request.form['username']
        hashed_pw = generate_password_hash(request.form['password'])

        # validate user input
        if not username or not hashed_pw:
            flash("Please enter a valid username and password", "danger")
            return render_template('signup.html')

        # Check if username already exists
        conn = mysql.connect()
        cursor = conn.cursor(pymysql.cursors.DictCursor)
        #cur = mysql.connection.cursor()
        cursor.execute('SELECT * FROM `users` WHERE username = %s', (username,))
        result = cursor.fetchone()
        cursor.close()

        if result:
            flash("The username already exists. Please enter another username.", "danger")
            return render_template('signup.html')

        # if valid input, insert into users table in the db
        conn = mysql.connect()
        cursor = conn.cursor(pymysql.cursors.DictCursor)
        sql_query = 'INSERT INTO `users`(username, password) VALUES (%s, %s)'
        cursor.execute(sql_query, (username, hashed_pw,))
        conn.commit()
        cursor.close()

        flash("Successfully signed up! Please log in to continue", "success")
        return redirect(url_for('login'))

    return render_template('signup.html', username=None)


@app.route('/logout')
def logout():
    """ Route for user logout """
    session.pop('user', None)
    session.pop('user_id', None)
    return redirect(url_for('index'))


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=sys.argv[1], debug=True)
    #app.run()

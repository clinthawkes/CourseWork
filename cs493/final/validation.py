from google.cloud import datastore
import datetime
import constants

client = datastore.Client()

def valCapacity(number):
    if not isinstance(number, int):
        return False
    if number > 400 or number <= 0:
        return False
    return True

def valLocation(input):
    if not isinstance(input, str):
        return False
    if len(input) > 50 or len(input) == 0:
        return False
    character = ['-', '.', ',', '\'', ' ']
    for char in input:
        if not char.isalpha():
            if not char.isdigit():
                if char not in character:
                    return False
    return True

def valName(input):
    if not isinstance(input, str):
        return False
    if len(input) > 50 or len(input) == 0:
        return False
    character = ['-', '.', ',', '\'', ' ']
    for char in input:
        if not char.isalpha():
            if char not in character:
                return False
    return True
    
def valDate(input):
    if not isinstance(input, str):
        return False
    if len(input) != 10:
        return False
    for i in input:
        if not i.isdigit():
            if i != '/':
                return False
    data = input.split('/') 
    today = datetime.datetime.now()
    year = today.year 
    month = today.month
    day = today.day
    if int(data[0]) < year:
        return False
    if int(data[1]) < month and int(data[0]) <= year:
        return False
    if int(data[2]) < day and int(data[1]) <= month and int(data[0]) <= year:
        return False
    return True

def valBirthday(input):
    if not isinstance(input, str):
        return False
    if len(input) != 10:
        return False
    for i in input:
        if not i.isdigit():
            if i != '/':
                return False
    data = input.split('/') 
    today = datetime.datetime.now()
    year = today.year 
    month = today.month
    day = today.day
    if int(data[0]) > year:
        return False
    if int(data[1]) > month and int(data[0]) >= year:
        return False
    if int(data[2]) > day and int(data[1]) >= month and int(data[0]) >= year:
        return False
    return True
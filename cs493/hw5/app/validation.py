from google.cloud import datastore
import constants

client = datastore.Client()

def valLength(number):
    if not isinstance(number, int):
        return False
    if number > 2000 or number <= 0:
        return False
    return True

def valName(input):
    if not isinstance(input, str):
        return False
    if len(input) > 50 or len(input) == 0:
        return False
    character = ['-', '_', '!', '?', '.', ',', '$', '#', '@', '&', '/', '%', '*', ' ']
    for char in input:
        if not char.isalpha():
            if not char.isdigit():
                if char not in character:
                    return False
    return True

def valType(input):
    if not isinstance(input, str):
        return False
    if len(input) > 50 or len(input) == 0:
        return False
    for char in input:
        if not char.isalpha():
            if not char.isdigit():
                if char != ' ':
                    return False
    return True

def uniqueName(boat_name):
    query = client.query(kind=constants.boats)
    results = list(query.fetch())
    for b in results:
        if b["name"] == boat_name:
            return False
    return True
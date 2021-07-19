import random
import string

def getState():
    characters = string.ascii_letters + string.digits
    result = ''.join((random.choice(characters) for i in range(20)))
    return result
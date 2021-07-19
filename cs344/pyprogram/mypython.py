import string
import random
import sys

for i in range(3):
    fileName = "projectFile" + str(i+1) + ".txt"
    f = open(fileName, "w")
    letters = ''.join(random.choice(string.ascii_lowercase) for j in range(10)) + "\n"
    f.write(letters)
    sys.stdout.write(letters) 
    f.close() 

x = random.randrange(1, 43, 1)
sys.stdout.write(str(x)+"\n")
y = random.randrange(1, 43, 1)
sys.stdout.write(str(y)+"\n")
z = x * y
sys.stdout.write(str(z)+"\n")

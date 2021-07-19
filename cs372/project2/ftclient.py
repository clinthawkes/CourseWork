#!/bin/python2.7

#Clinton Hawkes
#CS372-400
#Project 2
#Last Modified: 2020-03-08
# This is the client side of project 2. The server side was written in c. The
# server is started on a port of the user's choosing and then sits and waits
# until a client connects. Afer the client connects, the client sends commands 
# for the server to process and execute. Commands consist of -l for listing the
# current contents of the directory on the server or -g for the server to 
# transfer the specified file to the client

# SOURCES: Official Python Documentation, www.realpython.com/socket-programming, 
#          docs.python.org/3/howto/sockets.html, couple stackoverflow posts 
#          regarding user input. ***I didn't copy anything word for word '


from socket import * 
import sys
import os
import os.path

# Function is used to validate the user commands entered on the command line. If
# the commands are valid, the function will return with no issues. If there is an
# issue with the commands, the system will exit and an error message will print
# Preconditions: none
# Postconditions: commands should be valid
def validateArgs():
    # Splits IP address into 4 parts for validation. If there are any issues with
    # the IP address, an error will print 
    list = sys.argv[1].split(".")
    if len(list) == 4:
        for x in list:
            if int(x) < 0 or int(x) > 255:
                sys.exit("Invalid Host IP")
    else:
        sys.exit("Invalid Host IP")
        
    # Ensures the server port number entered is in the correct range 
    if int(sys.argv[2]) < 1024 or int(sys.argv[2]) > 65535:
        sys.exit("Invalid Server Port Range")
        
    # Ensures the third command is either -l or -g 
    if sys.argv[3] != "-l":
        if sys.argv[3] != "-g":
            sys.exit("Must contain -l or -g")
            
    # Ensures the server port number entered is in the correct range 
    if len(sys.argv) == 5:
        if int(sys.argv[4]) < 1024 or int(sys.argv[4]) > 65535:
            sys.exit("Invalid Data Port Range")
            
    # Ensures the filename is the correct format and then ensures the data port
    # number is in the correct range
    if len(sys.argv) == 6:
        file = sys.argv[4].split(".") 
        if len(file) != 2:
            sys.exit("Incorrect filename formatting")
        if file[1] != "txt":
            sys.exit("File must have .txt extention")
        if int(sys.argv[5]) < 1024 or int(sys.argv[5]) > 65535:
            sys.exit("Invalid Data Port Range")


# Function is used to connect to the control socket with the user's specified port
# number.
# Precondition: socket must be created in main
# Postconditions: socket connects to server socket 
def controlSetup(sock):
    serverName = sys.argv[1]
    serverPort = int(sys.argv[2]) 
    sock.connect((serverName,serverPort))


# Function is used to setup the data socket with the user's specified port
# number and then start it listening on that port'
# Precondition: socket must be created in main
# Postconditions: data socket is setup and waiting for data transfer 
def dataSetup(sock):
    if len(sys.argv) == 5:
        serverPort = int(sys.argv[4])  
    elif len(sys.argv) == 6:
        serverPort = int(sys.argv[5]) 
    sock.bind(('',serverPort)) 
    sock.listen(1)         # only one client can connect at a time
    
    
# Function is used to retrieve the data from the socket that was sent from
# the client. Once it is taken out of the socket, it is printed to the screen
# Preconditions: client socket must be populated and passed into function
# Postconditions: if socket is closed, return 0. If message is received, 
#                 return 1
def receiveMessage(sock):
     
    sentence = sock.recv(4096)  # 501 bytes can be read from the socket
    if len(sentence) == 0:     # this means socket is closed
        return 0 
    return sentence 


# Function is used to get user provided message and send it to the socket for
# transmission to the client's machine. This function limits the size of the 
# message being sent to 500 characters, including the user handle
# Preconditions: client socket must be populated and passed into the functions
# Postconditions: program terminates if user tyes \quit. Function returns 1
#                 if message was sent successfully
def sendMessage(sock):
    if len(sys.argv) == 5: 
        userInput = sys.argv[3] + " " + sys.argv[4] 
    elif len(sys.argv) == 6:
        userInput = sys.argv[3] + " " + sys.argv[4] + " " + sys.argv[5]
    sock.send(userInput)
    return 1 
    
    
if __name__ == '__main__':
    
    # Function validates the user's input to ensure the commands are correct 
    # An error message will be displayed if they are incorrect 
    validateArgs()

    # Socket for control connection is created and connects to the server
    controlSocket = socket(AF_INET, SOCK_STREAM)
    controlSetup(controlSocket)
    
    # The user's commands are sent to the server for processing 
    sendMessage(controlSocket) 
    
    # Server returns either a message to continue or a message with an error. 
    reply = receiveMessage(controlSocket)  
    
    # Proceed tells this client to contiue with setting up the data socket
    if reply != "proceed":
        controlSocket.close()
        sys.exit(sys.argv[1] + ":" + sys.argv[2] + " says " + reply.upper())
    
    # Creates socket for data transfer and starts listening 
    dataSocket = socket(AF_INET,SOCK_STREAM)  
    dataSetup(dataSocket)  

    # Continues to loop and check for new clients until kill sig sent 
    clientSocket, addr = dataSocket.accept()
    
    # Following will execute if the -l command was sent to the server for a direcory listing 
    if sys.argv[3] == "-l": 
        print("Receiving directory structure from " + sys.argv[1] + ":" + sys.argv[4]) 
        
        # Receives the first message sent from the server 
        message = receiveMessage(clientSocket) 
        
        # Loop will continue reading from the socket and printing until the socket is empty 
        while message: 
            print(message)
            message = receiveMessage(clientSocket)
            
        # The control connection is closed(the data is closed by the server) 
        controlSocket.close() 
        
    # Following will execute if the -g command was sent to the server for file transfer
    elif sys.argv[3] == "-g": 
        
        # The following while loop checks to see if the file requested is already present
        # in this client's working directory. If there is already a file with the same name,
        # a "_" is prepended to the filename that will be created. It loops until there is
        # no file with the same name that will be created
        filename = sys.argv[4] 
        flag = 1
        while flag == 1:
            if os.path.isfile(filename):
                filename = "_" + filename 
            else:
                flag = 0
            
        # Message is printed informing user of the filename and the host that is sending it  
        # A file with the unique filename created above is created and opened. I closed the file
        # and reopened it with "appending" property so the information is added to the end of 
        # the file. 
        print("Receiving " + sys.argv[4] + " from "+ sys.argv[1] + ":" + sys.argv[5]) 
        file = open(filename, "w+") 
        file.close()
        file = open(filename, "a")
        
        # Loop created to read part of the file from the data socket. The server sends the file
        # in pieces, so the loop reads socket - writes to file - reads socket - writes to file
        message = receiveMessage(clientSocket)
        while message:
            file.write(message)
            message = receiveMessage(clientSocket)

        # File is closed after the entire file has been received
        file.close()
        
        # Confirmation message is printed and the socket is closed 
        print("File transfer complete")
        controlSocket.close() 
            

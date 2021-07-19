#Clinton Hawkes
#CS372-400
#Project 1
#Last Modified: 2020-02-09
# This is the server side of project 1. The client side was written in c. The
# server is started on a port of the user's choosing and then sits and waits
# until a client connects. Afer the client connects, the user and server exchange
# messages back and forth until one of them wants to quit by issuing the \quit 
# command'

# SOURCES: Official Python Documentation, www.realpython.com/socket-programming, 
#          docs.python.org/3/howto/sockets.html, couple stackoverflow posts 
#          regarding user input. ***I didn't copy anything word for word '


from socket import * 
import sys
import os


# Function is used to setup the server socket with the user's specified port
# number and then start it listening on that port'
# Precondition: socket must be created in main
# Postconditions: none
def initialSetup(sock):
    serverPort = int(sys.argv[1])
    sock.bind(('',serverPort)) 
    sock.listen(1)         # only one client can connect at a time
    
    
# Function is used to retrieve the data from the socket that was sent from
# the client. Once it is taken out of the socket, it is printed to the screen
# Preconditions: client socket must be populated and passed into function
# Postconditions: if socket is closed, return 0. If message is received, 
#                 return 1
def receiveMessage(sock):
    sentence = sock.recv(501)  # 501 bytes can be read from the socket
    if len(sentence) == 0:     # this means socket is closed
        return 0 
    print(sentence)
    return 1


# Function is used to get user provided message and send it to the socket for
# transmission to the client's machine. This function limits the size of the 
# message being sent to 500 characters, including the user handle
# Preconditions: client socket must be populated and passed into the functions
# Postconditions: program terminates if user tyes \quit. Function returns 1
#                 if message was sent successfully
def sendMessage(sock):
    userInput = raw_input('server> ')     #prompts user for input 
    while len(userInput) > 492:
        print("Error: message can only be 500 characters (including handle)")
        userInput = raw_input('server> ') 
    # if the user wants to quit they just have to type the command "\quit" 
    if userInput == "\quit":
        clientSocket.close()
        print("Socket has been closed") 
        return 0 
    # User message with the server handle prepended to the front is sent  
    clientSocket.send('server> ' + userInput)
    return 1 
    
    
if __name__ == '__main__':
    
    # Creates socket and uses function to initialize it
    serverSocket = socket(AF_INET,SOCK_STREAM)  
    initialSetup(serverSocket)  
    
    # Continues to loop and check for new clients until kill sig sent 
    while 1:      
         
        print("The server is ready to receive")
        clientSocket, addr = serverSocket.accept()
        
        while 1: 
            
            # If a 0 is returned from either of the following functions, the
            # socket has been closed (user initiated or otherwise) The loop
            # continues allowing the exchange of messages if not.
            
            if not receiveMessage(clientSocket):
                break
            
            if not sendMessage(clientSocket):
                break

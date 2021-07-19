/* Clinton Hawkes */
/* CS372-400 */
/* Project 1 */
/* Last Modified: 2020-02-09 */
/* This project is used to teach how processes talk to one another through the use of sockets. */
/* The client program is written in C and the server program is written in python. First, start */
/* the server and note the host/port number so it can be listening for the client program(this). */
/* This program is started by ./chatclient [HOSTNAME] [PORT] */
/* After the user chooses a handle, they can chat back and forth with the server by using */
/* sockets. */

/* SOURCES: I used my course materials/lectures/assignments from cs344  */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#define h_addr h_addr_list[0]


/* error function used to print to stderr and exit */
void error(const char *msg) { fprintf(stderr, "%s", msg); exit(2); } // Error function used for reporting issues

/* This function is used to ask the user what they want their handle to be (Identification). The handle */
/* is returned to the calling function using a char * */
/* Preconditions: none */
/* Postconditions: user handle is created and passed back to main */
char* makeHandle(){
    
    size_t handleSize = 0; 
    char* clientHandle = NULL; 
    size_t charRead; 
    
    /* Asks the user what they want their handle to be and then reads in the stdin. */
    printf("What do you want your handle to be? (max 10 chars): ");
    charRead = getline(&clientHandle,&handleSize,stdin);
    clientHandle[charRead-1] = '\0'; 
    
    /* The handle can only be 10 characters, so the user is asked to re-enter if it */ 
    /* is too long. */
    while(charRead > 11){ 
        free(clientHandle);
        clientHandle = NULL; 
        printf("Handle has a max length of 10 chars, please enter it now: ");
        charRead = getline(&clientHandle,&handleSize,stdin);
        clientHandle[charRead-1] = '\0'; 
    } 
    /* Returns handle after all requirements are met */ 
    return clientHandle; 
}


/* This function is used to setup the socket for the client program. I wrote this in cs344, so I borrowed */ 
/* heavily from that course. The socked struct is populated after the hostname and server port number */
/* are obtained from the user. The socket file descriptor is then returned to main*/ 
/* Preconditions: sockaddr struct and hostent struct must be created and passed into the function. */ 
/* Postconditions: Sockaddr struct and hostent struct are populated with the correct user info and the */ 
/*                 connections with the server is made. */ 
int initialSetup(struct sockaddr_in *serverAddress, struct hostent **serverHostInfo, char* argv[]){
    
    int socketFD; 
	int portNumber = atoi(argv[2]); // Get the port number, convert to an integer from a string
    char* serverHost = argv[1]; 
    
	/* Set up the server address struct using the user provided portnumber and host */
	memset((char*)serverAddress, '\0', sizeof(*serverAddress)); // Clear out the address struct
    
	serverAddress->sin_family = AF_INET; // Create a network-capable socket
	serverAddress->sin_port = htons(portNumber); // Store the port number
	(*serverHostInfo) = gethostbyname(serverHost); // Convert the machine name into a special form of address
    
	if (serverHostInfo == NULL) { error("CLIENT: ERROR, no such host");}
	memcpy((char*)&serverAddress->sin_addr.s_addr, (char*)(*serverHostInfo)->h_addr, (*serverHostInfo)->h_length); // Copy in the address

	/* Set up the socket */
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");
	
	 /* Connect to server */
	if (connect(socketFD, (struct sockaddr*)serverAddress, sizeof(*serverAddress)) < 0) // Connect socket to address
		error("CLIENT: ERROR connecting");
    
    return socketFD; 
} 


/* This function is used to send a message to the server. The length of the message must be */
/* under 500 characters total, and if the user types "\quit", the socket will close and the */
/* program will exit. The server will go back and listen for another client to connect. */ 
/* Every message has the user specified handle prepended to the front of the message. */
/* Preconditions: Socket file descriptor must be created and passed into the functions along with */
/*                the user's create handle' */
/* Postconditions: If user types \quit, the program will terminate. If the user sends a message successfully, */
/*                 a 1 is returned to main and the message is sent to the socket. */
int sendMessage(int socket, char* handle){
    
    char* format = "> "; 
    char messageText[501];
    char* input = NULL; 
    size_t bufferSize = 0; 
    
    printf("%s> ", handle); /*prints the user handle so the user knows to type */
    
    /* gets the input from the user */ 
    int charEntered = getline(&input, &bufferSize, stdin);
    
    /* Ensures the user's message is total length of 500 characters' */ 
    if(charEntered > (498-strlen(handle))){
        while(charEntered > (498-strlen(handle))){ 
            printf("Error: message may only be 500 characters long (including handle)\n"); 
            printf("%s> ", handle); 
            charEntered = getline(&input, &bufferSize, stdin);
        } 
    } 
    
    /* if error, clear stdin and reset */ 
    if(charEntered == -1){
        clearerr(stdin);
    }else if(strcmp(input,"\\quit\n")== 0){   /* user wants to exit program */
        free(input); 
        return 0;      /* signals the program to terminate in main */ 
    }else{
        input[charEntered-1] = '\0'; /* removes the newline character at the end */
    }
    
    /* Message can be 500 characters with a terminating \0. This concatenates the sentence together */ 
    memset(&messageText, '\0', 501); 
    strcat(messageText,handle); 
    strcat(messageText,format); 
    strcat(messageText, input); 
    
    /* Ensures all the user's message is sent to the socket by looping until all characters */
    /* are sent. The message is freed after it has been sents' */ 
    int total = 0;
    while(1){
        // Send verify message to server
        int charsWritten = send(socket, messageText,strlen(messageText), 0); // Write to the server
        if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
        total += charsWritten;
        /* breaks out only if the desired number of characters have been sent*/  
        if(total == strlen(messageText)) break;
    } 
    free(input); 
    return 1;       /* signals a sucessful send */
} 
    
/* This function is used to get the info that was sent by the server to the socket. The message */
/* that has been received is then printed to the screen */
/* Preconditions: Socket file descriptor must be created and passes into the function. */
/* Postconditions: If socket has been closed, the function returns a 0 and the program is terminated. */
/*                 If a message is received successfully, a 1 is returned to main */

int receiveMessage(int socket){

	char buffer[512];
     
    // Get return message from server
    memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer again for reuse
    
    int charsRead = 1; 
    int total = 0;
    
    charsRead = recv(socket, buffer, sizeof(buffer) - 1, 0); // Read data from the socket, leaving \0 at end
    
    if (charsRead < 0) error("CLIENT: ERROR reading from socket");
    total += charsRead;
    
    /* breaks out and terminates program if zero characters have been read */  
    if(total == 0) return 0;
    
    /* print the message if data was received */ 
    printf("%s\n", buffer);
   
    return 1;      /* message was received sucessfully */
}


int main(int argc, char *argv[]){
    
	int socketFD;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
    char* handle = NULL; 
    
    /* ensures the correct number of arguments have been provided by the user */ 
	if (argc < 3) { fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); exit(1); } // Check usage & args
    
    /* Gets the user's desired chat handle' */ 
    handle = makeHandle(); 

    /* Setup the socket with the user provided information */ 
    socketFD = initialSetup(&serverAddress, &serverHostInfo, argv);
    
    /* Loops letting the client/server take turns sending messages until one exits with \quit */ 
    while(1){ 
        
        /* if either returns a 0 value, the program will exit */ 
        if(!(sendMessage(socketFD,handle))) break;    
        if(!(receiveMessage(socketFD))) break; 
    } 

    /* memory cleanup */ 
    free(handle); 
	close(socketFD); // Close the socket
	return 0;
}

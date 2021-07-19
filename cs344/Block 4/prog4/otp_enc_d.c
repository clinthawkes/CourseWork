#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) { fprintf(stderr, "%s", msg); exit(1); } // Error function used for reporting issues

/* function used to create a pool of processes to handle encryption */
void createPool(pid_t* array, int num){
    int i;
    for(i = 0; i < num; i++){ 
        array[i] = fork();
        if(array[i] < 0){ fprintf(stderr, "Fork Error"); i--;}
        /* if the process is a child it breaks out of the function */ 
        else if(array[i] == 0) break; 
    } 
}

/* function splits the received message from the client into a key string and a message string to be encrypted */
char* splitText(char* messageReceived){
    char* key = messageReceived;
    char* message = NULL;
    char* encrypted = NULL;
    int i, charCount, len, temp; 
    len = strlen(messageReceived);
    
    /* finds the # character and breaks the received message into a key and message */ 
    for(i = 0; i < len; i++){
        if(messageReceived[i] == '#'){
            messageReceived[i] = '\0';
            message = key + i + 1;
        }
    }
    
    /* determines how many characters the cipher text will be */ 
    charCount = (int)strlen(message); 
    
    /* creates a string variable the size of charCount to hold the cipher text */ 
    encrypted = malloc(charCount + 1); 
    memset(encrypted, '\0', charCount + 1); 
    
    /* The following takes the message and encryptes it using the key file. */ 
    /* Guide: A = 0, B = 1, ..., Z = 25, space = 26
     * The value of the character in the message is added to the value of the character
     * in the key. Mod 27 is then taken to figure what character to put in the cipher*/ 
    for(i = 0; i < charCount; i++){
        if(key[i] == ' '){
            if(message[i] > 64 && message[i] < 91){
                temp = (int)message[i] - 65;
                encrypted[i] = ((temp + 26)%27) + 65;
                if(encrypted[i] == 91) encrypted[i] = 32; 
            }else{
                encrypted[i] = 'Z';
            }
        }else{
            if(message[i] > 64 && message[i] < 91){
                temp = (int)message[i] - 65;
                encrypted[i] = ((temp + ((int)key[i] - 65))%27) + 65;
                if(encrypted[i] == 91) encrypted[i] = 32; 
            }else{
                temp = 26;
                encrypted[i] = ((temp + ((int)key[i] - 65))%27) + 65;
                if(encrypted[i] == 91) encrypted[i] = 32; 
            }
        }
    }
    return encrypted; 
}


int main(int argc, char *argv[]){
    
	int listenSocketFD, establishedConnectionFD, portNumber, charsRead, messageLen, total;
	socklen_t sizeOfClientInfo;
	char buffer[1024];
    char* rawText = NULL; 
    char* encryptedText = NULL; 
    char* proceed = "proceed";
    char* rejected = "rejected"; 
	struct sockaddr_in serverAddress, clientAddress;
    pid_t processes[5] = {0}; 

    /* ensures the correct number of arguments are provided by the user */ 
	if (argc < 2) { fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1); } // Check usage & args

	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	// Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) error("ERROR opening socket");

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
		error("ERROR on binding");
	listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections

    /* calls function to create the child processes that will handle encryption */ 
    createPool(processes, 5); 
    
    /* if the process is a child */ 
    if(processes[4] == 0){ 
        
        while(1){ 
            // Accept a connection, blocking if one is not available until one connects
            sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
            establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
            if (establishedConnectionFD < 0) fprintf(stderr, "ERROR on accept");

            // Get the message from the client and display it
            memset(buffer, '\0', sizeof(buffer));
            
            total = 0;
            while(1){
                /* will receive the verification message from the client */ 
                charsRead = recv(establishedConnectionFD, buffer, sizeof(buffer)-1, 0); // Read the client's message from the socket
                if (charsRead < 0) fprintf(stderr, "ERROR reading from socket");
                total += charsRead;
                /* exits the loop after the desired number of characters have been read from the client */ 
                if(total == 6) break;
            }
                
            if(strcmp(buffer, "encode") != 0){ 
                total = 0;
                while(1){
                    /* sends a rejection if the client did not send the word "encode" */ 
                    charsRead = send(establishedConnectionFD, rejected, strlen(rejected), 0); // Send success back
                    if (charsRead < 0) fprintf(stderr, "ERROR writing to socket");
                    total += charsRead;
                    /* exits the loop after the desired number of characters have been sent to the client */ 
                    if(total == strlen(rejected)) break;
                } 
            }else{ 
                
                total = 0;
                while(1){
                    // Send a Success message back to the client
                    charsRead = send(establishedConnectionFD, proceed, strlen(proceed), 0); // Send success back
                    if (charsRead < 0) fprintf(stderr, "ERROR writing to socket");
                    total += charsRead;
                    /* exits the loop after the desired number of characters have been sent to the client */ 
                    if(total == strlen(proceed)) break;
                }
                
                // Get the message from the client and display it
                memset(buffer, '\0', sizeof(buffer));
                /* will receive the number of character in the message that will follow */ 
                charsRead = recv(establishedConnectionFD, buffer, sizeof(buffer)-1, 0); // Read the client's message from the socket
                if (charsRead < 0) fprintf(stderr, "ERROR reading from socket");
                
                /* changes the value recived into an int and creates a string that will hold that many characters */ 
                messageLen = atoi(buffer); 
                rawText = (char*)malloc(messageLen + 1); 
                
                // Send a Success message back to the client
                total = 0;
                while(1){
                    /* sends message telling the client to proceed with the message */ 
                    charsRead = send(establishedConnectionFD, proceed + total, strlen(proceed) - total, 0); // Send success back
                    if (charsRead < 0) fprintf(stderr, "ERROR writing to socket");
                    total += charsRead;
                    /* exits loop after the desired number of characters have been sent to the client */ 
                    if(total == strlen(proceed)) break;
                } 
                
                // Get the message from the client and display it
                memset(rawText, '\0', messageLen+1);
                
                total = 0; 
                while(1){
                    charsRead = recv(establishedConnectionFD, rawText + total, messageLen - total, 0); // Read the client's message from the socket
                    if (charsRead < 0){ fprintf(stderr, "ERROR reading from socket"); break;}
                    total += charsRead; 
                    /* exits the loop after the desired number of characters have been received from the client */ 
                    if(total == messageLen) break; 
                } 
                
                /* takes the message that was just received and uses the splitText function to encrypt it. The cipher is returned */ 
                encryptedText = splitText(rawText); 
                
                // Send a Success message back to the client
                total = 0;
                while(1){ 
                    charsRead = send(establishedConnectionFD, encryptedText + total, strlen(encryptedText) - total, 0); // Send success back
                    if (charsRead < 0) fprintf(stderr, "ERROR writing to socket");
                    total += charsRead; 
                    /* exits the loop after the cipher text has been sent to the client in its entirety */ 
                    if(total == strlen(encryptedText)) break; 
                } 
            } 
            /* memory cleanup */ 
            free(encryptedText);            
            encryptedText = NULL; 
            free(rawText);
            rawText = NULL;
            close(establishedConnectionFD); // Close the existing socket which is connected to the client
        } 
    /* if the process is the parent */ 
    }else{
        /* pause and continue to listen */ 
        pause();
    }
	close(listenSocketFD); // Close the listening socket
    
	return 0; 
}

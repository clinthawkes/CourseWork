#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) { fprintf(stderr, "%s", msg); exit(1); } // Error function used for reporting issues

/* function used to creat a pool of processes to handle the decryption */
void createPool(pid_t* array, int num){
    int i;
    for(i = 0; i < num; i++){ 
        array[i] = fork();
        if(array[i] < 0) {fprintf(stderr, "Fork Error"); i--;}
        /* if the process is a child, it breaks out of the function */ 
        else if(array[i] == 0) break; 
    } 
}

/* function splits the received message from the client into a key string and a cipher string to be decrypted */
char* splitText(char* messageReceived){
    char* key = messageReceived;
    char* message = NULL;
    char* decrypted = NULL;
    int i, charCount, len, temp, temp2; 
    len = strlen(messageReceived);
    
    /* searches until the # character is found and splits the message into its key/cipher parts */ 
    for(i = 0; i < len; i++){
        if(messageReceived[i] == '#'){
            messageReceived[i] = '\0';
            message = key + i + 1;
        }
    }
    
    /* determines how large the decrypted message will be */ 
    charCount = (int)strlen(message); 
    
    /* creates a string variable to hold the decrypted message */ 
    decrypted = malloc(charCount + 1); 
    memset(decrypted, '\0', charCount + 1); 
    
    /* The following takes the cipher and decrypts it using the key file. 
     * Guide: A = 0, B = 1, ..., Z = 25, space = 26
     * The value of the character in the key is subtracted from the value
     * of the character in the cipher. If the subtraction is negative, 27 is
     * added to the value. This determines what character to put in the decrypted text*/ 
    for(i = 0; i < charCount; i++){
        if(key[i] == ' '){
            if(message[i] > 64 && message[i] < 91){
                temp = (int)message[i] - 65;
                decrypted[i] = ((temp - 26)+27) + 65;
                if(decrypted[i] == 91) decrypted[i] = 32; 
            }else{
                decrypted[i] = 'A';
            }
        }else{
            if(message[i] > 64 && message[i] < 91){
                temp = (int)message[i] - 65;
                temp2 = (temp - ((int)key[i] - 65));
                if(temp2 >= 0){
                    decrypted[i] = temp2 + 65;
                }else{
                    decrypted[i] = (temp2 + 27) + 65;
                }
                if(decrypted[i] == 91) decrypted[i] = 32; 
            }else{
                temp = 26;
                decrypted[i] = (temp - ((int)key[i] - 65)) + 65;
                if(decrypted[i] == 91) decrypted[i] = 32; 
            }
        }
    }
    return decrypted; 
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

    /* uses function to create the pool of processes used to decrypt the ciphers */ 
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
                /* exits the loop after the desired number of characters have been receivded from client */ 
                if(total == 6) break;
            }                

            /* if the verification message is invalid */ 
            if(strcmp(buffer, "decode") != 0){ 
                total = 0;
                while(1){
                    /* a rejction message is sent back to the client */ 
                    charsRead = send(establishedConnectionFD, rejected + total, strlen(rejected) - total, 0); // Send success back
                    if (charsRead < 0) fprintf(stderr, "ERROR writing to socket");
                    total += charsRead;
                    /* exits the loop after the desired number of characters have been sent to the client */ 
                    if(total == strlen(rejected)) break;
                } 
            /* the verification message was correct, so the following exectutes */ 
            }else{ 
                
                total = 0; 
                while(1){ 
                    // Send a Success message back to the client
                    charsRead = send(establishedConnectionFD, proceed + total, strlen(proceed) - total, 0); // Send success back
                    if (charsRead < 0) fprintf(stderr, "ERROR writing to socket");
                    total += charsRead;
                    /* exits the loop after the desired number of characters have been sent to the client */
                    if(total == strlen(proceed)) break; 
                } 
                
                // Get the message from the client and display it
                memset(buffer, '\0', sizeof(buffer));
                /* will receive the number of characters the cipher/key contains that will be sent next */ 
                charsRead = recv(establishedConnectionFD, buffer, sizeof(buffer)-1, 0); // Read the client's message from the socket
                if (charsRead < 0) fprintf(stderr, "ERROR reading from socket");
                /* printf("SERVER: I received this from the client: \"%s\"\n", buffer); */
                
                /* converts the message into a int and creates a string variable with that size */ 
                messageLen = atoi(buffer); 
                rawText = (char*)malloc(messageLen + 1); 
                
                total = 0;
                while(1){
                    // Send a Success message back to the client
                    charsRead = send(establishedConnectionFD, proceed + total, strlen(proceed) - total, 0); // Send success back
                    if (charsRead < 0) fprintf(stderr, "ERROR writing to socket");
                    total += charsRead;
                    /* will exit the loop after the desired number of characters have been sent to the client */ 
                    if(total == strlen(proceed)) break;
                } 
                
                // Get the message from the client and display it
                memset(rawText, '\0', messageLen+1);
                
                total = 0;
                while(1){
                    /* reads in the cipher/key message */ 
                    charsRead = recv(establishedConnectionFD, rawText + total, messageLen - total, 0); // Read the client's message from the socket
                    if (charsRead < 0) fprintf(stderr, "ERROR reading from socket");
                    total += charsRead;
                    /* exits after the entire message has been received */ 
                    if(total == messageLen) break;
                }
                
                /* uses a function to decrypt the cipher and gets the original string back */ 
                encryptedText = splitText(rawText); 
                 
                total = 0;
                while(1){
                    /* sends the decrypted cipher(original message) back to the client */ 
                    charsRead = send(establishedConnectionFD, encryptedText, strlen(encryptedText), 0); // Send success back
                    if (charsRead < 0) fprintf(stderr, "ERROR writing to socket");
                    total += charsRead;
                    /* exits after the entire message has been sent back to the client */ 
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
    
    }else{
        /* pauses and continues to listen */ 
        pause();
    }
	close(listenSocketFD); // Close the listening socket
    
	return 0; 
}

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

/* function used to combine key/message text together to be sent to daemon */
char* combineText(char* key, char* message){
    char* new = NULL;
    int length;
    length = strlen(key) + strlen(message);

    /* text will be the size of the message + key */ 
    new = (char*)malloc(length); 
    memset(new, '\0', length); 
    
    /* concatenates the key and message together */ 
    strcat(new, key);
    new[strlen(key)-1] = '#';
    strcat(new, message);
    new[length - 1] = '\0'; 
    
    return new; 
}

/* verifies the characters in the provided filename. File may only contain A - Z and space */
int verifyInput(char* string){
    int i; 
    for(i = 0; i < strlen(string) - 1; i++){
        if(string[i] > 90 || string[i] < 65){
            if(string[i] != 32){
                return 0;
            }
        }
    }
    return 1; 
}

/* function will open the file provided as a parameter and read its contents into a string */
char* readFile(char* fileName){
    int charsRead;
    long fileSize;
    FILE* file;
    char* readInput; 

    file = fopen(fileName, "r");
    if(file == NULL) error("Failed to open file"); 
    
    /* positions file pointer at end of file and counts the number of characters from the beginning 
     * to the end of the filefile*/ 
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file); 
    fseek(file, 0, SEEK_SET);

    /* creates a string for the number of characters counted */ 
    readInput = malloc(fileSize + 1);
    if(!readInput) error("Error creating string\n");
    
    /* reads the file into the string and adds a null terminator */ 
    charsRead = fread(readInput, 1, fileSize, file);
    readInput[fileSize] = 0; 
    if(charsRead < 0) error("Error reading from file\n");
    fclose(file); 

    /* outputs error and exits program if a file contains an invalid character */ 
    if(!verifyInput(readInput)){fprintf(stderr, "Invalid character in %s file\n", fileName); exit(1);} 
    
    return readInput; 
}


int main(int argc, char *argv[]){
    
	int socketFD, portNumber, charsWritten, charsRead, total, numChars;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char buffer[1024];
    char transfer[20]; 
    char* keyArg = argv[2]; 
    char* messageArg = argv[1]; 
    char* keyText = NULL;
    char* messageText = NULL;
    char* allText = NULL; 
    char* encrypted = NULL; 
    char verify[] = "encode"; 
    
    /* ensures the correct number of arguments have been provided by the user */ 
	if (argc < 3) { fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); exit(1); } // Check usage & args
    
    /* uses readFile function to read the provided filename into a char* */ 
    keyText = readFile(keyArg); 
    messageText = readFile(messageArg); 
    
    /* ensures the key file is at least a large as the provided message */ 
    if(strlen(keyText) < strlen(messageText)){ fprintf(stderr, "Error: Key is smaller than Message\n"); exit(1);}
    
    /* counts the number of characters that will be transferred to the server */ 
    numChars = strlen(keyText) + strlen(messageText) - 1;
    sprintf(transfer, "%d", numChars); 
    
    /* uses combineText function to combine the text in the provided filenames for transfer to the server */ 
    allText = combineText(keyText, messageText); 
    
	// Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) { error("CLIENT: ERROR, no such host");}
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address

	// Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");
	
	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to address
		error("CLIENT: ERROR connecting");

    total = 0;
    while(1){
        // Send verify message to server
        charsWritten = send(socketFD, verify, strlen(verify), 0); // Write to the server
        if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
        total += charsWritten;
        /* breaks out only if the desired number of characters have been sent*/  
        if(total == strlen(verify)) break;
    } 

	// Get return message from server
	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer again for reuse
    
    total = 0;
    while(1){
        charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); // Read data from the socket, leaving \0 at end
        if (charsRead < 0) error("CLIENT: ERROR reading from socket");
        total += charsRead;
        /* breaks out only if the desired number of characters have been read */  
        if(total >= 7) break;
    }
    
    if(strcmp(buffer, "rejected") == 0){
        
        /* prints out error and exits program if the server has rejected the connection request */ 
        fprintf(stderr, "Connection rejected: otp_enc cannot connect to otp_dec_d @ port %s", argv[3]); exit(2); 
        
    }else{
        
        total = 0;
        while(1){
            // Send size of message to server
            charsWritten = send(socketFD, transfer, strlen(transfer), 0); // Write to the server
            if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
            total += charsWritten;
            /* breaks out only if the desired number of characters have been sent */  
            if(total == strlen(transfer)) break;
        } 

        memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer again for reuse
        
        total = 0;
        while(1){
            charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); // Read data from the socket, leaving \0 at end
            if (charsRead < 0) error("CLIENT: ERROR reading from socket");
            total += charsRead;
            /* breaks out only if the desired number of characters have been read */  
            if(total >= 7) break;
        } 
        
        if(strcmp(buffer, "proceed") == 0){
            
            total = 0;
            while(1){
                // Send key and message to server
                charsWritten = send(socketFD, allText, strlen(allText), 0); // Write to the server
                if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
                total += charsWritten;
                /* breaks out only if the desired number of characters have been sent*/  
                if(total == strlen(allText)) break;
            } 

            /* creates a string variable to hold the encrypted message(cipher) returned from the server */ 
            encrypted = malloc(strlen(messageText) + 1); 
            memset(encrypted, '\0', strlen(messageText)); // Clear out the buffer again for reuse
            
            total = 0; 
            while(1){ 
                charsRead = recv(socketFD, encrypted + total, strlen(messageText) - total, 0); // Read data from the socket, leaving \0 at end
                if (charsRead < 0) error("CLIENT: ERROR reading from socket");
                total += charsRead;
                /* breaks out only if the desired number of characters have been read */  
                if(total == strlen(messageText)-1) break;
            } 
                
            /* print the ciper out to stdout */ 
            printf("%s\n", encrypted);
        }
    }

    /* memory cleanup */ 
    free(encrypted); 
    free(keyText);
    free(messageText);
    free(allText); 
	close(socketFD); // Close the socket
	return 0;
}

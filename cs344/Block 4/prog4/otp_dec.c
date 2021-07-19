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

/* function used to print error to stderr and exit program */
void error(const char *msg) { fprintf(stderr, "%s", msg); exit(2); } // Error function used for reporting issues

/* function used to combine key/cipher text to be sent to the daemon */
char* combineText(char* key, char* message){
    char* new = NULL;
    int length;
    length = strlen(key) + strlen(message);

    /* text will be the same size as cipher + key */ 
    new = (char*)malloc(length); 
    memset(new, '\0', length); 
    
    /* concatenates the key and cipher together */ 
    strcat(new, key);
    new[strlen(key)-1] = '#';
    strcat(new, message);
    new[length - 1] = '\0'; 
    
    return new; 
}

/* verifies the characters in the provided filename. File may only contain A - Z and a space */
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

    /* opens file for reading */ 
    file = fopen(fileName, "r");
    if(file == NULL) error("Failed to open file"); 
    
    /* moves file pointer to end of file and counts characters from the beginning of the file */ 
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file); 
    fseek(file, 0, SEEK_SET);

    /* creates a string to fit the characters we just counted */ 
    readInput = malloc(fileSize + 1);
    if(!readInput) error("Error creating string\n");
    
    /* reads the file into the string variable we just created */ 
    charsRead = fread(readInput, 1, fileSize, file);
    readInput[fileSize] = 0; 
    if(charsRead < 0) error("Error reading from file\n");
    fclose(file); 

    /* checks that there were not invalid characters in the file we just read */ 
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
    char* cipherArg = argv[1]; 
    char* keyText = NULL;
    char* cipherText = NULL;
    char* allText = NULL; 
    char* encrypted = NULL; 
    char verify[] = "decode"; 
    
    /* ensures there are enough arguments provided by the user */ 
	if (argc < 3) { fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); exit(1); } // Check usage & args
    
    /* uses readFile function to read the filename provided into the char* on the left */ 
    keyText = readFile(keyArg); 
    cipherText = readFile(cipherArg); 
    
    /* ensures the key text is at least as long as the cipher text file */ 
    if(strlen(keyText) < strlen(cipherText)){ fprintf(stderr, "Error: Key is smaller than ciphertext\n"); exit(1);}
    
    /* counts the number of characters that will be sent to the daemon and stores the number as a string */ 
    numChars = strlen(keyText) + strlen(cipherText) - 1;
    sprintf(transfer, "%d", numChars); 
    
    /* uses the function combineText to concatenate the key and cipher together for transfer */ 
    allText = combineText(keyText, cipherText); 
     
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
        /* breaks out only if the desired number of characters have been sent */ 
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
        
        /* prints error and exits if the server rejected the request to connect */ 
        fprintf(stderr, "Connection rejected: otp_dec cannot connect to otp_enc_d @ port %s\n", argv[3]); exit(2); 
        
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
                /* breaks out only if the desired number of characters have been sent */ 
                if(total == strlen(allText)) break;
            } 

            /* creates a string variable to hold the decrypted cipher */ 
            encrypted = malloc(strlen(cipherText) + 1); 
            memset(encrypted, '\0', strlen(cipherText)); // Clear out the buffer again for reuse
             
            total = 0; 
            while(1){ 
                charsRead = recv(socketFD, encrypted + total, strlen(cipherText) - total, 0); // Read data from the socket, leaving \0 at end
                if (charsRead < 0) error("CLIENT: ERROR reading from socket");
                total += charsRead;
                /* breaks out only if the desired number of characters have been read */ 
                if(total == strlen(cipherText) - 1) break;
            } 
            
            /* prints decrypted cipher(message) out to stdout */ 
            printf("%s\n", encrypted);
        }
    }

    /* memory cleanup */ 
    free(encrypted); 
    free(keyText);
    free(cipherText);
    free(allText); 
	close(socketFD); // Close the socket
	return 0;
}

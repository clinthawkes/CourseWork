/* Clinton Hawkes */
/* CS372-400 */
/* Project 2 - Server side */
/* Last Modified: 2020-03-08 */
/* This is the server side of the FTP assignment. This program creates a control connection */
/* on a port specified in the command line arguments. The port waits for clients to connect */
/* and issue commands for listing the directory contents or transferring files that are */
/* currently in the server's directory. The server will connect to a port issued in the */ 
/* commands from the client for the data transfer. After the client is finished, they */ 
/* disconnect and the server waits for another client to connect. I have implemented multi- */
/* threading on this server, so there can be upto 5 clients connected at the same time. */

/* SOURCES: My main source for this project was the work I had already completed in cs344. Program */
/*          4 and program 2 came in very handy. Program 4 was used to help with the socket comm */
/*          and program 2 was used for the directory and file manipulation. I also borrowed the */
/*          waitASec() function found below: timmurphy.org/2009/09/29/nanosleep-in-c-c/ */
/*          I didn't use any other sources for code. I did clarify my understanding of certain */
/*          functions, but I didn't copy any code in. Just looked up return values, required */
/*          parameters, etc...  These were from geeksforgeeks.com, c-for-dummies.org, */
            /* man7.org/linux */

/* EXTRA CREDIT: I have made the server multithreaded, so more than one client may connect at */
/*               the same time */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <dirent.h>
#include <time.h>
#define h_addr h_addr_list[0]

void error(const char *msg) { fprintf(stderr, "%s", msg); exit(1); } // Error function used for reporting issues


/* function used to creat a pool of processes for multi threading */
/* preconditions: array must be created in main to hold pid numbers. */
/* postconditions: array is filled with the pid numbers of the child processes */
void createPool(pid_t* array, int num){
    int i;
    for(i = 0; i < num; i++){
        array[i] = fork();
        if(array[i] < 0) {fprintf(stderr, "Fork Error"); i--;}
        /* if the process is a child, it breaks out of the function */
        else if(array[i] == 0) break;
    }
}


/* This function is used to setup the socket for the client program. I wrote this in cs344, so I borrowed */
/* heavily from that course. The socked struct is populated after the hostname and server port number */
/* are obtained from the user. The socket file descriptor is then returned to main*/
/* Preconditions: sockaddr struct and hostent struct must be created and passed into the function. */
/* Postconditions: Sockaddr struct and hostent struct are populated with the correct user info and the */
/*                 connections with the server is made. */
int setupControl(struct sockaddr_in* serverAddress, char* argv[]){
    int portNumber, listenSocketFD;

	// Set up the address struct for this process (the server)
	memset((char *)serverAddress, '\0', sizeof(*serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress->sin_family = AF_INET; // Create a network-capable socket
	serverAddress->sin_port = htons(portNumber); // Store the port number
	serverAddress->sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	// Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) error("ERROR opening control socket\n");

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr*)serverAddress, sizeof(*serverAddress)) < 0) // Connect socket to port
		error("ERROR on control binding\n");
	listen(listenSocketFD,5); // Flip the socket on - it can now receive up to 5 connections

    return listenSocketFD;
}


/* This function is used to setup the socket to send data to the client program. I wrote this in cs344, so I borrowed */
/* heavily from that course. The socked struct is populated after the hostname and server port number */
/* are obtained from the user. The socket file descriptor is then returned to main*/
/* Preconditions: sockaddr struct and hostent struct must be created and passed into the function. */
                    /* port number and hostname of client must be passed into function */
/* Postconditions: Sockaddr struct and hostent struct are populated with the correct user info and the */
/*                 connections with the server is made. */
int setupData(struct sockaddr_in *serverAddress, struct hostent** serverHostInfo, char* port, char* hostName){

    int socketFD;
	int portNumber = atoi(port); // Get the port number, convert to an integer from a string
    char* serverHost = hostName;

	/* Set up the server address struct using the user provided portnumber and host */
	memset((char*)serverAddress, '\0', sizeof(*serverAddress)); // Clear out the address struct

	serverAddress->sin_family = AF_INET; // Create a network-capable socket
	serverAddress->sin_port = htons(portNumber); // Store the port number
	(*serverHostInfo) = gethostbyname(serverHost); // Convert the machine name into a special form of address

	if (serverHostInfo == NULL) { error("DATA CONNECTION: ERROR, no such host\n");}
	memcpy((char*)&serverAddress->sin_addr.s_addr, (char*)(*serverHostInfo)->h_addr, (*serverHostInfo)->h_length); // Copy in the address

	/* Set up the socket */
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("DATA CONNECTION: ERROR opening socket\n");

	 /* Connect to server */
	if (connect(socketFD, (struct sockaddr*)serverAddress, sizeof(*serverAddress)) < 0) // Connect socket to address
		error("DATA CONNECTION: ERROR connecting to client\n");

    return socketFD;
}

/* I was having an issue with my program trying to connect to the socket on the client for data transfer */
/* before the client had time to receive the go ahead and create the socket. I didn't want to use the sleep */
/* function and wait for a whole second, so I got this function from timmurphy.org/2009/09/29/nanosleep-in-c-c/ */
/* This function "sleeps" for 1/10th of a second */
void waitASec(){
    int milisec = 100;
    struct timespec req = {0};
    req.tv_sec = 0;
    req.tv_nsec = milisec * 1000000L;
    nanosleep(&req, (struct timespec*)NULL);
}


/* This function is used to send a message to the client.  */
/* Preconditions: Socket file descriptor must be created and passed into the functions along with */
/*                the user's create handle' */
/* Postconditions: If user types \quit, the program will terminate. If the user sends a message successfully, */
/*                 a 1 is returned to main and the message is sent to the socket. */
int sendMessage(int socket, char* message){

    /* Ensures all the user's message is sent to the socket by looping until all characters */
    /* are sent. The message is freed after it has been sents' */
    int total = 0;
    while(1){
        // Send verify message to server
        int charsWritten = send(socket, message, strlen(message), 0); // Write to the server
        if (charsWritten < 0) error("ERROR writing to socket\n");
        total += charsWritten;
        /* breaks out only if the desired number of characters have been sent*/
        if(total == (int)strlen(message)) break;
    }

    return 1;       /* signals a sucessful send */
}


/* This function is used to get the info that was sent by the server to the socket. The message */
/* that has been received is then returned to the calling function as a char* */
/* Preconditions: Socket file descriptor must be created and passes into the function. */
/* Postconditions: If socket has been closed, the function returns a 0 and the program is terminated. */
/*                 If a message is received successfully, a 1 is returned to main */
char* receiveMessage(int socket){

	char* buffer = (char*)malloc(512 * sizeof(char));

    // Get return message from server
    memset(buffer, '\0', 512); // Clear out the buffer again for reuse

    int charsRead = 0;

    charsRead = recv(socket, buffer, 511, 0); // Read data from the socket, leaving \0 at end

    if (charsRead < 0) error("ERROR reading from socket\n");

    return buffer;      /* message was received sucessfully */
}

/* Function is used to validate the commands received from the client. It ensures all the commands */
/* are the correct format and returns an integer corresponding to the results encountered. Main */
/* will print out the error and send a message to the client dependent upon what is wrong. */
/* Preconditions: commands must be received and stored in array passed to function */
/* Postconditions: meaningful integer will be returned to signal how main should handle the situation */
int validateInput(char argList[3][256]){

    char list[] = "-l";
    char get[] = "-g";

    /* This runs if the first command is -l. It checks to make sure the port number following the command */
    /* is in the correct range. */
    if(strncmp(argList[0], list, 2) == 0){
        int portNum = atoi(argList[1]);
        if(portNum > 1023 && portNum < 65536){
            return 1;
        }else{
            return 3;
        }
    /* This runs if the first command is -g. It checks to see if the file requested is available on the server, */ 
    /* and if it is, the port number for the data connection is checked to make sure it is within correct range */
    }else if(strncmp(argList[0], get, 2) == 0){
        
        struct dirent* info;
        DIR* directory = opendir(".");
        
        /* This loop checks to see if the filename is present */ 
        while((info = readdir(directory)) != NULL){
            if(strcmp(info->d_name, (argList)[1]) == 0){
                int portNum = atoi(argList[2]);
                if(portNum > 1023 && portNum < 65536){
                    closedir(directory);
                    return 1; 
                }else{
                    return 3;
                }
            }
        }
        return 2; /*file not found*/
    }
    return 0; /* command did not contain -l or -g */
}


int main(int argc, char *argv[]){

	int listenSocketFD, establishedConnectionFD, dataFD, readin, code;
	socklen_t sizeOfClientInfo;
    char commands[3][256];
    char* rawText = NULL;
    char* temp = NULL;
	struct sockaddr_in serverAddress, clientAddress, clientData;
    struct hostent* clientHostInfo;
    pid_t processes[5] = {0};

    /* ensures the correct number of arguments are provided by the user */
	if (argc < 2) { fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1); } // Check usage & args

    /* Setup for the control connection */ 
    listenSocketFD = setupControl(&serverAddress, argv);

    printf("Server open on %s\n", argv[1]);

    /* uses function to create the pool of processes used to decrypt the ciphers */
    createPool(processes, 5);

    /* if the process is a child */
    if(processes[4] == 0){

        while(1){
            // Accept a connection, blocking if one is not available until one connects
            sizeOfClientInfo = sizeof(clientAddress); // Get the size of the address for the client that will connect
            establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept
            if (establishedConnectionFD < 0) fprintf(stderr, "ERROR on accept");

            /* Retrieves and prints the client IP that has been accepted */ 
            char* ip = inet_ntoa(clientAddress.sin_addr);
            printf("Connection from %s\n\n", ip);

            /* Retrieves message from the control socket that was sent by the client */ 
            rawText = receiveMessage(establishedConnectionFD);

            /* Preparing buffer for commands to be stored */
            memset(commands, '\0', (3*256) * sizeof(char));

            /* Breaks message received from client into individual commands for easier processing/handling */ 
            int count = 0;
            temp = strtok(rawText, " ");
            while(temp){
                snprintf(commands[count], 255, "%s", temp);
                temp = strtok(NULL, " \n");
                count++;
                if(count > 2) break;
            }

            /* Memory Cleanup */
            free(rawText);
            rawText = NULL;

            /* Validates the commands to ensure correctness */ 
            code = validateInput(commands);

            /* Only runs if validate function returns 1. If other integer is returned, a message is sent in the switch */
            /* statement further down the page */
            if(code == 1){

                /* Sends message to client that they may continue setting up the data port, and then waits 1/10th of a second */
                /* for the client to setup the data port before this server tried to connect */
                sendMessage(establishedConnectionFD, "proceed");
                waitASec();

                /* Following executes if the command is -l */ 
                if(strcmp(commands[0], "-l") == 0){

                    /* prints client info for server and then connects to the data port created by the client */ 
                    printf("List directory requested on port %s\n", commands[1]);
                    dataFD = setupData(&clientData, &clientHostInfo, commands[1], ip);
                    printf("Sending directory contents to %s:%s\n\n", ip, commands[1]);

                    struct dirent* info;
                    DIR* directory = opendir(".");
                    char temp[256];
                    memset(temp, '\0', 256);

                    /* Loops through all the files in the current directory and sends their name in a message to the client */ 
                    while((info = readdir(directory)) != NULL){
                        strcat(temp, info->d_name);
                        strcat(temp, "\n");
                        sendMessage(dataFD, temp);
                        memset(temp, '\0', 256);
                    }
                    /* Closes the data connection */ 
                    close(dataFD);

               /* Following will execute if the first command is -g */     
               }else if(strcmp(commands[0], "-g") == 0){

                    /* Prints the file requested by client and connects to the data socket on the client */ 
                    printf("File \"%s\" requested on port %s\n", commands[1], commands[2]);
                    dataFD = setupData(&clientData, &clientHostInfo, commands[2], ip);
                    printf("Sending \"%s\" to %s:%s\n\n", commands[1], ip, commands[2]);

                    char* tempLine = NULL;
                    size_t length = 0;
                    FILE* fp = fopen(commands[1], "r");

                    /* Loop reads a section of the specified file and then sends that portion to the client. */
                    /* The file is read from again and another portion is sent to the client. This continues */
                    /* until the entire file is sent. */
                    while((readin = getline(&tempLine, &length, fp)) != -1){
                        sendMessage(dataFD, tempLine);
                        free(tempLine);
                        tempLine = NULL;
                    }
                    close(dataFD);
                }
                
            /* This statement will execute if there was a problem found when validating the client's commands */ 
            }else{
                
                /* The return value from validateInput() determines which error message is sent back to the client */ 
                switch(code){
                    
                    /* Messages sent to the client are self explanitory. They all have to do with the client's commands */
                    case 0: sendMessage(establishedConnectionFD, "Invalid Command");
                            break;
                    case 2: printf("File \"%s\" requested on port %s\n", commands[1], commands[2]);
                            printf("File '%s' not found. Sending error message to %s:%s\n", commands[1], ip, commands[2]);
                            sendMessage(establishedConnectionFD, "File not found");
                            break;
                    case 3: sendMessage(establishedConnectionFD, "Reserved/Invalid Port");
                            break;
                }
            }
            close(establishedConnectionFD); // Close the existing socket which is connected to the client
        }
    }else{
        /* parent process pauses and continues to listen */
        pause();
    }
	close(listenSocketFD); // Close the listening socket

	return 0;
}

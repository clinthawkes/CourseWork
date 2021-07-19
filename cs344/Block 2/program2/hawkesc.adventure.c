/*Clinton Hawkes*/
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include <dirent.h>

/* global mutex is created and initialized */
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 

/* container that each room will use to store data pertaining to it */
struct room {
    char name[10];
    int numCon;
    char conName[7][10];
    struct room* connection[7];
    char roomType[15]; 
};

/* container that is used to pass parameters into the thread function */
struct args {
    int* flag;
    int* file;
    int written; 
};

/* function is called when the information about the current room needs to be */
/* printed to the console. The current room pointer is passed to the function */
void printRoomInfo(struct room* cur){
    
    /* prints the current room name */ 
    printf("\nCURRENT LOCATION: %s\n", cur->name);
    
    /* prints all the connections for the current room using the container data */ 
    /* function correctly formats the names according to the spec. */ 
    printf("POSSIBLE CONNECTIONS: ");
    int i; 
    for(i = 0; i < cur->numCon-1; i++){
        printf("%s, ", cur->conName[i]);
    }
    /* prints the last connection name with a period */  
    printf("%s.\n", cur->conName[cur->numCon-1]);  
    
    printf("WHERE TO? >"); 
}

/* function uses the current room container and string parameters that have been passed */
/* to it to ensure only valid user entries are accepted */
int validEntry(struct room* cur, char* input){
    int i;
    /* if loop returns a 1, the user has input the name of a room that the current room */
    /* has as a connection */
    for(i = 0; i < cur->numCon; i++){
        if(strcmp(input, cur->conName[i]) == 0){
            return 1;
        } 
    }
    /* if the user input the string "time" the function returns a 1 */ 
    if(strcmp(input, "time") == 0) return 1; 
    
    /* user must have entered an invalid room name or other command. */ 
    return 0; 
}

/* function is called to write the current time and date to the file opened in the main */
/* function. This function is ran in the second thread and uses a mutex to control */
/* when it is able to write to the file */
void* printTime(void* arg){
    time_t t;
    struct tm* info;
    /* will hold the formatted time/date string to be written */ 
    char lineToWrite[100];
    memset(lineToWrite, '\0', 100);
    
    /* this function in the second thread attempts to lock the global mutex. If another thread */
    /* has alreadly lock it, this function will wait until it is unlocked to proceed. */
    pthread_mutex_lock(&lock);
    
    /* checks the flag variable to see if the thread should exit or continue. The flag will make */
    /* this thread exit only during the memory cleanup at the end of the main function */
    /* this is to prevent another time record from being written to the file when the program terminates */ 
    if(*(((struct args*)arg)->flag) == 0) pthread_exit((NULL)); 
    
    time(&t);
    info = localtime(&t); 
    
    /* uses the information provided by the time library calls above to create a formatted string containing */
    /* the date and time information required by the program specs */
    strftime(lineToWrite, sizeof(lineToWrite), "%l:%M%P, %A, %B %d, %Y\n", info); 
    
    /* writes the string that was just created to the file */ 
    ((struct args*)arg)->written = write(*(((struct args*)arg)->file), lineToWrite, strlen(lineToWrite)*sizeof(char));     

    /* unlocks the mutex so the other thread may continue */ 
    pthread_mutex_unlock(&lock);
    return NULL; 
}
    
/* function prints the rusults of the game after the user has reached the end room */
void printResults(int steps, char* path[]){

    printf("\nYOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n"); 
    printf("YOU FINISHED IN %d STEPS. YOUR PATH TO VICTORY WAS:\n", steps); 
    int i; 
    /* prints each of the rooms visited */ 
    for(i = 0; i < steps; i++){
        printf("%s\n", path[i]);
    }
}

int main(int argc, char *argv[]){
    
    int i, k, steps, count, tmpCnt, len; 
    int fileDescriptor = 0; 
    int newestDirTime = -1;
    int flag = 1; 
    char targetDirPrefix[32] = "hawkesc.rooms.";
    char newestDirName[256];
    char fileName[256]; 
    char readBuffer[100]; 
    char* pathway[50];    
    char* tempLine = NULL;
    char* tok; 
    FILE* file; 
    DIR* dirToCheck;
    ssize_t readIn;
    size_t length = 0;
    struct dirent* fileInDir;
    struct stat dirInfo;
    struct room* list[7]; 
    struct room* current = NULL; 
    struct room* finish = NULL; 
    
    /* creates the container used to pass info to the second thread */ 
    struct args* pass = (struct args*)malloc(sizeof(struct args)); 
    pass->flag = &flag;
    pass->file = &fileDescriptor;
    
    /* creates the object for the second thread, first thread locks the global */
    /* mutex, and the second thread is then created */ 
    pthread_t t2; 
    pthread_mutex_lock(&lock); 
    pthread_create(&t2, NULL, printTime, (void*)pass); 
    
    /* the following code was taken from the class material. In a few words, */  
    /* it opens up the current directory and searches through all the files and */
    /* directories for names that contain the string saved in the prefix variable. */
    /* if a name is found with the prefix, the newestDirTime is compared to the */ 
    /* existing time. This continues until the newest fold is found */
    dirToCheck = opendir(".");
    if(dirToCheck != 0){
        while((fileInDir = readdir(dirToCheck)) != NULL){
            if(strstr(fileInDir->d_name, targetDirPrefix) != NULL){
                stat(fileInDir->d_name, &dirInfo);

                if((int)dirInfo.st_mtime > newestDirTime){
                    newestDirTime = (int)dirInfo.st_mtime;
                    memset(newestDirName, '\0', sizeof(newestDirName));
                    strcpy(newestDirName, fileInDir->d_name);
                }
            }
        }
    }
    closedir(dirToCheck);

    
    /* opens the directory that was found to be the newest above */ 
    dirToCheck = opendir(newestDirName);
    if(dirToCheck != 0){
        count = 0; 
        
        /* loop will continue until there are no more files in the directory */ 
        while((fileInDir = readdir(dirToCheck)) != NULL){
            tmpCnt = 0;
            
            /* checks to see if the current file is a room file */ 
            if(strstr(fileInDir->d_name, "_room") != NULL){
                /* creates a struct to hold the information about a room in this file */ 
                list[count] = (struct room*)malloc(sizeof(struct room)); 
                list[count]->numCon = 0; 
                
                /* combines the directory and file name into a string so it can be opened */ 
                memset(fileName, '\0', sizeof(fileName)); 
                sprintf(fileName, "%s/%s", newestDirName, fileInDir->d_name);
                file = fopen(fileName, "r"); 
                assert(file); 
                    
                /* loop will run as long as getline is able to read lines from file */ 
                while((readIn = getline(&tempLine, &length, file)) != -1){
                    
                    /* each file contains descriptions with useful info separated by : */
                    /* this first token is the description and is used to determine where */
                    /* to store the accompanying info */
                    tok = strtok(tempLine, ":");
                    
                    if(strcmp(tok, "ROOM NAME") == 0){
                        /* token contains the name of the room, and it is saved to the struct */ 
                        tok = strtok(NULL, ": ");
                        strcpy(list[count]->name, tok); 
                        
                        /* trimming the trailing newline */ 
                        len = strlen(list[count]->name);
                        list[count]->name[len-1] = '\0';
                        
                    }else if(strcmp(tok, "ROOM TYPE") == 0){
                        /* token contains the type of room, and it is saved to the struct */  
                        tok = strtok(NULL, ": ");
                        strcpy(list[count]->roomType, tok); 
                        
                        /* trimming the trailing newline */ 
                        len = strlen(list[count]->roomType);
                        list[count]->roomType[len-1] = '\0';
                        
                        /* there are two pointers, one points to the start room and one points to */
                        /* the end room. the following assigns the pointers accordingly */
                        if(strcmp(list[count]->roomType, "START_ROOM") == 0){ 
                            current = list[count];
                        }else if(strcmp(list[count]->roomType, "END_ROOM") == 0){ 
                            finish = list[count];
                        }
                    }else{                        
                        /* token contains a connection of the current room. The connection name */
                        /* is saved to the struct */
                        tok = strtok(NULL, ": ");
                        strcpy(list[count]->conName[tmpCnt], tok); 
                        
                        /* trimming the trailing newline */ 
                        len = strlen(list[count]->conName[tmpCnt]);
                        list[count]->conName[tmpCnt][len-1] = '\0';
                        
                        /* variable tracking the number of connections for this room is inc */ 
                        list[count]->numCon++; 
                        tmpCnt++; 
                    }                        
                }
                count++; 
                fclose(file); 
            } 
        }
    }
    closedir(dirToCheck);
    
    i = 0;
    steps = 0; 
    
    /* This is the main loop where all the user interaction takes place. The loop will */ 
    /* continue until the end room is reached */
    while(i == 0){
        /* information about the current room is printed to the console and user input */
        /* is obtained */
        printRoomInfo(current);
        k = getline(&tempLine, &length, stdin); 
        
        /* i needed to trim a trailing newline from the user input to compare to the */ 
        /* room name variable */
        len = strlen(tempLine); 
        tempLine[len-1] = '\0'; 
        
        /* the following will execute if the user entered a valid room name or "time" */ 
        if(validEntry(current, tempLine)){
            for(k = 0; k < 7; k++){
                if(strcmp(list[k]->name, tempLine) == 0){
                    
                    /* user entered a valid connection, so the current room pointer is */ 
                    /* updated to the user's selected room, and the new room is saved */ 
                    /* to show the user the path taken */ 
                    current = list[k]; 
                    pathway[steps] = current->name; 
                    steps++; 
                    k = 7; 
                    
                    /* if the room that was just selected is the end room, the game is over */
                    if(current == finish) i = 1; 
                }
            }
            /* user has entered the time command if the following executes */ 
            if(strcmp("time", tempLine) == 0){
                /* opens a file where the current time and date will be written/read from */ 
                fileDescriptor = open("currentTime.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
                
                /* first thread unlocks the mutex so the second thread can execute the printTime */
                /* function. First thread then joins the second thread so the first will wait */
                pthread_mutex_unlock(&lock);
                pthread_join(t2, NULL);
                
                /* once the second thread is done and unlocks the mutex, the first will lock the mutex */
                /* and create another second thread to run the printTime function */
                pthread_mutex_lock(&lock);
                pthread_create(&t2, NULL, printTime, (void*)pass); 
                
                /* the file pointer is returned to the beginning so the date that was just written in the */
                /* second thread can be read. The file is read and printed to the console */
                lseek(fileDescriptor, 0, SEEK_SET); 
                memset(readBuffer, '\0', sizeof(readBuffer)); 
                read(fileDescriptor, readBuffer, pass->written);
                printf("\n%s", readBuffer); 
                close(fileDescriptor); 
            }
        }else{
            /* user has entered an invalid command */  
            printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
        } 
         
    }
    
    /* calls the function to print the end message after the user has reached the end room */ 
    printResults(steps, pathway);
    
    /* the remaining lines are used to cleanup memory that has been allocated */ 
    for(i = 0; i < 7; i++){
        free(list[i]);
    }
    
    /* flag tells the printTime function to exit instead of printing to the file */ 
    flag = 0; 
    pthread_mutex_unlock(&lock); 
    pthread_join(t2, NULL); 
    free(pass); 
    free(tempLine);
    
    return 0;
}

/*Clinton Hawkes*/
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/* Global string arrays to hold the room names and types */
char roomNames[10][9] = {"kitchen", "dining", "pool", "living", "family", 
                        "garage", "basement", "attic", "lair", "bedroom"};

char roomTypes[3][11] = {"START_ROOM", "MID_ROOM", "END_ROOM"}; 

/* Container used to store the info about each room */
struct room {
    char* name;
    int numCon;
    char* roomType;
    char* connections[6];
};

/* function is used to check if the all the rooms have between 3 and 6 connections */
/* each. If they do a 1 is returned. Otherwise a 0 is returnded */
int IsGraphFull(struct room* array[]){
    int i;
    for(i = 0; i < 7; i++){
        if(array[i]->numCon < 3){ 
            return 0;
        } 
    }
    return 1;
}

/* function is used to get a random room when called upon. a pointer to the room */
/* is returned. */
struct room* GetRandomRoom(struct room* array[]){
    int temp;
    temp = rand()%7;
    return array[temp]; 
}

/* function checks to see if a room is able to make another connection to another room. */
/* if it has 6 connections, a 0 is returned. If it has < 6, a 0 is returned. */
int CanAddConnectionFrom(struct room* single){
    if(single->numCon < 6){
        return 1;
    }
    return 0;
}

/* function is used to ensure a room is not connected to the same room twice. If a connection */
/* has already been made to a room, a 1 is returned. Otherwise a 0 is returned */
int ConnectionAlreadyExists(struct room* x, struct room* y){
    int i;
    for(i = 0; i < x->numCon; i++){
        if(strcmp(x->connections[i], y->name) == 0){
            return 1;
        }
    }
    return 0;
}

/* function is used to make connections between the two room structs passed into the function. */
void ConnectRoom(struct room* x, struct room* y){
    x->connections[x->numCon] = y->name; 
    x->numCon++;
    y->connections[y->numCon] = x->name; 
    y->numCon++; 
}

/* function checks to see if the two rooms passed into the function are the same room. If they are the */ 
/* same room, a 1 is returned. Otherwise a 0 is returned. */
int IsSameRoom(struct room* x, struct room* y){
    if(x == y){
        return 1;
    }
    return 0;
}

/* function is called when a connection should be made between two random rooms. */ 
void AddRandomConnection(struct room* list[]){
    struct room* A;
    struct room* B;

    while(1 == 1){
        /* gets a random room using the function and checks to see if a connection can be made. */
        /* this loop continues until a room is randomly found that can make a connection */
        A = GetRandomRoom(list);

        if(CanAddConnectionFrom(A)){
            break;
        }
    }

    /* this gets a random room and checks to see if it can add a connection, then checks to make sure this */
    /* room and the other room picked are not the same room, and finally makes sure it will not be a */
    /* duplicate connection */
    do{
        B = GetRandomRoom(list);
    } while(CanAddConnectionFrom(B) == 0 || IsSameRoom(A, B) == 1 || ConnectionAlreadyExists(A, B) == 1);

    /* connects the rooms if all the tests are passed */ 
    ConnectRoom(A, B);
}

int main(int argc, char *argv[]){
    /* seeding the random number generator */    
    srand(time(NULL)); 
    
    /* creates a string variable to store the name of the folder we want to create. Name includes PID */ 
    char dirName[50];
    memset(dirName, '\0', 50); 
    sprintf(dirName, "hawkesc.rooms.%d", (int)getpid());

    /* creates a directory using the string we just created above */ 
    int result;
    result = mkdir(dirName, 0755);
    assert(result == 0);
    
    /* creates an array to hold pointers to each room we are about to create */ 
    struct room* list[7]; 
    
    /* going to fill an array with unique random numbers. Since the names of the rooms are */
    /* hard coded, filling an array with random numbers that correspond to the indexes */
    /* of the room names is a good way to acheive the random room/connection/type requirement. */
    int randNums[7];
    memset(randNums, -1, sizeof(randNums)); 
    
    int i, j, count, found; 
    i = 0;
    count = 1; 
    
    /* this is the loop I created to fill the array with unique random numbers between 0 and 9 */ 
    while(i == 0){ 
        found = 0; 
        int temp = rand()%10;
        
        /* checks each random number against numbers in array to ensure unique numbers */ 
        for(j = 0; j < count; j++){
            if(temp == randNums[j]){
                found = 1;    
                j = count;
            } 
        }
        /* if the number just generated does not match the numbers in the array, it is added in */
        /* the next available slot */
        if(found != 1){
            randNums[count-1] = temp;
            count++; 
        }
        /* used to escape the loop when the array is full of unique numbers */ 
        if(count == 8){
            i = 1;
        }
    }
    
    /* loop is used to create each room container on the heap and initialize their values. */ 
    for(i = 0; i < 7; i++){
        list[i] = (struct room*)calloc(1, sizeof(struct room)); 
        
        /* randomly assigns room name using the array of random numbers */
        list[i]->name = roomNames[randNums[i]];   
        list[i]->numCon = 0;
         
        /* first room is the assigned the start room. Since the first room was assigned a random */
        /* name, the start room will vary everytime the program is run. This continues with */
        /* the other room types as well */ 
        if(i == 0){
            list[i]->roomType = roomTypes[0];
        }else if(i == 6){
            list[i]->roomType = roomTypes[2];
        }else{
            list[i]->roomType = roomTypes[1];
        }
    }
    
    /* this loop utilizes most of the functions created above to assign random room connections */
    /* to every room in the array of rooms. Loop will run until all connections are made. */
    while(!IsGraphFull(list)){
        AddRandomConnection(list);
    }

    /* this section is used to write the information contained in each room container to */
    /* a unique file. The 7 individual files will be in the directory we created earlier */
    for(i=0; i < 7; i++){
        ssize_t nwritten; 
        char fileName[50];
        char roomName[20];
        char connect[25];
        char roomT[25];
        memset(fileName, '\0', 50);
        /* file name for each room is created */ 
        sprintf(fileName, "%s/%s_room", dirName, list[i]->name);

        /* the filename that was just created is used to create and open the file */ 
        int fileDescriptor = open(fileName, O_WRONLY | O_CREAT, 0644);
        if(fileDescriptor < 0){
            printf("Error creating file\n");
        }
        
        /* creates the formatted string containing the current room name and writes it to the file */ 
        sprintf(roomName, "ROOM NAME: %s\n", list[i]->name); 
        nwritten = write(fileDescriptor, roomName, strlen(roomName) * sizeof(char));

        /* will loop for the number of connections in current room and create a formatted string for */
        /* each connection to be written to the file */
        for(j = 0; j < list[i]->numCon; j++){ 
            sprintf(connect, "CONNECTION %d: %s\n", (j+1), list[i]->connections[j]);
            nwritten = write(fileDescriptor, connect, strlen(connect) * sizeof(char)); 
        }
        
        /* creates a formatted string for the current room type and writes it to the file */ 
        sprintf(roomT, "ROOM TYPE: %s\n", list[i]->roomType);
        nwritten = write(fileDescriptor, roomT, strlen(roomT) * sizeof(char));
        
        close(fileDescriptor); 
    }
    
    /* memory cleanup for the room containers created on the heap */ 
    for(i = 0; i < 7; i++){
       free(list[i]);
    }
    
    return 0;
}

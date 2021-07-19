#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

/* function used to create a key file of random character. Characters must be A-Z or space */
int main(int argc, char *argv[]){
    
    srand(time(NULL)); 
   
    /* converts the user provided arguement stating the desired number of characters */
    /* into an integer */
    int characters = atoi(argv[1]); 
    char key[characters+2];  
    
    /* executes if key is to be printed to stdout */ 
    if(argc == 2){
        int i; 
        for(i = 0; i < characters; i++){
            key[i] = rand()%27 + 65;
            if(key[i] == 91){
                key[i] = 32;
            }
        }
        /* newline added to end, null terminated and then printed */ 
        key[characters] = '\n'; 
        key[characters+1] = '\0'; 
        printf("%s", key); 
        fflush(stdout); 
        
    /* executes if the key is to be saved in a file */ 
    }else if(argc == 4 && argv[2][0] == '>'){
        int newFD; 
        
        /* file is opened for writing. Create a new one if not found */ 
        newFD = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(newFD < 0) perror("Open file failure"); exit(1); 
        
        int i; 
        for(i = 0; i < characters; i++){
            key[i] = rand()%27 + 65;
            if(key[i] == 91){
                key[i] = 32;
            }
        }
        key[characters] = '\n'; 
        key[characters+1] = '\0'; 
        
        /* write the created characters into the file, along with newline and null term */ 
        i = write(newFD, key, (characters+2)); 
        
        if(i < 0) perror("Error writing to file"); exit(1); 
        
        close(newFD); 
        
    }
    
    return 0;
}

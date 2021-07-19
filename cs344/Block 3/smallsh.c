/* Clinton Hawkes */
/* Program 3 */
#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


/* flag indicating if background processes are enabled or not. 1 = enabled */
volatile sig_atomic_t bgEnabled = 1;

/* this is the sig handler in the parent(shell) for the SIGTSTP signal. */
void catchSIGTSTP(int sig){
    /* each time the signal is caught, the flag is toggled on/off by bit manipulation */ 
    bgEnabled ^= 1;
    
    char* message1 = "\nEntering foreground-only mode (& is now ignored)\n"; 
    char* message2 = "\nExiting foreground-only mode\n";
    
    /* determines what to print to the screen depending on the bgEnabled flag */ 
    if(bgEnabled == 0){ 
        write(STDOUT_FILENO, message1, 50);
        fflush(stdout); 
    }else{
        write(STDOUT_FILENO, message2, 30);
        fflush(stdout);
    } 
}

/* function used to execute the commands built into bash. If there is an error with the */
/* command, the allocated memory for the line variable is freed and exits 1 */
void execute(char** arguments, char* line){
    if(execvp(*arguments, arguments) < 0){
        perror("Exec failure");
        free(line);
        exit(1);
    }
}

/* found help with this function on stack overflow and geeksforgeeks*/
/* I never thought to manipulate the pointer address of the parameter passed */
/* into the function. I learned more than expected while tracing this. */
char* find_Replace(char* target, char* find, char* replacement){
    /* going to hold the new line created by replacing the $$ */ 
    char* newWord; 
    int i, count = 0; 
    int findLen = strlen(find);
    int repLen = strlen(replacement);

    /* this counts the number of times the "find" parameter is found */
    /* and it counts the number of characters in the string. */
    /* this will visit every character in the string */ 
    for(i = 0; target[i] != '\0'; i++){
        /* returns true if the "find" is found starting with the current character */
        /* being evaluated in the string */
        if(strstr(&target[i], find) == &target[i]){
            /* count holds the number of appearances */ 
            count++;
            /* this moves i past the word that was just found */ 
            i += findLen - 1;
        }
    }

    /* memory allocated for the new string. Large enough to hold the replacement string */ 
    newWord = (char*)malloc(i + count * (repLen - findLen) + 1);
    
    i = 0;
    /* loops until the null terminating 0 is reached at the end of the string */ 
    while(*target){
        /* returns true if the start of the "find" string is located at the current character */ 
        if(strstr(target, find) == target){
            /* copies the replacement word to the new string being built */ 
            strcpy(&newWord[i], replacement);
            i += repLen;
            target += findLen;
        }else{
            /* copies the current character in the input string to the new */ 
            /* and then increments both their tracking variables */ 
            newWord[i++] = *target++;
        }
    }
    
    /* null terminates the new string that has been built and returns it*/ 
    newWord[i] = '\0';
    return newWord; 
} 


/* function is used to check if a process has finished, and prints out the information */
/* regarding the exit method/signal exit */
int checkChild(pid_t pid){
    int childExit;
    pid_t result; 
    
    /* checks the pid of a child to see if it has finished */ 
    result = waitpid(pid, &childExit, WNOHANG);
    
    if(result == -1){
        perror("Error while waiting");
    }
    /* I checked to make sure waitpid returned something greater than 0, meaning the process */
    /* being checked has finished. */
    if(result > 0){ 
        if(WIFEXITED(childExit)){
            /* extracts the exit code from the variable and prints to the screen*/ 
            int exitStatus = WEXITSTATUS(childExit);
            printf("Background pid %d is done: exit value %d\n", pid, exitStatus);
            fflush(stdout);
            /* returning 1 signals the returning function to delete this pid */ 
            return 1; 
        }else if(WIFSIGNALED(childExit)){
            /* extracts the terminating signal code from the variable and prints it out */ 
            int termSignal = WTERMSIG(childExit);
            printf("Background pid %d is done: terminated by signal %d\n", pid, termSignal);
            fflush(stdout);
            /* returning 1 signals the returning function to delete this pid */ 
            return 1;
        }
    } 
    /* the child pid being checked has not finished, so 0 indicates not to delete pid from array */ 
    return 0; 
}


int main(int argc, char *argv[]){
    
    /* container for the SIGTSTP signal handler */ 
    struct sigaction SIGTSTP_action = {{0}};
    /* when SIGTSTP is caught, the catchSIGTSTP function will execute */ 
    SIGTSTP_action.sa_handler = catchSIGTSTP;
    sigfillset(&(SIGTSTP_action.sa_mask)); 
   
    /* sigaction container for used when a signal needs to be ignored */ 
    struct sigaction ignore = {{0}};
    ignore.sa_handler = SIG_IGN;
    sigfillset(&(ignore.sa_mask)); 
    
    /* sigaction container used when the signal default action is desired */ 
    struct sigaction defAction = {{0}};
    defAction.sa_handler = SIG_DFL;
    sigfillset(&(defAction.sa_mask)); 
    
    /* SIGINT is ignored in the parent, and SIGTSTP runs the catchSIGTSTP function */ 
    sigaction(SIGINT, &ignore, NULL); 
    sigaction(SIGTSTP, &SIGTSTP_action, NULL);
    
    int charEntered; 
    int bgGranted = 0; 
    int argCount = 0; 
    int childExit; 
    int unfinished[100] = {0}; 
    int unfinCount = 0; 
    char* input = NULL; 
    char* line = NULL; 
    char* token = NULL; 
    char* prevToken = NULL; 
    char* inRedir = NULL;
    char* outRedir = NULL;
    char* command = NULL; 
    char status[100] = "exit value 0\n"; 
    char* args[515] = {0};
    size_t bufferSize = 0; 
    pid_t spawnpid;
    char parent[20] = {0};
    sprintf(parent, "%d", (int)getpid()); 

    
    /* main loop runs until exit is called */ 
    while(1){ 
        
        /* loop runs after each input is entered and run */ 
        while(1){
            
            /* this checks all the unfinished processes for completion */
            if(unfinCount > 0){ 
                int k;        
                /* checks all positions in the array for finished processes */ 
                for(k = 0; k < 100; k++){
                    if(unfinished[k] != 0){
                       /* checks all array values that are not zero for finish status*/ 
                        if(checkChild((pid_t)unfinished[k])){
                            /* if it finished, this array position is set to 0 */ 
                            unfinished[k] = 0;
                            unfinCount--; 
                        }
                    }
                }
            } 
            
            printf(": ");
            fflush(stdout);
            
            /* gets the input from the user */ 
            charEntered = getline(&input, &bufferSize, stdin);
            /* if error, clear stdin and reset */ 
            if(charEntered == -1){
                clearerr(stdin);
            /* user just pressed enter, so reset */ 
            }else if(charEntered == 1){
                free(input); 
                input = NULL; 
            /* move on to the next step if user entered and input */ 
            }else{
                break;
            }
        }
        
        /* replaces all instances of $$ in user input with the pid of shell */ 
        /* newly created string with replacements is returned to line variable */ 
        line = find_Replace(input, "$$", parent); 
        free(input);
        input = NULL;
        
        /* first argument entered by user is the command */ 
        command = strtok(line, " \n");
        args[0] = command; 
        argCount++; 
        
        /* checks if command is a comment */ 
        if(strstr(command, "#") == command){
            strcpy(command, "#");
        }
        
        /* evaluate the rest of the input if it is not a comment */ 
        if(strcmp(command, "#") != 0){ 
            token = strtok(NULL, " \n");
            /* process string until null terminator is reached */ 
            while(token != NULL){
                /* stdin redirected to argument following < */ 
                if(strcmp(token, "<") == 0){
                    inRedir = strtok(NULL, " \n");
                    args[argCount] = NULL;    
                    argCount++; 
                /* stdout redirected to argument following > */ 
                }else if(strcmp(token, ">") == 0){
                    outRedir = strtok(NULL, " \n");
                    args[argCount] = NULL;    
                    argCount++; 
                /* the rest just ensures correct arguement count limits */ 
                }else{
                    if(argCount < 513){
                        args[argCount] = token;    
                        argCount++; 
                    }else if(argCount == 513 && strcmp(token, "&") == 0){
                        args[argCount] = token;
                        argCount++; 
                    }else{
                        printf("Command has too many arguments");
                        fflush(stdout);
                        argCount = 0;
                        break;
                    } 
                }                    
                /* holds the last argument in the user's input when done */ 
                prevToken = token; 
                token = strtok(NULL, " \n");
            }
            /* toggles the bgGranted flag if the last argument was & */ 
            if(prevToken != NULL && strcmp(prevToken, "&") == 0){ 
                /* deletes the last args element if it is & */  
                args[argCount-1] = NULL; 
                argCount--;  
                
                /* process is background if btEnabled and last element was & */ 
                if(bgEnabled){ 
                    bgGranted = 1; 
                /* not granted if bgEnabled is 0 */    
                }else{ 
                    bgGranted = 0; 
                } 
            }                
            /* logic for the cd command */  
            if(strcmp(command, "cd") == 0){
                /* change pwd to HOME if there is just cd command */ 
                if(argCount == 1){
                    chdir(getenv("HOME"));
                /* attempts to change pwd to user path entered */ 
                }else{
                    int res;
                    res = chdir(args[1]);
                    /* if path was invalid, message is printed */ 
                    if(res == -1){
                        printf("Invalid path\n");
                        fflush(stdout);
                    }
                } 
            /* logic for the exit command */ 
            }else if(strcmp(command, "exit") == 0){
                int k = 0; 
                /* loops through all the unfinished processes and issues */
                /* a kill command to them all */
                while(unfinCount > 0){ 
                    if(unfinished[k] != 0){
                        kill(unfinished[k], SIGTERM); 
                        unfinCount--; 
                    }
                    k++; 
                } 
                /* exits the loop for final memory cleanup/exit */ 
                break; 
                
            /* logic for the status command */ 
            }else if(strcmp(command, "status") == 0){
                /* prints the string holding the exit status of the last foreground process */ 
                printf("%s", status);
                fflush(stdout);               
                
            /* if it made it this far, a child process needs to be spawned for exec() */
            /* of a command */
            }else{
                
                /* new child process is created(forked) */ 
                spawnpid = fork(); 
                
                switch(spawnpid){
                    
                    /* if fork encountered an error */ 
                    case -1: 
                        perror("Fork Failed");
                        exit(1);
                        break;
                        
                    /* This section is for the child process */ 
                    case 0:
                        /* children processes ignore SIGTSTP */ 
                        sigaction(SIGTSTP, &ignore, NULL); 
                        
                        /* The following code is if the child is in the background */ 
                        if(bgGranted == 1){
                            printf("Background process is running"); 
                            /* redirects stdin to file if provided, /dev/null if no */
                            /* file was provided */
                            if(inRedir){
                                int inFD;
                                inFD = open(inRedir, O_RDONLY); 
                                if(inFD == -1){
                                    perror("Cannot open file for input");
                                    exit(1);
                                }else{
                                    dup2(inFD, 0);
                                } 
                            /* no file provided */ 
                            }else{
                                int inFD = open("/dev/null", O_RDONLY); 
                                dup2(inFD, 0);
                            }
                            /* redirects stdout to a file if one was provided, or to */ 
                            /* /dev/null if no dile was provided */
                            if(outRedir){
                                int outFD;
                                /* opens provided file with write only */ 
                                outFD = open(outRedir, O_WRONLY | O_TRUNC | O_CREAT, 0644); 
                                if(outFD == -1){
                                    perror("Cannot open file for output");
                                    exit(1);
                                }else{
                                    dup2(outFD, 1);
                                } 
                            /* no file was provided, so redirect stdout to /dev/null */ 
                            }else{
                                int outFD = open("/dev/null", O_WRONLY); 
                                dup2(outFD, 1);
                            }
                            
                            /* executes the user's command/arguments using the execute function */                            
                            execute(args, line);
                        }
                        
                        /* The following code is if the child is in the foreground */ 
                        else{
                            /* foreground children should receive the SIGINT signal */ 
                            /* and react in default manner */
                            sigaction(SIGINT, &defAction, NULL); 
                            
                            /* if user provide a file for stdin redirection, the following executes */ 
                            if(inRedir){
                                int inFD;
                                /* opens the file for stdin with readonly permissions */ 
                                inFD = open(inRedir, O_RDONLY); 
                                if(inFD == -1){
                                    perror("Cannot open file for input");
                                    exit(1);
                                /* if no error opening file, stdin is redirected to file */ 
                                }else{
                                    dup2(inFD, 0);
                                } 
                            } 
                            /* if user provides a file for stdout redirection, the following executes */ 
                            if(outRedir){
                                int outFD;
                                /* provided filename is opened for writing */ 
                                outFD = open(outRedir, O_WRONLY | O_CREAT | O_TRUNC, 0644); 
                                if(outFD == -1){
                                    perror("Cannot open file for output");
                                    exit(1);
                                /* if no error opening file, stdout is redirected to file */ 
                                }else{
                                    dup2(outFD, 1);
                                } 
                            }
                            
                            /* executes the user's command/arguments using the execute function */                            
                            execute(args, line);                            
                        } 
                        break; 
                        
                    /* the following is for the parent process after the child was forked off */ 
                    default:
                        
                        /* the following runs if the child that was forked runs in the background */
                        if(bgGranted){
                            /* the child pid is printed */ 
                            printf("Background pid is %d\n", spawnpid);
                            fflush(stdout);
                            
                            int j; 
                            j = 0; 
                            
                            /* searches for an empty location in the array holding unfinished processes */ 
                            while(unfinished[j] != 0){
                                j++;
                            }
                            
                            /* puts the unfinished process pid in the array */
                            unfinished[j] = (int)spawnpid;      
                            unfinCount++; 
                        }
        
                        /* the following will run if the child that was forked runs in the foreground */ 
                        else{
                            /* the parent process must wait for the foreground process to finish */ 
                            /* the following 4 lines sets up a sigprocmask so the parent can block out */ 
                            /* the SIGTSTP signal until the foreground processes finishes. That way the */
                            /* waitpid() is not interupted by the signal */
                            sigset_t mask;
                            sigemptyset(&mask);
                            sigaddset(&mask, SIGTSTP);
                            sigprocmask(SIG_BLOCK, &mask, NULL);
                            
                            /* parent waits for the foreground process to finish */ 
                            spawnpid = waitpid(spawnpid, &childExit, 0);
                            
                            /* the sigprocmask now unblocks the SIGTSTP signal so the parent can receive */
                            /* any that where sent while it was blocked and in the future */
                            sigprocmask(SIG_UNBLOCK, &mask, NULL);
                            memset(status, '\0', sizeof(status) * sizeof(char)); 
                            
                            /* waitpid returns a -1 if there was an error */ 
                            if(spawnpid == -1){
                                perror("Error while waiting");
                            }
                            /* if the process exited without a signal */  
                            if(WIFEXITED(childExit)){
                                /* the macro run on childExit returns the exit code */ 
                                int exitStatus = WEXITSTATUS(childExit);
                                sprintf(status, "exit value %d\n", exitStatus);
                                
                            /* if the process was terminated by a signal, the following runs */ 
                            }else if(WIFSIGNALED(childExit)){
                                /* the macro returns the signal code use to terminate process */ 
                                int termSignal = WTERMSIG(childExit);
                                sprintf(status, "terminated by signal %d\n", termSignal);
                                /* signal termination information is immediately printed to screen */ 
                                printf("%s", status);
                                fflush(stdout);
                            }
                        }
                }
            }
        }
        
        /* the following block of code resets all the variables for the next run */ 
        free(line); 
        line = NULL; 
        bgGranted = 0;
        prevToken = NULL; 
        command = NULL;
        argCount = 0;
        inRedir = NULL;
        outRedir = NULL;
        int i; 
        /* resets all the elements in the args array back to NULL */ 
        for(i = 0; i < sizeof(args)/sizeof(char*); i++){
            args[i] = NULL;
        }
    }
    /* the next two lines are for final memory cleanup */ 
    free(line); 
    line = NULL; 
    
    return 0;
}

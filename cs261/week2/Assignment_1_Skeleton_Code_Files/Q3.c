/* CS261- Assignment 1 - Q.3*/
/* Name: Clinton Hawkes
 * Date: July 3, 2019
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>


char toUpperCase(char ch){
  /*Convert ch to upper case, assuming it is in lower case currently*/
    if(ch >= 'a' && ch <= 'z'){ 
        return ch - 32; 
    }
    else{
        return ch;
    }
}

char toLowerCase(char ch){
  /*Convert ch to lower case, assuming it is in upper case currently*/                          
    if(ch >= 'A' && ch <= 'Z'){ 
        return ch + 32; 
    } 
    else{ 
        return ch; 
    } 
}

int stringLength(char s[]) {
   /*Return the length of the string*/
    int counter = 0;

    while(s[counter] != '\0'){
        counter++;
    }
    return counter;
}

void camelCase(char* word){
	/*Convert to camelCase*/
    char* temp = (char*)malloc(sizeof(char)*50);
    int count = 0; 

    for(int i = 0; i < stringLength(word); i++){
        if(word[i]=='_'){
            word[i+1] = toUpperCase(word[i+1]);
             
        }
        else if((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z')){
            temp[count] = word[i];
            count++;
        }
    }	
    for(int j = 0; j < count; j++){
        word[j] = temp[j];
    }
    word[count] = '\0';    
    
    free(temp); 
    temp = NULL; 
}

int convertString(char* input){

    char* holder = (char*)malloc(sizeof(char)*50); 
    int alpha = 0;
    int symbol = 0; 
    int num = 0; 
     
    /* Converts input string to correct format for camelCase() and stores it in holder variable */ 
    for(int i = 0; i < stringLength(input); i++){
        //if the current character is a letter, it is copied to the holder string 
        if((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')){
            alpha = 1;
            holder[num] = toLowerCase(input[i]);
            num++;
        }
        // copies '_' to holder if a letter has already appeared and the last char copied is not '_' 
        else if(input[i] == '_' && alpha == 1 && holder[num-1] != '_'){
            holder[num] = '_';
            symbol = 1; 
            num++;
        }
        // copies '_' to holder if a letter has already appeared and the last char copied is not '_' 
        else if(input[i] == ' ' && alpha == 1 && holder[num-1] != '_'){
            holder[num] = '_';
            symbol = 1; 
            num++;
        } 
        // copies '_' to holder if a letter has already appeared and the last char copied is a lower
        // case letter. This allows numbers and symbols to count as spaces between words.
        else if(alpha == 1 && (holder[num-1] >= 'a' || holder[num-1] <= 'z')){
            holder[num] = '_';
            symbol = 1; 
            num++;
        } 
    }
    holder[num] = '\0';  
    num++; 
    
    /* Checks to see if string is valid. Prints error if string is invalid */ 
    if(alpha == 0 || symbol == 0){
        printf("Invalid input string\n");
        free(input);
        input = NULL;
        free(holder);
        holder = NULL;
        return 0;
    }
    
    /* Copies converted string to the input variable passed to function */ 
    for(int k = 0; k < num; k++){
        input[k] = holder[k];
    }
    
    free(holder); 
    holder = NULL; 
    
    return 1; 
}

int main(){
    
    char* sptr = (char*)malloc(sizeof(char)*50); 
    
    
	/*Read the string from the keyboard
    Found my scanf code idea from the link below. The posting user was SVA.
    www.stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf* sptr = NULL; */
    printf("Please enter test string: ");
    if(!scanf("%49[^\n]s", sptr)){               //program will not accept empty strings
        printf("Invalid input string\n");
        free(sptr);
        sptr = NULL;
        return 0;
    }

    /* If the string was found to be invalid in convertString(), the program terminates. */ 
    if(!convertString(sptr)){
        return 0;
    }
	
	/*Call camelCase*/
    camelCase(sptr);	
    
	/*Print the new string*/
    printf("Lower camel case version: %s\n", sptr); 
    
    free(sptr);
    sptr = NULL;
	
	return 0;
}

/* CS261- Assignment 1 - Q.1*/
/* Name: Clinton Hawkes
 * Date: July 3, 2019
 * Solution description:
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
    struct student* temp = (struct student*)malloc(sizeof(struct student) * 10);

     /*Return the pointer*/
    return temp; 
}

void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
    IDs being between 1 and 10, scores between 0 and 100*/
    int idNum[] = {1,2,3,4,5,6,7,8,9,10}; 
    int randNum;
    int temp; 

    /* Using the Fisher Yates shuffle included in the spec sheet */ 
    for(int i = 9; i >= 0; i--){
        randNum = rand()%(i+1);
        temp = idNum[i];
        idNum[i] = idNum[randNum];
        idNum[randNum] = temp;
    }
    
    for(int j = 0; j < 10; j++){
        students[j].id = idNum[j];
        students[j].score = rand()%101;
    }
}

void output(struct student* students){
     /*Output information about the ten students in the format: */
    printf("==STUDENTS==\nID    SCORE\n"); 
     
    for(int i = 0; i < 10; i++){
        printf("%d     %d\n", students[i].id, students[i].score);
    }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the 
    ten students*/
    int sum = 0;
    int min = 100;
    int max = 0;

    for(int i = 0; i < 10; i++){
        sum += students[i].score;
        if(students[i].score > max){
            max = students[i].score;
        }
        if(students[i].score < min){
            min = students[i].score;
        }
    } 
    printf("==SCORES==\nMinimum: %d\nMaximum: %d\nAverage: %f\n", min, max, (sum/10.0)); 
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
    if(stud != 0){ 
        free(stud); 
    } 
}

int main(){
    
    srand(time(0));  
    struct student* st = 0;
    
    /*Call allocate*/
    st = allocate(); 
    
    /*Call generate*/
    generate(st); 
    
    /*Call output*/
    output(st); 
    
    /*Call summary*/
    summary(st); 
    
    /*Call deallocate*/
    deallocate(st); 

    return 0;
}


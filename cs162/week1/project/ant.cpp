/*******************************************************************************    
** Program Name:Langton's Ant
** Name:        Clinton Hawkes
** Date:        04/08/2019
** Description: Implementation file for the Ant class. Contains the logic for 
                the constructor, destructor, and all functions used by the 
                class. Detailed description of each function can be found
                below. 
*******************************************************************************/
#include "ant.hpp"
#include <iostream>

//constructor initializes all object variables to zero. ***except board***
Ant::Ant(){
    
    antXCoord = 0;
    antYCoord = 0;
    numRow = 0;
    numCol = 0;
    numSteps = 0;
    orientation = 0;
}

//destructor deletes memory created by createBoard() function
Ant::~Ant(){
     
    //deletes the dynamically allocated memory used by the simulation board 
    for(int z = 0; z < numRow; z++){
        delete [] board[z];
    }
    delete [] board;
    board = nullptr;
}

//setter for Ant X coordinate
void Ant::setAntX(int x){
    antXCoord = x;
}

//getter for Ant X coordinate
int Ant::getAntX(){
    return antXCoord;
}

//setter for Ant Y coordinate
void Ant::setAntY(int y){
    antYCoord = y;
}

//getter for Ant Y coordinate
int Ant::getAntY(){
    return antYCoord;
}

//setter for Ant orientation
void Ant::setAntOrient(int way){
    orientation = way;
}

//getter for Ant orientation
int Ant::getAntOrient(){
    return orientation;
}

//setter for board number of rows
void Ant::setNumRow(int rows){
    numRow = rows;
}

//getter for board number of rows
int Ant::getNumRow(){
    return numRow;
}

//setter for board number of columns
void Ant::setNumCol(int cols){
    numCol = cols;
}

//getter for board number of columns
int Ant::getNumCol(){
    return numCol;
}

//setter for number of steps to be taken
void Ant::setNumSteps(int steps){
    numSteps = steps;
}

//getter for number of steps to be taken
int Ant::getNumSteps(){
    return numSteps;
}

/*******************************************************************************
** Description: function dynamically allocates a 2d array of chars which is
                used as the game board. The size of the board is determined by
                numRow and numCol info obtained from the user. After the array 
                is created, it is filled with ' '
*******************************************************************************/
void Ant::createBoard(){
    
    //2d array is created dynamically 
    board = new char*[numRow];
        for(int i = 0; i < numRow; i++){
            board[i] = new char[numCol];
        }

    //2d array is filled with spaces 
    for(int a = 0; a < numRow; a++){
        for(int b = 0; b < numCol; b++){
            board[a][b] = ' ';
        }
    }
}


/*******************************************************************************
** Description: function prints the 2d array named "board" to the console. It
                also prints the Ant's location on the game board. The Ant's 
                location is shown using *
*******************************************************************************/
void Ant::printBoard(){
    
    //loops through each location in the 2d array printing their value 
    for(int m = 0; m < numRow; m++){
        for(int n = 0; n < numCol; n++){
            //will print * if the Ant's coordinates match current array location 
            if(m == antXCoord && n == antYCoord){
                std::cout << '*';
            } 
            else{
                std::cout << board[m][n];
            } 
        }
        std::cout << std::endl;
    }
}


/*******************************************************************************
** Description: function turns Ant 90 degrees to the right if it is on a white
                location when it is called. Function turns Ant 90 degrees to 
                the left if it is on a black location when it is called.
                ***adding 5 to orient and then taking the modulus is same as +1
                ***adding 3 to orient and then taking the modulus is same as -1
                orientation = {west=0, north=1, east=2, south=3}
*******************************************************************************/
void Ant::changeOrient(){

    //turn Ant 90 degrees right when on white 
    if(board[antXCoord][antYCoord] == ' '){
        orientation = (orientation + 5)%4;
    } 
    //turns Ant 90 degrees left when on black 
    else{
        orientation = (orientation + 3)%4;
    } 
} 


/*******************************************************************************
** Description: function changes the color of the array location currently 
                occupied by the Ant. The color is changed from white to black, 
                or from black to white. Which ever is the opposite of its 
                current color.
*******************************************************************************/
void Ant::changeColor(){
    
    if(board[antXCoord][antYCoord] == ' '){
        board[antXCoord][antYCoord] = '#';
    } 
    else{
        board[antXCoord][antYCoord] = ' ';
    } 
}


/*******************************************************************************
** Description: function uses the Ant's current orientation to determine how
                to advance "forward" one space. 
                orientation = {west=0, north=1, east=2, south=3}
                If Ant facing north, it moves up one row. If Ant is facing
                east, it moves one column to the right... 
*******************************************************************************/
void Ant::advance(){
    
    switch(orientation){

        case 0: antYCoord -= 1;     //facing west, move one column left
                break;
        case 1: antXCoord -= 1;     //facing north, move one row up
                break;
        case 2: antYCoord += 1;     //facing east, move one column right    
                break;
        case 3: antXCoord += 1;     //facing south, move one row down
                break;
    }
    
   //checks all four walls against Ant's location. If Ant moves out of bounds,
   //it is transferred to the opposite side of the board. 
   if(antYCoord == (numCol)){
       antYCoord = 0;
   } 
   else if(antYCoord == -1){
       antYCoord = (numCol - 1);
   } 
   else if(antXCoord == numRow){
       antXCoord = 0;
   } 
   else if(antXCoord == -1){
       antXCoord = (numRow - 1);
   } 
}

/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        03/06/2019
** Description: File containing logic for the constructors and functions used
                by the SBoard class. 
*******************************************************************************/

#include "SBoard.hpp"
#include <fstream>
#include <cmath>
//#include <iostream>       //used for testing

SBoard::SBoard(){
    
    tokenCount = 0;         //initializes token counter to 0 
    
    for(int row = 0; row < 10; row++){
        for(int col = 0; col < 10; col++)
            grid[row][col] = '.';
    } 
}

/*******************************************************************************
** Description: Function takes in two ints as arguments that represent the 
                coordinates where a token should be placed. Token is place at   
                the coordinates if it passes validation.
*******************************************************************************/
int SBoard::placeToken(int row, int col){
    
    if(grid[row][col] == 'x' || row < 0 || row > 9 || col < 0 || col > 9)
        return -1;
    
    grid[row][col] = 'x';
    tokenCount++; 
    
    return countSquare(row, col);     //returns the number of squares completed by token
}                           //that was just placed


/*******************************************************************************
** Description: 
*******************************************************************************/

int SBoard::countSquare(int r, int c){
    
    int sqrComplete = 0;    //initializes counter for squares completed
    
    for(int i = 0; i < 10; i++){
        int diff = std::abs(r - i);
        if(grid[i][c] == 'x' && i != r){
           if(diff <= c){
                if(grid[r][c - diff] == 'x'){
                    if(grid[i][c - diff] == 'x'){
                        sqrComplete++;}}}
            if(diff <= (9 - c)){
                if(grid[r][c + diff] == 'x'){
                    if(grid[i][c + diff] == 'x'){
                        sqrComplete++;}}}}
    } 
    return sqrComplete; 
}


/*******************************************************************************
** Description: Function takes in filename as a string argument and places 
                tokens on grid in specified coordinates contained in file.
*******************************************************************************/
void SBoard::readPlacementsFromFile(std::string inputFile){
    
    int x, y;                   //declare variables to hold x and y coords 
    std::ifstream readFile;     //declare ifstream variable for input file
    
    readFile.open(inputFile);

    while(readFile >> x >> y)
        placeToken(x,y);

    readFile.close();
}

/*******************************************************************************
** Description: Getter function returns total number of tokens placed
*******************************************************************************/
int SBoard::getNumTokens(){
    
    return tokenCount;
}

/*************** Following functions are used for testing *******************
  
void SBoard::printBoard(){
    for(int row = 0; row < 10; row++){
        for(int col = 0; col < 10; col++)
            std::cout  << " " << grid[row][col] << " ";
        std::cout << std::endl; 
    }
}

void SBoard::removeToken(int x, int y){
    grid[x][y] = '.';
}

*************** Alternate logic for finding completed squares ***************

    for(int r = 0; r < 10; r++){
        for(int c = 0; c < 10; c++){
            if(grid[r][c] == 'x'){
                if((r+c)==(row+col) || (r-c)==(row-col)){
                    if(grid[r][col] == 'x' && grid[row][c] == 'x'){
                        if(r != row && c != col)
                            sqrComplete++;}}}}} 
*/    

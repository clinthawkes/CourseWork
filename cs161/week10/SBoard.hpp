/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        03/06/2019
** Description: Header file for the SBoard class. Contains the variables used
                by the class, as well as the constructor/function prototypes.
*******************************************************************************/

#ifndef SBOARD_HPP
#define SBOARD_HPP
#include <string>

class SBoard
{
    private:
        int tokenCount;         //declares int variable for counting tokens
        char grid[10][10];      //declares 2d array of chars
        int countSquare(int, int); 

    public:
        SBoard();
        int placeToken(int, int);
        void readPlacementsFromFile(std::string); 
        int getNumTokens();
        //void printBoard();            //function for testing
        //void removeToken(int,int);    //function for testing 
};
#endif

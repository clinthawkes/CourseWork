/**************************************************************************************************
** Program Name:Predator/Prey Game
** Author:      Clinton Hawkes
** Date:        04/23/2019
** Description: This is the inplementation file for the Ant class. It contains all the functions
                needed to make the "Ant" move and breed. Ant is derived from the Critter class,
                so it inherits the Age, Row, and Column variables, as well as the functions
                move, breed and type. Additional details about the variables and functions of
                the Ant class can be found below.
**************************************************************************************************/

#include "Ant.hpp"
#include "Critter.hpp"
#include "Point.hpp"
#include <cstdlib>
#include "Gameboard.hpp"

//default constructor
Ant::Ant() : Critter() {
    setAge(0);
    setRow(0);              //may cause problems. Always use constructor with arguments
    setCol(0);              //may cause problems. Always use constructor with arguments
    this->board = nullptr;
}

//constructor with two arguments
Ant::Ant(Point &point, Gameboard* board) : Critter(point) {
//	std::srand(std::time(0));
	this->board = board;
}


/**************************************************************************************************
** Description: Function overrides the virtual function move() in Critter. This is the function
                that is responsible for the movement of the ants. First the age of the ant is
                incremented when the function is called. Next a random number between 0 and 3 is
                generated. This number determines what direction the ant is going to move.
                0=up, 1=right, 2=down, 3=left If the direction chosen is not a valid move, the ant
                stays put.
**************************************************************************************************/
Point Ant::move(){

    //creates Point object with same coordinates as the ant
    Point point(row, column);

    age++;          //increases age of ant at the start of each move

    int random = rand()%4;      //genterates random number between 0 and 3

    //0 = up  |  1 = right  |  2 = down  |  3 = left
    switch(random){

            //Ant moves up one cell as long as it passes the tests. If it doesn't pass, ant doesn't move.
            case 0: {
                    point.moveUp();

                    if(board->isValid(point) && board->isEmpty(point)){
                        setOldRow(row);             //updates old row with previous coordinates
                        row = point.getY();         //updates ant row coordinate if it was able to move
                        setOldColumn(column);       //updates old col with previous coordinates
                        column = point.getX();      //updates ant col coordinate if it was able to move
                        return point;
                    }
                    break;
            }

            //Ant moves right one cell as long as it passes the tests. If it doesn't pass, ant doesn't move.
            case 1: {
                    point.moveRight();

                    if(board->isValid(point) && board->isEmpty(point)){
                        setOldRow(row);             //updates old row with previous coordinates
                        row = point.getY();         //updates ant row coordinate if it was able to move
                        setOldColumn(column);       //updates old col with previous coordinates
                        column = point.getX();      //updates ant col coordinate if it was able to move
                        return point;
                    }
                    break;
            }

            //Ant moves down one cell as long as it passes the tests. If it doesn't pass, ant doesn't move.
            case 2: {
                    point.moveDown();

                    if(board->isValid(point) && board->isEmpty(point)){
                        setOldRow(row);             //updates old row with previous coordinates
                        row = point.getY();         //updates ant row coordinate if it was able to move
                        setOldColumn(column);       //updates old col with previous coordinates
                        column = point.getX();      //updates ant col coordinate if it was able to move
                        return point;
                    }
                    break;
            }

            //Ant moves left one cell as long as it passes the tests. If it doesn't pass, ant doesn't move.
            case 3: {
					point.moveLeft();

                    if(board->isValid(point) && board->isEmpty(point)){
                        setOldRow(row);             //updates old row with previous coordinates
                        row = point.getY();         //updates ant row coordinate if it was able to move
                        setOldColumn(column);       //updates old col with previous coordinates
                        column = point.getX();      //updates ant col coordinate if it was able to move
                        return point;
                    }
                    break;
			}
    }

    //if randomly chosen cell was not valid, (-1,-1) is returned and ant does not move
    point.setX(-1);
    point.setY(-1);
    return point;
}


/**************************************************************************************************
** Description: Function overrides the breed() function in Critter class. This is the function that
                controls the breeding of the ant. First the function checks to see if the ant is
                at least 3 years old. If the ant is 3 years old, the function checks the north,
                south, east and west cells to see if they are open/valid. If none of the directions
                are open/valid, the ant does not breed. If at least one of the directions is open
                and valid, the ant will choose one of the directions randomly and create a new ant
                obect in the cell. The new ant's location is passed back to the gameboard.
**************************************************************************************************/
Critter* Ant::breed(){

    Point point(-1, -1);
    bool state = false,
         north = false,
         east = false,
         south = false,
         west = false;

    //if age is less than 3, no calculations are done and a nullptr is returned
    if(age < 3){
        return nullptr;
    }

    //sets point to current ant location
    point.setX(column);
    point.setY(row);

    //checks cell above current ant location to see if it is a valid location and empty
    point.moveUp();
    if(board->isValid(point) && board->isEmpty(point)){
        north = true;
        state = true;
    }

    //checks cell to the right of the current ant location to see if it is a valid location and empty
    point.moveDown();
    point.moveRight();
    if(board->isValid(point) && board->isEmpty(point)){
        east = true;
        state = true;
    }

    //checks cell below the current ant location to see if it is a valid location and empty
    point.moveLeft();
    point.moveDown();
    if(board->isValid(point) && board->isEmpty(point)){
        south = true;
        state = true;
    }

    //checks cell to the left of the current ant location to see if it is a valid location and empty
    point.moveUp();
    point.moveLeft();
    if(board->isValid(point) && board->isEmpty(point)){
        west = true;
        state = true;
    }

    point.moveRight();      //returns point to it's intial coordinates

    //if state == false this far in, there were no valid cells for the ant to breed. nullptr is returned.
    if(state == false){

        return nullptr;
    }

    //loop will run until a random valid location is chosen for breeding
    while(state == true){

        int random = rand()%4;      //random number between 0 and 3 generated

        // 0 = cell above  |  1 = cell right  |  2 = cell below  | 3 = cell left
        switch(random){

            //ant breeds into cell above it. If cell is not valid or not empty, another cell is chosen.
            case 0: if(north){
                        point.moveUp();
                        state = false;
                    }
                    break;

            //ant breeds into cell to the right of it. If cell is not valid or not empty, another cell is chosen.
            case 1: if(east){
                        point.moveRight();
                        state = false;
                    }
                    break;

            //ant breeds into cell below it. If cell is not valid or not empty, another cell is chosen.
            case 2: if(south){
                        point.moveDown();
                        state = false;
                    }
                    break;

            //ant breeds into cell to the left of it. If cell is not valid or not empty, another cell is chosen.
            case 3: if(west){
                        point.moveLeft();
                        state = false;
                    }
                    break;
        }
    }
    //reset age to zero if ant is able to breed
    age = 0;

    //pointer to the newly created ant object is returned
    Critter* baby = new Ant(point, board);
    return baby;
}


/**************************************************************************************************
** Description: Function returns the BugType enum designated to the ant class.
**************************************************************************************************/
BugType Ant::getType(){

    return ANT;
}

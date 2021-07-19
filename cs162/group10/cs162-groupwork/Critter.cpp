/******************************************************************************
 * Program Name: Critter.cpp - Predator-Prey Game (Group Project)
 * Author: Victoria Dmyterko
 * Date: 4/29/2019
 * Description: This is the source file for the Critter class. This is the base
 *              class for the derived classes Ant and Doodlebug.
 *****************************************************************************/
#include "Critter.hpp"
#include "Point.hpp"

/******************************************************************************
 * Critter::Critter()
 * This is the default constructor for the class. This sets everything to zero
 * and sets the board to nullptr.
 *****************************************************************************/
Critter::Critter()
{
   setAge(0);
   setRow(-1);
   setCol(-1);
}

/******************************************************************************
 * Critter::Critter(int, int, Gameboard*)
 * This is the three parameter constructor for the class. This sets the member
 * variables equal to the arguments passed to it.
 *****************************************************************************/
Critter::Critter(Point &point)
{
   setAge(0);
	 setRow(point.getY());
	 setOldRow(point.getY());
	 setCol(point.getX());
	 setOldColumn(point.getX());
}

/******************************************************************************
 * Critter::move()
 * This method moves the critter on the gameboard randomly. In the Critter
 * class the method simply returns a Point object with value (-1,-1). This
 * method is meant to be overridden in the derived classes Ant and Doodlebug.
 * This method takes no arguments.
 *****************************************************************************/
Point Critter::move()
{
   //Create a Point object with row = -1 and column = -1.
   Point point(-1, -1);
   return point;
}

/******************************************************************************
 * Critter::breed()
 * This method simulates the critter breeding. It is supposed to create a new
 * critter and place it in an adjacent, empty location. Since this method is
 * supposed to be overridden in the Ant and Doodlebug class the Critter version
 * of this method simply returns a Point object with value (-1, -1). This
 * method takes no arguments.
 *****************************************************************************/
Critter* Critter::breed()
{
   //Create a Point object with row = -1 and column = -1.
   Point point(-1, -1);
   return nullptr;
}

/******************************************************************************
 * Critter::starve()
 * This method simulates the critter starving. It is supposed to check if the
 * critter starved after a specified number of steps then tell the gameBoard
 * to remove the critter at the returned Point. Since this method is meant to
 * be overridden in the Doodlebug class the Critter version of the method
 * simply returns a Point object with value (-1, -1). This method takes no
 * arguments.
 *****************************************************************************/
//Point Critter::starve()
bool Critter::starve()
{
   //Create a Point object with row = -1 and column = -1.
   return 0;
}

/*****************************************************************************
* Critter::getType()
* Returns the type to the calling program. Returns CRITTER.
*****************************************************************************/
BugType Critter::getType()
{
   return CRITTER;
}


//These are the get and set method for the age member variable.
int Critter::getAge()
{
   return age;
}

void Critter::setAge(int ageIn)
{
   age = ageIn;
}

//These are the get and set method for the row member variable.
int Critter::getRow()
{
   return row;
}

void Critter::setRow(int rowIn)
{
   row = rowIn;
}

//These are the get and set method for the column member variable.
int Critter::getCol()
{
   return column;
}

void Critter::setCol(int colIn)
{
   column = colIn;
}

//These are the get and set method for the oldRow member variable.
int Critter::getOldRow(){

    return oldRow;
}

void Critter::setOldRow(int oldR){

    oldRow = oldR;
}

//These are the get and set method for the oldColumn member variable.
int Critter::getOldColumn(){

    return oldColumn;
}

void Critter::setOldColumn(int oldC){

    oldColumn = oldC;
}


/**************************************************************************************************
* Critter::getOldLocation()
* This method returns a Point object with the coordinates of the Critter's old location. This
* method takes no arguments.
**************************************************************************************************/
Point Critter::getOldLocation(){

    Point old(oldRow, oldColumn);
    return old;
}


/**************************************************************************************************
* Critter::getCurrentLocation()
* This method returns a Point object with the coordinates of the Critter's current location. This
* method takes no arguments.
**************************************************************************************************/
Point Critter::getCurrentLocation(){
	Point p(row,column);
	return p;

}

/******************************************************************************
 * Critter::~Critter()
 * This is the destructor for the class. This destructor is declared virtual
 * so that derived class objects can be deleted properly.
 *****************************************************************************/
Critter::~Critter()
{
}

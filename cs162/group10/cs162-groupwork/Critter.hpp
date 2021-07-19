/******************************************************************************
 * Program Name: Critter.hpp - Predator-Prey Game (Group Project)
 * Author: Victoria Dmyterko
 * Date: 4/21/2019
 * Description: This is the header file for the Critter class. This is the base
 *              class for the derived classes Ant and Doodlebug. This contains
 *              declarations for shared member variables, and function
 *              prototypes for the class.
 *****************************************************************************/
#ifndef CRITTER_HPP
#define CRITTER_HPP

#include "Point.hpp"
#include "BugType.hpp"

class Gameboard;

class Critter
{
   protected:
	int age,
	    row,
	    column,
            oldRow,
            oldColumn;

   public:
	//Constructors
	Critter();
	Critter(Point &point);

	//Virtual move method
	virtual Point move();

	//Virtual breed method
	virtual Critter* breed();

	//Virtual starve method
	virtual bool starve();
   
	//BugType method
	virtual BugType getType();

	//Get and set for age variable
	int getAge();
	void setAge(int ageIn);

	//Get and set for row variable
	int getRow();
	void setRow(int rowIn);
	
	//Get and set for old row variable
	int getOldRow();
	void setOldRow(int);

	//Get and set for col variable
	int getCol();
	void setCol(int colIn);
	
	//Get and set for old column variable.
	int getOldColumn();
	void setOldColumn(int);
    
	//getOldLocation method, returns Critter's old location. 
    	Point getOldLocation();
    
	//getCurrentLocation method, returns Critter's new location.
	Point getCurrentLocation();
	
	//Virtual destructor.
	virtual ~Critter();
};

#endif

/*******************************************************************
    Program name: Doodlebug.cpp
    Author: Chen Yan
    Date: 05/08/2019
    Description: This program is specification file implementation for 
                 Doodlebug class. It includes default constructe, 
		 overloading constructor and member functions.
*****************************************************************/
#include "Doodlebug.hpp"
#include <cstdlib>

/**************************************************************************************************
**                              Doodlebug::Doodlebug()
** This is default constructor. It means to initiate the member variables.
**************************************************************************************************/
Doodlebug::Doodlebug() : Critter(){
    
    age = 0;
    starveAge = 0;
    row = 0;
    column = 0;
    this -> board = NULL;
}

/**************************************************************************************************
**             Doodlebug::Doodlebug (int bugRow, int bugCol, Gameboard* board)
** This is overloading constructor. It takes three aruguments and initiate the member variables.
**************************************************************************************************/
Doodlebug::Doodlebug(Point &point, Gameboard* board) : Critter(point){
    
    starveAge = 0;
    this -> board = board;
}

/**************************************************************************************************
**                               Point Doodlebug::move()
** This member function is mean to control the movement of Doodlebug and return as value as Point 
** type. 
**************************************************************************************************/
Point Doodlebug::move(){
    
    Point point(row, column);
    int random = rand()% 4 + 1;
    
    bool state = false,
         north = false,
         east = false,
         south = false,
         west = false;
	
    //move up to check if it's in the boundary and has an ant on it
    point.moveUp();
    if(board->isValid(point) && board->hasAnt(point)){
        north = true;
        state = true;
    }

    //move right to check if it's in the boundary and has an ant on it	 
    point.moveDown();
    point.moveRight();
    if(board->isValid(point) && board->hasAnt(point)){
        east = true;
        state = true;
    }

    //move down to check if it's in the boundary and has an ant on it	
    point.moveLeft();
    point.moveDown();
    if(board->isValid(point) && board->hasAnt(point)){
        south = true;
        state = true;
    }

    //move left to check if it's in the boundary and has an ant on it
    point.moveUp();
    point.moveLeft();
    if(board->isValid(point) && board->hasAnt(point)){
        west = true;
        state = true;
    }

    //move back to original point
    point.moveRight();

    //If adjacent cells do not have ANT 
    if(state == false)
    {
        switch(random){
                        
                case 1: point.moveUp();
                        //move up to check if it's in the boundary and is empty
                        if(board->isValid(point) && board->isEmpty(point)){
                            setOldRow(row);
                            row = point.getY();
                            setOldColumn(column);
                            column = point.getX();
                            //increment steps to breed
			    age++;
			    //increment steps to starve
                            starveAge++;
                            return point;
                        }
                        break;

                case 2: point.moveRight();
                        //move right to check if it's in the boundary and is empty
                        if(board->isValid(point) && board->isEmpty(point)){
                            setOldRow(row);
                            row = point.getY();
                            setOldColumn(column);
                            column = point.getX();
                            age++;
                            starveAge++;
                            return point;
                        }
                        break;

                case 3: point.moveDown();
			//move down to check if it's in the boundary and is empty
                        if(board->isValid(point) && board->isEmpty(point)){
                            setOldRow(row);
                            row = point.getY();
                            setOldColumn(column);
                            column = point.getX();
                            age++;
                            starveAge++;
                            return point;
                        }
                        break;

                case 4: point.moveLeft();
			//move left to check if it's in the boundary and is empty
                        if(board->isValid(point) && board->isEmpty(point)){
                            setOldRow(row);
                            row = point.getY();
                            setOldColumn(column);
                            column = point.getX();
                            age++;
                            starveAge++;
                            return point;
                        }
                        break;
        }
    }

    //If adjecent cells have ANT
    else if(state == true){
	    
        //move up to eat ANT
        if(north == true){
            point.moveUp();
	    //Remove ANT
            board->removeCritter(point);
            setOldRow(row);
            row = point.getY();
	    setOldColumn(column);
            column = point.getX();
            //Reset starve steps
	    starveAge = 0;
            age++;
            return point;
        }
        
	//move right to eat ANT    
        else if(east == true){
            point.moveRight();
            board->removeCritter(point);
            setOldRow(row);
            row = point.getY();
	        setOldColumn(column);
            column = point.getX();
            starveAge = 0;
            age++;
            return point;
        }
	    
        //move down to eat ANT	    
        else if(south == true ){
            //move down to eat ANT 
            point.moveDown();
            board->removeCritter(point);
	        setOldRow(row);
            row = point.getY();
	        setOldColumn(column);
            column = point.getX();
            starveAge = 0;
            age++;
            return point;
        }
	    
        //move left to eat ANT
        else if(west == true){
            point.moveLeft();
            board->removeCritter(point);
		    setOldRow(row);
            row = point.getY();
		    setOldColumn(column);
            column = point.getX();
            starveAge = 0;
            age++;
            return point;
        }
    }
    //If adjacent cells do not have ants and are not empty
    starveAge++; 
    age++; 
    //Doodlebug stay at original point
    point.setX(-1);
    point.setY(-1);
    return point;
}

/**************************************************************************************************
**                                    Doodlebug::breed()
** This member function is mean to control breed method of Doodlebug. 
**************************************************************************************************/
Critter* Doodlebug::breed(){
    
    Point point(row, column);

    bool state = false,
         north = false,
         east = false,
         south = false,
         west = false;

    if(age < 8){
        return nullptr;
    }
    //move up to check if it's in the boundary and is empty for breed
    point.moveUp();
    if(board->isValid(point) && board->isEmpty(point)){
        north = true;
        state = true;
    }
    //move right to check if it's in the boundary and is empty for breed
    point.moveDown();
    point.moveRight();
    if(board->isValid(point) && board->isEmpty(point)){
        east = true;
        state = true;
    }
    
    //move down to check if it's in the boundary and is empty for breed
    point.moveLeft();
    point.moveDown();
    if(board->isValid(point) && board->isEmpty(point)){
        south = true;
        state = true;
    }

    //move left to check if it's in the boundary and is empty for breed
    point.moveUp();
    point.moveLeft();
    if(board->isValid(point) && board->isEmpty(point)){
        west = true;
        state = true;
    }

    point.moveRight();

    //If there is no available cells
    if(state == false){
       return nullptr;
    }

    while(state == true){
        
	//Randomly choose cells to breed
        int random = rand()%4 + 1;

        switch(random){
            
                case 1: if(north == true){
                            point.moveUp();
                            state = false;
                        }
                        break;
                        
                case 2: if(east == true){
                            point.moveRight();
                            state = false;
                        }
                        break;
                        
                case 3: if(south == true){
                            point.moveDown();
                            state = false;
                        }
                        break;
                        
                case 4: if(west == true){
                            point.moveLeft();
                            state = false;
                        }
                        break;
        }
    }
    
    age = 0;
	
    //Dynamiclly allocate space for Doodlebug baby
    Critter* baby = new Doodlebug(point, board);
    return baby;
}

/**************************************************************************************************
**                               Doodlebug::starve()
** This member function is mean to remove Doodlebugs if Doodlebugs have not eaten ants for 3 days.
** It will return value as bool type.
**************************************************************************************************/
bool Doodlebug::starve(){
    
	Point point(row, column);

	if(starveAge >= 3){
		
        //Remove Doolebugs if starved
	board->removeCritter(point);
        return true; 
	}
    
    return false; 
}

/**************************************************************************************************
**                                  Doodlebug::getType()
** This getter is mean to return Doodlebug as enmu type data.
**************************************************************************************************/
BugType Doodlebug::getType(){
    
    return BUG;
}






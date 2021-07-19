/**************************************************************************************************
** Program Name:Group 10 Predatory-Prey Game
** Date:        04/23/2019
** Description: Header file for the Ant class. Contains the member variables and functions.
**************************************************************************************************/

#ifndef ANT_HPP
#define ANT_HPP
#include "Critter.hpp"
#include "Point.hpp"
#include "Gameboard.hpp"

class Ant : public Critter{
    private:
        Gameboard* board;

    public:
	    Ant(); 
        Ant(Point&, Gameboard*); 
        Point move();
        Critter* breed();
	    BugType getType();
};

#endif

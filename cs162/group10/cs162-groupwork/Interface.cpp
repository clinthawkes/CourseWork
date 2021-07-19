/***********************************************************************
 * Program Name: Interface.cpp
 * Author: Brian Yi
 * Date: 5/6/2019
 * Description: This is the interface for the creation of critters.
 * *********************************************************************/

#include "Interface.hpp"
#include "Critter.hpp"
#include "Ant.hpp"
#include "Doodlebug.hpp"
#include "Gameboard.hpp"


//Default constructor

Interface::Interface() {
}


//Creates a pointer to ant at a point on the gameboard
//returns the pointer to ant

Ant* Interface::createAnt(Point point, Gameboard* gameboard) {
    Ant* newAnt = new Ant(point, gameboard);
    return newAnt;
}


//Creates a pointer to the doodlebug at a point on the gameboard
//returns the pointer to doodlebug

Doodlebug* Interface::createDoodlebug(Point point, Gameboard* gameboard) {
    Doodlebug* newDoodlebug = new Doodlebug(point, gameboard);
    return newDoodlebug;
}

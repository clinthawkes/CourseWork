/***********************************************************************
 * Program Name: Interface.hpp
 * Author: Brian Yi
 * Date: 5/6/2019
 * Description: This is the interface for the creation of critters.
 * *********************************************************************/

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Point.hpp"
#include "Critter.hpp"
#include "Ant.hpp"
#include "Doodlebug.hpp"
#include "BugType.hpp"
#include "Gameboard.hpp"

class Interface {
private:

public:
    Interface();
    Ant* createAnt(Point, Gameboard*);
    Doodlebug* createDoodlebug(Point, Gameboard*);
};

#endif
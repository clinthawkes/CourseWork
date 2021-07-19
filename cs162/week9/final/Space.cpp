/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/05/2019
** Description: Implementation file for the Space class. This is an abstract class and has three
                pure virtual functions that are overridden by the derived classes. Space contains
                these setters and getters for its member variables. 
**************************************************************************************************/

#include "Space.hpp"

//getter for the pointer to the North of this Space
Space* Space::getNorth(){

    return north;
}

//setter for the pointer to the North of this Space
void Space::setNorth(Space* N){

    north = N;
}

//getter for the pointer to the East of this Space
Space* Space::getEast(){

    return east;
}

//setter for the pointer to the East of this Space
void Space::setEast(Space* E){

    east = E;
}

//getter for the pointer to the South of this Space
Space* Space::getSouth(){

    return south;
}

//setter for the pointer to the South of this Space
void Space::setSouth(Space* S){

    south = S;
}

//getter for the pointer to the West of this Space
Space* Space::getWest(){

    return west;
}

//setter for the pointer to the West of this Space
void Space::setWest(Space* W){

    west = W;
}

//getter for the object variable
item Space::getObject(){

    return object; 
}

//setter for the object variable
void Space::setObject(item obj){

    object = obj; 
}

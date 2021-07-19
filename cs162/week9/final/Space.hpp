/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/05/2019
** Description: Header file for the Space class. The Space class is the base class for all the 
                different locations in the game. This class contains five member variables with 
                their setters and getters, as well as three pure virtual functions. More info
                can be found in the Space.cpp file
**************************************************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP
#include "validation.hpp"
#include <vector>

//type used for the items found in the game 
enum item {none, rope, pipe, powder, bomb};

class Space{

    protected:
        Space* north;           //pointer to above
        Space* east;            //pointer to the right
        Space* south;           //pointer to below
        Space* west;            //pointer to the left
        item object;            //stores object until user picks it up
        
    public:
        virtual bool investigate(std::vector<item> &backpack) = 0;
        virtual void showMap(int) = 0;
        virtual Space* move() = 0;
        Space* getNorth();
        void setNorth(Space*);
        Space* getEast();
        void setEast(Space*);
        Space* getSouth();
        void setSouth(Space*);
        Space* getWest();
        void setWest(Space*);
        item getObject();
        void setObject(item);

        
};

#endif

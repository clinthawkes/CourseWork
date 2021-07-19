/*******************************************************************
    Program name: Doodlebug.hpp
    Author: Chen Yan        
    Date: 05/08/2019
    Description: This program is specification file header of Doodlebug
                 class. It includes member variables and member function
                 prototypes.
*****************************************************************/
#ifndef DOODLEBUG_HPP
#define DOODLEBUG_HPP
#include "Critter.hpp"
#include "Point.hpp"
#include "Gameboard.hpp"

class Doodlebug : public Critter
{
    private:
        int starveAge;
        Gameboard *board;

    public:
        Doodlebug();
        Doodlebug(Point &point, Gameboard*);
        Point move() override;
        Critter* breed() override;
        BugType getType() override;
        bool starve() override;
};
#endif

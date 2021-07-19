/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/06/2019
** Description: Header file for the Ladder class. This class is derived from the abstract Space
                class. Ladder contains three virtual functions that have been overridden. More
                information can be found in the Ladder.cpp file.
**************************************************************************************************/

#ifndef LADDER_HPP
#define LADDER_HPP
#include "Space.hpp"

class Ladder : public Space{

    private:

    public:
        Ladder();
        virtual void showMap(int) override;
        virtual bool investigate(std::vector<item> &backpack) override;
        virtual Space* move() override;

    
};

#endif


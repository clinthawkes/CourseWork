/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/07/2019
** Description: Header file for the Gear class. Gear is derived from the abstract Space class. It
                contains three virtual functions that have been overridden. More information can be
                found in the Gear.cpp file.
**************************************************************************************************/

#ifndef GEAR_HPP
#define GEAR_HPP
#include "Space.hpp"

class Gear : public Space{

    private:

    public:
        Gear();
        virtual void showMap(int) override;
        virtual bool investigate(std::vector<item> &backpack) override;
        virtual Space* move() override;

};

#endif

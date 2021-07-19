/**************************************************************************************************
** Program Name:Final Project       
** Author:      Clinton Hawkes
** Date:        06/07/2019
** Description: This is the header file for the Chemical class. Class contains one member variable
                that stores the state of an object and three virtual functions from the Space
                class that must be overridden. More information can be found in Chemical.cpp
**************************************************************************************************/

#ifndef CHEMICAL_HPP
#define CHEMICAL_HPP
#include "Space.hpp"

class Chemical : public Space{

    private:
        bool open;      //stores state of locker cabinet

    public:
        Chemical();
        virtual void showMap(int) override;
        virtual bool investigate(std::vector<item> &backpack) override;
        virtual Space* move() override;

};

#endif

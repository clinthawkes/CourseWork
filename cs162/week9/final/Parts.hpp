/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/07/2019
** Description: Header file for the Parts class. Parts is derived from the abstract Space class. 
                Parts contains three virtual functions that have been overridden. More information
                about the class can be found in the Parts.cpp file.
**************************************************************************************************/

#ifndef PARTS_HPP
#define PARTS_HPP
#include "Space.hpp"

class Parts : public Space{

    private:

    public:
        Parts();
        virtual void showMap(int) override;
        virtual bool investigate(std::vector<item> &backpack) override;
        virtual Space* move() override;

};

#endif

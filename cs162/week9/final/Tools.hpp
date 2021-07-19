/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/07/2019
** Description: This is the header file for the Tools class. Tools is derived from the abstract
                Space class and has one member variable with three virtual functions that must
                have been overridden. More information can be found in the Tools.cpp file
**************************************************************************************************/

#ifndef TOOLS_HPP
#define TOOLS_HPP
#include "Space.hpp"

class Tools : public Space{

    private:
        bool open;          //keeps current state of the toolbox in the class 

    public:
        Tools();
        virtual void showMap(int) override;
        virtual bool investigate(std::vector<item> &) override;
        virtual Space* move() override;

};

#endif

/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/07/2019
** Description: Header file for the Workbench class. This class is derived from the abstract
                Space class. Workbench contains three virtual functions that have been overridden.
                More information can be found in the Workbench.cpp file.
**************************************************************************************************/

#ifndef WORKBENCH_HPP
#define WORKBENCH_HPP
#include "Space.hpp"

class Workbench : public Space{
    
    private:

    public:
        Workbench();
        virtual void showMap(int) override;
        virtual bool investigate(std::vector<item> &backpack) override;
        virtual Space* move() override;

};

#endif

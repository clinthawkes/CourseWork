/**************************************************************************************************
** Program Name:Fantasy Combat
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Header file for the HarryPotter class. Class overrides the two virtual functions 
                found in the Character class, which is the parent to this class.
**************************************************************************************************/

#ifndef HARRYPOTTER_HPP
#define HARRYPOTTER_HPP
#include "Character.hpp"

class HarryPotter : public Character{

    private:
        int numLife; 

    public:
        HarryPotter();
        HarryPotter(std::string);
        virtual int attack() override;
        virtual int defense(int) override;
        virtual void recovery() override;    
};

#endif

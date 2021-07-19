/**************************************************************************************************
** Program Name:Fantasy Combat
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Header file for the Barbarian class. Class overrides the two virtual functions 
                in the Character class, which is the parent to this class.
**************************************************************************************************/

#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP
#include "Character.hpp"

class Barbarian : public Character{
    
    private:

    public:
        Barbarian();
        Barbarian(std::string); 
        virtual int attack() override;
        virtual int defense(int) override;
    
};

#endif

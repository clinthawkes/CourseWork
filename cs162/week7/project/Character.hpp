/**************************************************************************************************
** Program Name:Fantasy Combat  
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Header file for the Character class. Contains the variables used by all the 
                derived classes and the functions used to test the characters. Two of the 
                functions are pure virtual, so this is an abstract class.
**************************************************************************************************/

#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <string>
#include "rollDie.hpp"

class Character {

    protected:
        int armor,
            sp,
            maxSP; 
        std::string type; 
        std::string name; 
    
    public:
        Character(); 
        virtual int attack() = 0;           //pure virtual, must be overridden
        virtual int defense(int) = 0;       //pure virtual, must be overridden
        int getArmor();
        int getSP();
        std::string getType();
        std::string getName();
        void setName(std::string); 
        virtual void recovery();            //virtual
};

#endif

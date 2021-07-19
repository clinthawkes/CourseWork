/**************************************************************************************************
** Program Name:Fantasy Combat
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Implementation file for the Character class. This is an abstract class that holds
                the information of the derived classes. Two pure virtual functions are not 
                declared here, but are overridden in the derived classes.
**************************************************************************************************/

#include "Character.hpp"

//default constructor
Character::Character(){
    armor = 0;
    sp = 0;
    type = "";
}

//getter for the armor variable
int Character::getArmor(){
    return armor;
}

//getter for the sp variable
int Character::getSP(){
    return sp;
}

//getter for the type variable
std::string Character::getType(){
    return type;
}

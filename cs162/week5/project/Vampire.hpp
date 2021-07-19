/**************************************************************************************************
** Program Name:Fantasy Combat
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Header file for the Vampire class. Class overrides the two virtual functions found
                in the Character class, the parent to this class.
**************************************************************************************************/

#ifndef VAMPIRE_HPP
#define VAMPIRE_HPP
#include "Character.hpp"

class Vampire : public Character{

    private:

    public:
        Vampire();
        virtual int attack() override;
        virtual int defense(int) override;

};

#endif

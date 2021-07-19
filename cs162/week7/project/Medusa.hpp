/**************************************************************************************************
** Program Name:Fantasy Class
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Header file for the Medusa class. Class overrides the two virtual functions found
                in the Character class, which is the parent to this class.
**************************************************************************************************/

#ifndef MEDUSA_HPP
#define MEDUSA_HPP
#include "Character.hpp"

class Medusa : public Character{

    private:

    public:
        Medusa();
        Medusa(std::string);
        virtual int attack() override;
        virtual int defense(int) override;

}; 

#endif

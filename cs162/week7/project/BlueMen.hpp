/**************************************************************************************************
** Program Name:Fantasy Combat      
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Header file for the BlueMen class. Class overrides the two virtual functions found
                in the Character class, which is the parent to this class.
**************************************************************************************************/

#ifndef BLUEMEN_HPP
#define BLUEMEN_HPP
#include "Character.hpp"

class BlueMen : public Character{

    private:
        int numDefDie; 

    public:
        BlueMen();
        BlueMen(std::string);
        virtual int attack() override;
        virtual int defense(int) override;

};

#endif

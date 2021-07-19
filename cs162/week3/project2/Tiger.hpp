/**************************************************************************************************
** Program Name:Zoo Tycoon
** Author:      Clinton Hawkes
** Date:        04/21/2019
** Description: Header file for the Tiger class. This file contains the constructor and the two
                member functions used by this class. This class is derived from the Animal class,
                so those variables and functions can be seen in the Animal.hpp file.
**************************************************************************************************/

#ifndef TIGER_HPP
#define TIGER_HPP
#include "Animal.hpp"

class Tiger : public Animal{

    public:
        Tiger();
        int getDailyFoodCost();
        int getPayoff();
        
};

#endif
 
 

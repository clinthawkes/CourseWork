/**************************************************************************************************
** Program Name:Zoo Tycoon
** Author:      Clinton Hawkes
** Date:        04/21/2019
** Description: Header file for the Penguin class. This file contains the constructor and two
                member functions used by this class. This class was derived from the Animal
                class, so those variables and functions can be found in Animal.hpp
**************************************************************************************************/

#ifndef PENGUIN_HPP
#define PENGUIN_HPP
#include "Animal.hpp"

class Penguin : public Animal{

    public:
        Penguin();
        int getDailyFoodCost();
        int getPayoff();
        
};

#endif

/**************************************************************************************************
** Program Name:Zoo Tycoon
** Author:      Clinton Hawkes
** Date:        04/21/2019
** Description: Header file for the Turtle class. This file contains the constructor and the two
                member functions used by this class. This class is derived from the Animal class
                so those variables and functions can be seen in Animal.hpp.
**************************************************************************************************/

#ifndef TURTLE_HPP
#define TURTLE_HPP
#include "Animal.hpp"

class Turtle : public Animal{

    public:
        Turtle();
        int getDailyFoodCost();
        int getPayoff();

};

#endif

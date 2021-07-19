/**************************************************************************************************
** Program Name:Zoo Tycoon
** Author:      Clinton Hawkes
** Date:        04/21/2019
** Description: Implementation file for the Penguin class. File contains the constructor and two
                member functions for the class. This class was derived from the Animal class, 
                so it inherited the variables and functions found in that class. More detailed
                description of the tow functions found in this class can be found below.
**************************************************************************************************/

#include "Penguin.hpp"

//default constructor
Penguin::Penguin(){
    
    cost = 1000;
    numberOfBabies = 5;
    payoff = 100;
}

/**************************************************************************************************
** Description: Function returns the daily food cost for the Penguin. This is the same as the 
                base food cost, so that is the value returned.
**************************************************************************************************/
int Penguin::getDailyFoodCost(){
    
    return BASE_FOOD_COST;
}

/**************************************************************************************************
** Description: Functions returns the daily payoff for a Penguin. This is calculated by dividing
                the initial cost of a penguin by 10. We only deal with whole dollars at this zoo,
                so the cents are dropped if there are any.
**************************************************************************************************/
int Penguin::getPayoff(){
    
    return cost / 10;
}

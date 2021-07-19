/**************************************************************************************************
** Program Name:Zoo Tycoon
** Author:      Clinton Hawkes
** Date:        04/21/2019
** Description: Implementation file for the Tiger class. File contains the constructor and two
                member functions for the class. This class was derived from the Animal class, 
                so it inherited the variables and functions found in that class as well. More
                detailed description of the two functions found in this class can be found below.
**************************************************************************************************/

#include "Tiger.hpp"

//default constructor
Tiger::Tiger(){

    cost = 10000;
    numberOfBabies = 1;
    payoff = 2000; 
}

/**************************************************************************************************
** Description: Function returns the daily food cost for the Tiger by multiplying the base food
                cost by 5.
**************************************************************************************************/
int Tiger::getDailyFoodCost(){
    
    return BASE_FOOD_COST * 5;
}

/**************************************************************************************************
** Description: Function returns the daily payoff for a Tiger. This is calculated by dividing the
                initial cost of a Tiger by 5. Wel only deal with whole dollars at this zoo, so
                the cents are left off.
**************************************************************************************************/
int Tiger::getPayoff(){
    
    return cost / 5;
}


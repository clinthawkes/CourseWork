/**************************************************************************************************
** Program Name:Zoo Tycoon
** Author:      Clinton Hawkes
** Date:        04/21/2019
** Description: Implementation file for the Turtle class. File contains the constructor and two
                member functions for the class. This is class was derived from the Animal class,
                so it inherited the variables and functions found in that class as well. More
                detailed description of the two functions for this class can be found below.
**************************************************************************************************/

#include "Turtle.hpp"

//default constructor
Turtle::Turtle(){

    cost = 100;
    numberOfBabies = 10;
    payoff = 5; 
}

/**************************************************************************************************
** Description: Function returns the daily food cost for a turtle by dividing the base food cost
                in half. We only deal with dollars at this zoo, so cents are left off.
**************************************************************************************************/
int Turtle::getDailyFoodCost(){
    
    return BASE_FOOD_COST / 2;
}

/**************************************************************************************************
** Description: Function returns the daily payoff for a turtle. This is calculated by dividing 
                the initial cost of a turtle by 20. (equiv 5% of cost). We only deal with dollars
                at this zoo, so the cents are left off.
**************************************************************************************************/
int Turtle::getPayoff(){
    
    return cost / 20;
}

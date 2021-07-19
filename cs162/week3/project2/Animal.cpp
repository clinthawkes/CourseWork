/**************************************************************************************************
** Program Name:Zoo Tycoon
** Author:      Clinton Hawkes
** Date:        04/21/2019
** Description: Implementation file for the Animal class. File contains the constructor and member
                function logic. This is the base class of three derived classes... Penguin, Tiger
                and Turtle. All variables and functions found in this class were inherited by those
                classes. More details about the functions of this class can be found below.
**************************************************************************************************/

#include "Animal.hpp"

//default constructor
Animal::Animal(){

    age = 1;
    cost = 0;
    numberOfBabies = 0;
    payoff = 0; 
}

//getter for the age variable
int Animal::getAge(){
    
    return age;
}

//setter for the age variable
void Animal::setAge(int age){
    
    this->age = age;    
}    

//getter for the cost variable
int Animal::getCost(){
    
    return cost;
}                                    
 
//getter for the numberOfBabies variable
int Animal::getNumberOfBabies(){
    
    return numberOfBabies;
}

//getter for the daily food cost
int Animal::getDailyFoodCost(){
    
    return BASE_FOOD_COST;
}

//getter for the payoff variable
int Animal::getPayOff(){
    return payoff;
}

/**************************************************************************************************
** Description: Function increases the age of the calling object by 1.
**************************************************************************************************/
void Animal::increaseAge(){
    
    age++;
}


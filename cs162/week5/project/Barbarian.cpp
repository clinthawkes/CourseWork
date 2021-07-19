/**************************************************************************************************
** Program Name:Fantasy Combat  
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Implementation file for the Barbarian class. Barbarian is a class found in the 
                game. The initial armor and sp values can be seen below, as well as the logic for
                the two overridden functions from the Character class.
**************************************************************************************************/

#include "Barbarian.hpp"
#include <iostream>

//default constructor
Barbarian::Barbarian(){
    
    armor = 0;
    sp = 12;
    type = "Barbarian";
}

/**************************************************************************************************
** Description: Function rolls two six sided die and returns the value as an attack.
**************************************************************************************************/
int Barbarian::attack(){

    //returns the simulated die roll value 
    return rollDie(2, 6);
}

/**************************************************************************************************
** Description: Function is used to determine how much damage the opponent's attack actually
                effects the Barbarian. The calculation specifics are below. The actual damage
                to the barbarian is returned to the calling function.
**************************************************************************************************/
int Barbarian::defense(int hit){

    //medusa performed her glare 
    if(hit == 99){
        sp = 0;         //glare killed the barbarian
        std::cout << "Barbarian was turned to stone... " << std::endl; 
        return 99;
    }
     
    //defense die is rolled 
    int defend = rollDie(2, 6);
    
    std::cout << "Defender rolled a " << defend << "." << std::endl; 

    int deduction = hit - defend - armor;
    
    //prevents the barbarian from gaining sp on the defense 
    if(deduction < 1){
        return 0;
    }
    else{
        sp -= deduction;        //subtracts damage from sp and returns ammount subtracted 
        return deduction;
    }
}

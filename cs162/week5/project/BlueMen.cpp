/**************************************************************************************************
** Program Name:Fantasy Combat  
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Implementation file for the BlueMen class. BlueMen is a type of character found
                in the game. The initial armor and sp values can be seen below, as well as the
                overridden functions from the Character class
**************************************************************************************************/

#include "BlueMen.hpp"
#include <iostream>

//default constructor
BlueMen::BlueMen(){
    
    armor = 3;
    sp = 12;
    type = "Blue Men";
    numDefDie = 3;
}

/**************************************************************************************************
** Description: Function rolls two, ten sided dice and returns the value as an attack
**************************************************************************************************/
int BlueMen::attack(){ 

    //returns the simulated die roll value 
    return rollDie(2, 10);
}

/**************************************************************************************************
** Description: Function is used to determine how much damage the opponent's attack actually has
                on the BlueMen. BlueMen have a special attribute that the other characters in the
                game don't have. Initially, the bluemen roll 3, 6 sided die for their defense. If
                the bluemen's sp drops down to 8, they only have 2 die to roll for the defense. If
                the bluemen's sp drops down to 4, they only have 1 die to roll for defense. Details
                are shown below.
**************************************************************************************************/
int BlueMen::defense(int hit){

    //medusa performed her glare 
    if(hit == 99){
        sp = 0;         //glare killed the bluemen
        std::cout << "Defender was turned to stone... " << std::endl; 
        return 99;
    }

    //defense die is rolled  
    int defend = rollDie(numDefDie, 6);
    
    std::cout << "Defender rolled a " << defend << "." << std::endl; 

    //calculating the actual damage to the bluemen 
    int deduction = hit - defend - armor;

    //prevents the bluemen from gaining sp on the defense 
    if(deduction < 1){
        return 0;
    }
    //the following sets the number of defense dice based on the current sp value 
    else{
        sp -= deduction;
        if(sp <= 8){
            numDefDie = 2;
            if(sp <= 4){
                numDefDie = 1;
            }
        }
        return deduction; 
    }
}

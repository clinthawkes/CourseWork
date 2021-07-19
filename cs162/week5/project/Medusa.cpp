/**************************************************************************************************
** Program Name:Fantasy Combat  
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Implementation file for the Medusa class. The initial armor and sp can be seen 
                below, as well as the overridden functions that were inherited from the Character
                class.
**************************************************************************************************/

#include "Medusa.hpp"
#include <iostream>

//default constructor
Medusa::Medusa(){
    
    armor = 3;
    sp = 8;
    type = "Medusa";
}

/**************************************************************************************************
** Description: Function rolls two, six sided dice to determint the attack value. Medusa has a
                special attack capability that the other characters do not have. She has the 
                ability to "glare" at her opponent instantly defeating them. (can be blocked by
                vampire charm and HarryPotter can come back to life)
**************************************************************************************************/
int Medusa::attack(){

    int value = rollDie(2, 6);
    
    //if the die roll is 12, then Medusa performs her glare and deals 99 damage to the opponent
    if(value == 12){
        std::cout << "Medusa rolls a 12 and uses her glare! (delivers 99 damage)" << std::endl; 
        return 99;
    }
    //if the die roll is not 12, the roll amount is returned as the attack value 
    else{
        return value;
    } 
}

/**************************************************************************************************
** Description: Function is used to determine how much damage the opponent's attack actually
                effects Medusa. If Medusa is battling another Medusa and the other performs a
                glare, then Medusa is turned to stone. Calculation details are below.
**************************************************************************************************/
int Medusa::defense(int hit){
    
    //opponent medusa performed her glare  
    if(hit == 99){
        sp = 0;             //glare from other Medusa killed this one
        std::cout << "Defender was turned to stone... " << std::endl;
        return 99;
    }

    //defense die roll 
    int defend = rollDie(1, 6);

    std::cout << "Defender rolled a " << defend << "." << std::endl; 
    
    //calculation of actual damage inflicted 
    int deduction = hit - defend - armor;

    //prevenst medusa from gaining sp on defense 
    if(deduction < 1){
        return 0;
    }
    else{
        //deducts damage from medusa's sp 
        sp -= deduction;
        return deduction;
    }
}

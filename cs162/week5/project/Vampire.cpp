/**************************************************************************************************
** Program Name:Fantasy Combat  
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Implementation file for the Vampire class. Vampire is one of the characters found
                in the game. The initial armor and sp values can be seen below, as well as the
                logic for the two overridden functions from the Character class.
**************************************************************************************************/

#include "Vampire.hpp"
#include <iostream>

//default constructor
Vampire::Vampire(){
    
    armor = 1;
    sp = 18;
    type = "Vampire";
}

/**************************************************************************************************
** Description: Function rolls one twelve sided die and returns the value as an attack.
**************************************************************************************************/
int Vampire::attack(){

    //returns the simulated die roll value 
    return rollDie(1, 12);
}

/**************************************************************************************************
** Description: Function is used to determine how much damage the opponents attack actually effects
                the vampire. The vampire has a special "Charm" ability where 50% of the time, the
                opponents attack does not actuall take place. This functions determines when the
                charm ability takes place, and if it does, the damage for the round is 0. If the 
                charm does not take place, the damage is calulated in the same manner as all the 
                other characters.
**************************************************************************************************/
int Vampire::defense(int hit){

    int deduction = 0; 
    int charm = rollDie(1, 2);      //random number between 1 and 2 determines charm
    int defend = rollDie(1, 6);     //random number is used as defending roll

    switch(charm){

        //if the charm die rolled a 1, the charm takes place and there is no damage this round 
        case 1: std::cout << "Vampire charmed opponent... " << std::endl; 
                std::cout << "Defender rolled a " << defend << "." << std::endl; 
                break; 

        //if the charm die rolled is 2, the damage is calculated below. 
        case 2: if(hit == 99){          //medusa performed her glare
                    deduction = 99;     //99 signifies glare
                    sp = 0;
                    std::cout << "Vampire was turned to stone... " << std::endl; 
                }
                else{ 
                    std::cout << "Defender rolled a  " << defend << "." << std::endl; 
                    deduction = hit - defend - armor;
                    //prevents vampire from gaining sp off a defense 
                    if(deduction > 0){  
                        sp -= deduction;
                    } 
                    else{
                        deduction = 0;
                    }
                } 
                break; 
    }
    return deduction; 
}

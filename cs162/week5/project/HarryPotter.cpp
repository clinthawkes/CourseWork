/**************************************************************************************************
** Program Name:Fantasy Combat  
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Implementation file for the HarryPotter class. The initial armor and sp values
                can be seen below, as well as the overridden functions from the Character class.
**************************************************************************************************/

#include "HarryPotter.hpp"
#include <iostream>

//default constructor
HarryPotter::HarryPotter(){
    
    armor = 0;
    sp = 10;
    type = "Harry Potter";
    numLife = 1;
}

/**************************************************************************************************
** Description: Function rolls two six sided dice and returns the value as an attack 
**************************************************************************************************/
int HarryPotter::attack(){

    //returns simulated die roll 
    return rollDie(2, 6);
}

/**************************************************************************************************
** Description: Function is used to determine how much damage the opponent's attack actually
                effects HarryPotter. Harrypotter has a special defense ability where he come back
                to life if his sp drops to zero. After he come back to life, his sp is set to 20.
                Harry only has one extra life, so if his sp drops to 0 again he is dead.
**************************************************************************************************/
int HarryPotter::defense(int hit){

    //Medusa performed her glare on harry 
    if(hit == 99){
        if(numLife == 1){   //if Harry is on his first life the glare kills him and he returns
            numLife = 0;    //subtracts a life because he died
            sp = 20;
            std::cout << "Harry used Hogwarts against Medusa's glare." << std::endl; 
            return 99; 
        }
        //if Harry is on his second life and medusa glares at him, he is dead 
        else{
            sp = 0;
            std::cout << "Harry was turned to stone... " << std::endl;   
            return 99;
        }
    }

    int defend = rollDie(2, 6);
    
    std::cout << "Defender rolled a " << defend << "." << std::endl; 

    //calculation of actual damage inflicted 
    int deduction = hit - defend - armor;

    //prevents Harry from gaining sp on the defense 
    if(deduction < 1){
        return 0;
    }
    else{
        sp -= deduction;
        //if Harry's sp drops to 0 and he is on his first life, he comes back to life with 20 sp 
        if(sp <= 0 && numLife == 1){
            sp = 20;
            numLife = 0;
            std::cout << "Harry came back to life..." << std::endl;  
            return deduction;
        }
        else{
            return deduction;
        }
    }
}

    

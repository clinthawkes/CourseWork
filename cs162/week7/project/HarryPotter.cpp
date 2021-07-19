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
    maxSP = 20;
    type = "Harry Potter";
    numLife = 1;
    name = ""; 
}

//constructor with string argument for name
HarryPotter::HarryPotter(std::string nombre){
    
    armor = 0;
    sp = 10;
    maxSP = 20;
    type = "Harry Potter";
    numLife = 1;
    name = nombre; 
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
            //std::cout << "Harry used Hogwarts against Medusa's glare." << std::endl; 
            return 99; 
        }
        //if Harry is on his second life and medusa glares at him, he is dead 
        else{
            sp = 0;
            //std::cout << "Harry was turned to stone... " << std::endl;   
            return 99;
        }
    }

    int defend = rollDie(2, 6);
    
    //std::cout << "Defender rolled a " << defend << "." << std::endl; 

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
            //std::cout << "Harry came back to life..." << std::endl;  
            return deduction;
        }
        else{
            return deduction;
        }
    }
}

/**************************************************************************************************
** Description: Function overrides the virtual function in parent class. Function is used to return
                some of the sp points lost during battle if Harry turns out to be the winner. This
                function needed to be different than the parent class recovery function because
                Harry has different max sp depending on if he is on his first or last life. The 
                function rolls a die to determine how many points are to be returned.
**************************************************************************************************/
void HarryPotter::recovery(){

    //generates a random number between 1 and 5 for calculating recovery points 
    int roll = rollDie(1,5);
    
    //if Harry is still on his first life, the recovery points can not put him over 10 sp  
    if(numLife == 1){
        maxSP = 10;
    }
    //if Harry is on his last life, the recovery points can not put him over 20 points 
    else{
        maxSP = 20;
    }

    switch(roll){

        //if 1 is rolled, ~20% of max sp is recovered for Harry 
        case 1: sp += (maxSP / 5);
                //recovered sp cannot put sp over maxSP 
                if(sp > maxSP){
                    sp = maxSP;
                }
                break;
                
        //if 2 is rolled, ~40% of max sp is recovered for Harry 
        case 2: sp += (2*(maxSP / 5));
                //recovered sp cannot put sp over maxSP 
                if(sp > maxSP){
                    sp = maxSP;
                }
                break;

        //if 3 is rolled, ~60% of max sp is recovered for Harry 
        case 3: sp += (3*(maxSP / 5));
                //recovered sp cannot put sp over maxSP 
                if(sp > maxSP){
                    sp = maxSP;
                }
                break;

        //if 4 is rolled, ~80% of max sp is recovered for Harry 
        case 4: sp += (4*(maxSP / 5));
                //recovered sp cannot put sp over maxSP 
                if(sp > maxSP){
                    sp = maxSP;
                }
                break;

        //if 5 is rolled, sp = maxSP 
        case 5: sp = maxSP;
                break;
    } 

}

/*************************************************************************************************
** Program Name:Fantasy Combat
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Implementation file for the Character class. This is an abstract class that holds
                the information of the derived classes. Two pure virtual functions are not 
                declared here, but are overridden in the derived classes.
**************************************************************************************************/

#include "Character.hpp"
#include "rollDie.hpp"

//default constructor
Character::Character(){
    armor = 0;
    sp = 0;
    maxSP = 0; 
    type = "";
    name = ""; 
}

//getter for the armor variable
int Character::getArmor(){
    return armor;
}

//getter for the sp variable
int Character::getSP(){
    return sp;
}

//getter for the type variable
std::string Character::getType(){
    return type;
}

std::string Character::getName(){
    return name;
}

//used to set the name variable
void Character::setName(std::string nombre){
    name = nombre;
}

/**************************************************************************************************
** Description: Function is used to return some of the winner's sp points that were lost during
                the battle. This function is called after the winner of the battle is determined
                and a random number generator is used to calculate how many sp points should be 
                returned.
**************************************************************************************************/
void Character::recovery(){

    //generates a random number between 1 and 5 for the recovery determination  
    int roll = rollDie(1, 5);

    switch(roll){

        //if 1 is rolled, ~20% of the players max sp is added to current sp points 
        case 1: sp += (maxSP / 5);
                //if adding 20% to sp puts sp over player max, sp = max 
                if(sp > maxSP){
                    sp = maxSP;
                }
                break;

        //if 2 is rolled, ~40% of the players max sp is added to current sp points 
        case 2: sp += (2*(maxSP / 5));
                //if adding 40% to sp puts sp over player max, sp = max 
                if(sp > maxSP){
                    sp = maxSP;
                }
                break;
                
        //if 3 is rolled, ~60% of the players max sp is added to current sp points 
        case 3: sp += (3*(maxSP / 5));
                //if adding 60% to sp puts sp over player max, sp = max 
                if(sp > maxSP){
                    sp = maxSP;
                }
                break;
                
        //if 4 is rolled, ~80% of the players max sp is added to current sp points 
        case 4: sp += (4*(maxSP / 5));
                //if adding 80% to sp puts sp over player max, sp = max 
                if(sp > maxSP){
                    sp = maxSP;
                }
                break;
                
        //if 5 is rolled, up to 100% of the players max sp is added to current sp points 
        case 5: sp = maxSP;
                break;
    }
}

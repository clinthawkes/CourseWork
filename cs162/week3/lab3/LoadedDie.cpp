/*******************************************************************************    
** Program Name:War Games
** Author:      Clinton Hawkes
** Date:        04/16/2019
** Description: Implementation file for the LoadedDie class. This class is a 
                child to the Die class. This class adds a round counter and a
                weighted random number generator. More details can be found 
                below.
*******************************************************************************/

#include "LoadedDie.hpp"
#include <cstdlib>

//default constructor
LoadedDie::LoadedDie(){
    round = 0; 
}

//default destructor
LoadedDie::~LoadedDie(){
}


/*******************************************************************************
** Description: Function generates a weighted random number between 1 and the 
                number of sides found on the die(variable N). The current round
                is tracked by the "round" variable. If the current round is even,
                the function returns a number that is averaged with the highest 
                number possible on the die(variable N). If the current round is
                odd, the function returns a "regular" random number between 1
                and the highest number possible for the die (variable N).
*******************************************************************************/
int LoadedDie::rollDie(){
    
    round++;            //round counter 
    
    //if the round is even, a random number is added to N and the average is returned. 
    if(round%2 == 0){    
        return ((rand()%N) + N) / 2;
    }        
    //if the round is odd, a regular random number is returned(between 1 and N) 
    else{
        return (rand()%N + 1);
    }
}


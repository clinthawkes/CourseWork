/**************************************************************************************************
** Program Name:Roll Die    
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Helper function that immitates the roll of a die. The user specifies how many
                die or dice they would like to roll and the number of sides of the die. The rand()
                function is used to randomize the results.
**************************************************************************************************/

#include "rollDie.hpp"
#include <cstdlib>

int rollDie(int numDice, int numSides){

    int total = 0;
    
    //random number is generated based off number of dice and number of sides  
    for(int i = 0; i < numDice; i++){
        total += (rand() % numSides) + 1;
    }

    return total;
}

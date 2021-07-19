/*******************************************************************************    
** Program Name:War Games   
** Author:      Clinton Hawkes
** Date:        04/17/2019
** Description: War Games is a game where two players "battle" by rolling a die
                (regular or loaded). The player with the highest number wins 
                the round. The Player with the most rounds won wins the battle.
                The number of rounds is specified, as well as the type and 
                number of sides for each player's die. This main function
                declares a Game object, seeds the random number generator and 
                then the Game class takes care of the rest.
*******************************************************************************/

#include "Game.hpp"
#include <ctime>        //used to seed rand()


int main(){

    //seeding the random number generator "rand" 
    srand(time(NULL)); 
    
    Game game;
    
    game.run(); 

    return 0;
}

/**************************************************************************************************
** Program Name:Fantasy Combat
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Main function for the Fantasy Combat game. Main is used to seed the rand()
                and to call the menu for testing the characters.
**************************************************************************************************/

#include "Game.hpp"
#include <ctime>
#include <cstdlib>

int main(){

    srand(time(NULL));      //seeding the random number generator
    
    Game game;

    game.play();            //begins the tournament

    return 0;
}

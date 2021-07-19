/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/06/2019
** Description: Header file for the Game class. The Game class is used to control the function
                calls and move the game along. The class has six Space class pointers for each
                of the rooms in the game, and it also has a Player object. Game has a constructor,
                destructor, and a run function to start the game.
**************************************************************************************************/

#ifndef GAME_HPP
#define GAME_HPP
#include "Space.hpp"
#include "Player.hpp"

class Game{

    private:
        Space* ladder;          //pointer to the ladder room
        Space* tools;           //pointer to the tools room
        Space* chemical;        //pointer to the chemical room
        Space* gear;            //pointer to the gear room
        Space* workbench;       //pointer to the workbench room
        Space* parts;           //pointer to the parts room
        Player player;          //player object used in game

    public:
        Game();
        ~Game(); 
        void run();

};

#endif

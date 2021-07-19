/**************************************************************************************************
** Program Name:Fantasy Combat  
** Author:      Clinton Hawkes
** Date:        05/19/2019
** Description: Header file for the Game class. Contains functions needed to run the fighting
                tournament. Acts as the controling class for the program.
**************************************************************************************************/

#ifndef GAME_HPP
#define GAME_HPP
#include "Character.hpp"

class Game{

    private:

    public:
        Game();
        void play();
        int test(Character*, Character*, int);
       
};

#endif

/*******************************************************************************    
** Program Name:War Games
** Author:      Clinton Hawkes
** Date:        04/16/2019
** Description: Header file for the Game class. This contains all the variables
                used by the class, as well as the function prototypes for the
                class functions. The implementation file for the Game class
                can be found at Game.cpp.
*******************************************************************************/

#ifndef GAME_HPP
#define GAME_HPP
#include "LoadedDie.hpp"
#include <string>

class Game{

    private:
        long numRounds,
             tieCount,
             p1Score,
             p2Score,
             roundCount;
        Die* p1Die;
        Die* p2Die;
        std::string p1DieType, 
                    p2DieType,
                    winner; 

    public:
        Game();
        bool mainMenu();
        void run();
        void match();
    
};

#endif

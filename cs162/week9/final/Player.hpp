/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/06/2019
** Description: Header file for the Player class. This class has three member variables and several
                member functions. The Player class is used to move around the different rooms in
                the game and interact with the structures in each location.
**************************************************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Space.hpp"

class Player{

    private:
        std::vector<item> backpack;         //container to hold items player picks up
        Space* location;                    //pointer to the player's current location
        int moveCount;                      //number of moves the player has remaining

    public:
        Player();
        Player(Space*); 
        ~Player();
        Space* getLocation();
        void setLocation(Space*);
        int getMoveCount();
        void decMoveCount();
        void showBackpack();
        std::vector<item>& getBackpack(); 

}; 

#endif

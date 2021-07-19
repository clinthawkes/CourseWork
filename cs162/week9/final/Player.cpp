/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/06/2019
** Description: Implementation file for the Player class. Player is used to move around the 
                different Space locations, pick up items and store them in the backpack variable,
                and interact with the different room structures. Details of the functions can
                be found below
**************************************************************************************************/

#include "Player.hpp"
#include <iostream>

//default constructor for the Player class
Player::Player(){
   
    location = nullptr;
    moveCount = 8;
    backpack.push_back(none);           //initialize first container slot   
    backpack.push_back(none);           //initialize second container slot
    backpack.push_back(none);           //initialize third container slot
}

//constructor with a Space* argument
Player::Player(Space* start){

    location = start;
    moveCount = 8; 
    backpack.push_back(none);
    backpack.push_back(none);
    backpack.push_back(none);
}

//default destructor
Player::~Player(){
}

//getter for the location variable
Space* Player::getLocation(){

    return location;
}

//setter for the location variable
void Player::setLocation(Space* here){

    location = here;
}

//getter for the moveCount variable
int Player::getMoveCount(){

    return moveCount;
}

//getter for the backpack vector
std::vector<item>& Player::getBackpack(){

    return backpack;
}

/**************************************************************************************************
** Description: Function is used to decrease the number of steps remaining for the player. This is
                called after the player moves each time. Once moveCount hits 0, the game is over.
**************************************************************************************************/
void Player::decMoveCount(){

    moveCount--;
}

/**************************************************************************************************
** Description: Function Function is used to display the current contents of the backpack 
                variable. The variable acts as a storage for the player during the game and it
                can only hold 3 items at one time. This function will print out the contents of
                the container to the screen for the user.
**************************************************************************************************/
void Player::showBackpack(){

    std::cout << "\nThese are the contents of your backpack:" << std::endl;
    std::cout << "\nSlot 1: ";
    
    //prints out the contents of slot 1 
    if(backpack.at(0) == none){
        std::cout << "Slot is empty" << std::endl;
    }
    else if(backpack.at(0) == pipe){
        std::cout << "Pipe" << std::endl;
    }
    else{
        std::cout << "Bomb" << std::endl;
    }
    
    //prints out the contents of slot 2
    std::cout << "\nSlot 2: ";
    if(backpack.at(1) == none){
        std::cout << "Slot is empty" << std::endl;
    }
    else{
        std::cout << "Gun Powder" << std::endl;
    }
    
    //prints out the contents of slot 3
    std::cout << "\nSlot 3: ";
    if(backpack.at(2) == none){
        std::cout << "Slot is empty" << std::endl;
    }
    else{
        std::cout << "Rope" << std::endl;
    }
}

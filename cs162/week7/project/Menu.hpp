/**************************************************************************************************
** Program Name:Fantasy Combat  
** Author:      Clinton Hawkes
** Date:        05/01/2019
** Description: Header file for the Menu class. There are three private functions that are to be 
                used only by the Menu class, and a test function that is called to run tests on
                the characters of the game.
**************************************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP
#include "Character.hpp"

class Menu{

    private:
    
    public:
        Menu(); 
        bool startMenu(); 
        Character* menu1(int, int);             //used to choose first player
        Character* menu2(int, int);   //used to choose second player
        bool endMenu();                 //ask user to continue or quit

}; 

#endif

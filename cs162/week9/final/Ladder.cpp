/**************************************************************************************************
** Program Name:Final Project   
** Author:      Clinton Hawkes
** Date:        06/05/2019
** Description: This is the implementation file for the Ladder class. This is a derived class from
                the Space class. It overrides three of the pure virtual functions found in the
                abstract Space class. Thos functions are showMap, investigate, and move. More 
                details about each of these functions can be found below.
**************************************************************************************************/

#include "Ladder.hpp"
#include <iostream>
using std::cout;
using std::endl;

//default constructor for the Ladder class
Ladder::Ladder(){

    setNorth(nullptr);
    setEast(nullptr);
    setSouth(nullptr);
    setWest(nullptr);
    setObject(none);            //Ladder does not contain an item
}

/**************************************************************************************************
** Description: Function is called to print the map of the bunker and show the current location of
                the user. This function must be overridden to update the player position.
**************************************************************************************************/
void Ladder::showMap(int steps){

    cout << "\n\n                      MOVES REMAINING: " << steps << endl; 
    cout << "________________________________________________________________" << endl;
    cout << "|    /               |      |______|      |      |------|      |" << endl;   
    cout << "|   / CHEMICAL                TOOLS`              LADDER       |" << endl;   
    cout << "|  /   LOCKER        |                    |                    |" << endl;   
    cout << "| /                                                 O          |" << endl;   
    cout << "|/                   |                    |        /|\\         |" << endl;   
    cout << "|                                                   A          |" << endl;   
    cout << "|                    |                    |        / \\         |" << endl;   
    cout << "|                                                              |" << endl;   
    cout << "| __  __  __  __  __ | __  __  __  __  __ | __  __  __  __  __ |" << endl;   
    cout << "|                    |                    |                    |" << endl;   
    cout << "|                                                              |" << endl;   
    cout << "|___                 |                    |                    |" << endl;   
    cout << "| G |                                                          |" << endl;   
    cout << "| E |                |   _____________    |                    |" << endl;   
    cout << "| A |                    | WORKBENCH |                         |" << endl;   
    cout << "|_R_|                |   |___________|    |    SPARE PARTS     |" << endl;   
    cout << "|                                              ###########     |" << endl;   
    cout << "|____________________|____________________|____|_________|_____|" << endl;   
}

/**************************************************************************************************
** Description: Function is used to interact with the individual Space structure. Each derived 
                class has the user interact with the node in some way. This space has a ladder
                with the escape hatch at the top. The hatch is sealed, so the user must have a bomb
                to blow the hatch open. This is the only way to win and the user must escape before
                they die of dehydration and starvation.
**************************************************************************************************/
bool Ladder::investigate(std::vector<item> &backpack){

    int choice = 0;         //stores user's choices

    cout << "\nThere is a ladder leading up to an escape hatch... " << endl;
    cout << "You try to open it but it won't budge. What do you do?" << endl;
    cout << "1. Blow the hatch open" << endl;
    cout << "2. Nothing" << endl; 
    cout << "\nSelection: ";
    choice = integerValidation(1, 2); 

    //user wants to blow the hatch open 
    if(choice == 1){
        //the hatch is blown open if the user has a bomb in their backpack 
        if(backpack.at(0) == bomb){
            cout << "\nYou attach the bomb to the hatch and run... " << endl;
            cout << "The hatch is blown open!" << endl;
            //hatch was blown open, so false is returned to end the game 
            return false; 
        }
        //if user does not have a bomb, the game informs the user 
        else{ 
            cout << "\nYou do not have any explosives" << endl; 
        }            
    } 
    //hatch was not blown open, so true is returned to keep the game going 
    return true; 
}

/**************************************************************************************************
** Description: Function is used to inform the user of the different directions they may move,
                asks user to choose the direction, and then returns the pointer to the next
                space so the user location can be updated.
**************************************************************************************************/
Space* Ladder::move(){

    int choice = 0;         //stores user's choice 

    cout << "\nWhat direction would you like to move?" << endl;
    cout << "1. Left" << endl;
    cout << "2. Down" << endl;
    cout << "\nSelection: ";
    choice = integerValidation(1, 2);
    
    //if user wants to move left, a pointer to the space on the left is returned
    if(choice == 1){
        return this->getWest();
    }
    //user wants to move down, so that space pointer is returned 
    else{
        return this->getSouth();
    }
}

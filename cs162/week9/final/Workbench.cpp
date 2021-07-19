/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/05/2019
** Description: Implementation file for the Workbench class. This class is derived from the space
                class. The Space class is an abstract class, so this class must override three 
                pure virtual functions. More details about these function overrides can be
                found below.
**************************************************************************************************/

#include "Workbench.hpp"
#include <iostream>
using std::cout;
using std::endl;

//default constructor for the Workbench class
Workbench::Workbench(){

    setNorth(nullptr);
    setEast(nullptr);
    setSouth(nullptr);
    setWest(nullptr);
    setObject(bomb);            //bomb is the object in this room, if the user builds it
}

/**************************************************************************************************
** Description: Function is called to print the map of the bunker and show the current location of
                the player. This function is overridden to update the player position.
**************************************************************************************************/
void Workbench::showMap(int steps){

    cout << "\n\n                      MOVES REMAINING: " << steps << endl; 
    cout << "________________________________________________________________" << endl;
    cout << "|    /               |      |______|      |      |------|      |" << endl;   
    cout << "|   / CHEMICAL                TOOLS`              LADDER       |" << endl;   
    cout << "|  /   LOCKER        |                    |                    |" << endl;   
    cout << "| /                                                            |" << endl;   
    cout << "|/                   |                    |                    |" << endl;   
    cout << "|                                                              |" << endl;   
    cout << "|                    |                    |                    |" << endl;   
    cout << "|                                                              |" << endl;   
    cout << "| __  __  __  __  __ | __  __  __  __  __ | __  __  __  __  __ |" << endl;   
    cout << "|                    |                    |                    |" << endl;   
    cout << "|                                                              |" << endl;   
    cout << "|___                 |         O          |                    |" << endl;   
    cout << "| G |                         /|\\                              |" << endl;   
    cout << "| E |                |   ______^______    |                    |" << endl;   
    cout << "| A |                    | WORKBENCH |                         |" << endl;   
    cout << "|_R_|                |   |___________|    |    SPARE PARTS     |" << endl;   
    cout << "|                                              ###########     |" << endl;   
    cout << "|____________________|____________________|____|_________|_____|" << endl;   
}

/**************************************************************************************************
** Description: Function is used to interact with the structures of the class. Each class derived
                from Space uses this function to allow the user to pick up an item, or turn on a 
                light, or do something else that progresse the game. This class checks the 
                player's backpack to see if they have acquired all the parts necessary to build
                a bomb to blow the hatch. If the player has all the parts, a bomb is built and 
                stored in the backpack. If the player does not have all the parts, a message
                informing the user of this is printed.
**************************************************************************************************/
bool Workbench::investigate(std::vector<item> &backpack){

    int choice = 0;         //stores user's choice

    cout << "\nYou stand in front of the perfectly lit workbench. This would be perfect" << endl;
    cout << "for assembling your explosive. What do you want to do?" << endl;
    cout << "1. Assemble the explosive" << endl;
    cout << "2. Nothing" << endl;
    cout << "\nSelection: ";
    choice = integerValidation(1, 2);

    //user chooses to assemble a bomb 
    if(choice == 1){
        //user has all the parts so the bomb is built 
        if(backpack.at(0) == pipe && backpack.at(1) == powder && backpack.at(2) == rope){
            cout << "\nYou have assembled a bomb" << endl;
            backpack.at(0) = object;
            backpack.at(1) = none;
            backpack.at(2) = none;
        }
        //user did not have all the required parts 
        else{
            cout << "\nYou do not have all the items required to build a bomb" << endl;
        }
    }
    return true;            //true is returned so game can continue
}

/**************************************************************************************************
** Description: Function is used to inform the user of the different directions them may move,
                asks the user to choose a direction, and then returns a pointer to the space in
                the direction chosen so the player location can be updated.
**************************************************************************************************/
Space* Workbench::move(){

    int pick = 0;           //stores user's choice

    cout << "\nWhat direction would you like to move?" << endl;
    cout << "1. Left" << endl;
    cout << "2. Up" << endl;
    cout << "3. Right" << endl;
    cout << "\nSelection: ";
    pick = integerValidation(1, 3);

    //user chooses to move left, so pointer to left room is returned 
    if(pick == 1){
        return this->getWest();
    }
    //user chooses to move up, so pointer to room above is returned 
    else if(pick == 2){
        return this->getNorth();
    }
    //user chooses to move right, so pointer to the right room is returned 
    else{
        return this->getEast();
    }
}

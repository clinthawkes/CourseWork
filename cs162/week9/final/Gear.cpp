/**************************************************************************************************
** Program Name:Final Project   
** Author:      Clinton Hawkes
** Date:        06/05/2019
** Description: Implementation file for the Gear class. This class is derived from the Space class.
                The Space class is abstract, so this class must override three pure virtual 
                functions. More details about these function overrides can be found below.
**************************************************************************************************/

#include "Gear.hpp"
#include <iostream>
using std::cout;
using std::endl;

//default constructor
Gear::Gear(){

    setNorth(nullptr);
    setEast(nullptr);
    setSouth(nullptr);
    setWest(nullptr);
    setObject(rope);            //object in this room is a rope
}

/**************************************************************************************************
** Description: Function is called to print the map of the bunker and show the current location of
                the player. This function is overridden to update the player position.
**************************************************************************************************/
void Gear::showMap(int steps){

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
    cout << "|___      O          |                    |                    |" << endl;   
    cout << "| G |    /|\\                                                   |" << endl;   
    cout << "| E |     A          |   _____________    |                    |" << endl;   
    cout << "| A |    / \\             | WORKBENCH |                         |" << endl;   
    cout << "|_R_|                |   |___________|    |    SPARE PARTS     |" << endl;   
    cout << "|                                              ###########     |" << endl;   
    cout << "|____________________|____________________|____|_________|_____|" << endl;   
}

/**************************************************************************************************
** Description: Function is used to interact with the structures of the class. Each class derived
                from Space uses this function to allow the user to pick up an item, or turn on a
                light, or do something else that progresses the game. This class has a pile of
                gear in the room and some rope is available for the user to take. The user can
                take or leave the rope.
**************************************************************************************************/
bool Gear::investigate(std::vector<item> &backpack){

    int choice = 0;             //stores user's choice
    
    if(backpack.at(2) == none && object == rope){ 
        cout << "\nYou see a bundle of rope in your pile of gear and decide to use" << endl;
        cout << "some as a fuse for your explosive. What do you do?" << endl;
        cout << "1. Take some rope" << endl;
        cout << "2. Leave it" << endl;
        cout << "\nSelection: ";
        choice = integerValidation(1, 2);

        //user chooses to take the rope 
        if(choice == 1){
            backpack.at(2) = object;    //rope is stored in the player backpack
            object = none;              //the rope is removed from the pile
            cout << "\nYou took some of the rope" << endl;
        }
    }
    //user already has the rope when the re-investigate 
    else{
        cout << "\nYou already took some rope." << endl;
    }
    return true;        //true is returned so game can continue
}

/**************************************************************************************************
** Description: Function is used to inform the user of the different directions they may move,
                asks the user to choose a direction, and then returns a pointer to the space in
                the direction chosen so the player location can be updated.
**************************************************************************************************/
Space* Gear::move(){

    int pick = 0;           //stores user's choice

    cout << "\nWhat direction would you like to move?" << endl;
    cout << "1. Up" << endl;
    cout << "2. Right" << endl;
    cout << "\nSelection: ";
    pick = integerValidation(1, 2);

    //user moves up, so pointer to room above is returned 
    if(pick == 1){
        return this->getNorth();
    }
    //user moves right, so a pointer to the room on the right is returned 
    else{
        return this->getEast();
    }
}

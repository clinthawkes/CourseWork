/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/05/2019
** Description: This is the implementation file for the Tools class. This class is derived from
                the Space class. The Space class is an abstract class, so this class must 
                override three functions. ShowMap, investigate, and the move functions. More 
                details about these functions can be found below.
**************************************************************************************************/

#include "Tools.hpp"
#include <iostream>
using std::cout;
using std::endl;

//default constructor for the Tools class
Tools::Tools(){

    open = false; 
    setNorth(nullptr);
    setEast(nullptr);
    setSouth(nullptr);
    setWest(nullptr);
    setObject(none);           //Tools does not have an item
}

/**************************************************************************************************
** Description: Function is called to print the map of the bunker and show the current location of
                the user. This function is overridden to update the player position.
**************************************************************************************************/
void Tools::showMap(int steps){

    cout << "\n\n                      MOVES REMAINING: " << steps << endl; 
    cout << "________________________________________________________________" << endl;
    cout << "|    /               |      |______|      |      |------|      |" << endl;
    cout << "|   / CHEMICAL                TOOLS`              LADDER       |" << endl;
    cout << "|  /   LOCKER        |                    |                    |" << endl;
    cout << "| /                            O                               |" << endl; 
    cout << "|/                   |        /|\\         |                    |" << endl;
    cout << "|                              A                               |" << endl;   
    cout << "|                    |        / \\         |                    |" << endl;   
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
** Description: Function is used to interact with the individual space structure. Each derived
                class uses this function to allow the user to interact with the space in some
                way. This space has a toolbox that the user can open and look through.
**************************************************************************************************/
bool Tools::investigate(std::vector<item> &backpack){

    int choice = 0;                 //stores user's choice

    //these options are printed if the toolbox has not been opened 
    if(!open){ 
        cout << "\nThere is a toolbox against the wall. What do you do?" << endl;
        cout << "1. Open it" << endl; 
        cout << "2. Nothing" << endl; 
        cout << "\nSelection: ";
        choice = integerValidation(1, 2);

        //user chooses to open the toolbox 
        if(choice == 1){
            open = true;
            cout << "\nNothing useful in here..." << endl;
        }
    }
    //user has already opened the toolbox and looked through it 
    else{
        cout << "\nNothing appears to be useful in the toolbox" << endl;
    }
    //game continues by returning true 
    return true; 
}

/**************************************************************************************************
** Description: Function is used to inform the user of the different direections they may move, 
                asks the user to choose a direction, and then returns a pointer to the space in 
                that direction so the player location can be updated.
**************************************************************************************************/
Space* Tools::move(){

    int pick = 0;               //stores user's choice

    cout << "\nWhat direction would you like to move?" << endl;
    cout << "1. Left" << endl;
    cout << "2. Down" << endl;
    cout << "3. Right" << endl;
    cout << "\nSelection: ";
    pick = integerValidation(1, 3);

    //returns pointer to the space left of this one 
    if(pick == 1){
        return this->getWest();
    }
    //returns pointer to space below this current one 
    else if(pick == 2){
        return this->getSouth();
    }
    //returns pointer to space right of this current one 
    else{
        return this->getEast();
    }
}

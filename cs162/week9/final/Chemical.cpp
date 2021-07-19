/**************************************************************************************************
** Program Name:Final Project
** Author:      Clinton Hawkes
** Date:        06/05/2019
** Description: This is the implementation file for the Chemical class. This class is derived from
                the Space class. The Space class is an abstract class, so this class must
                override three functions. Showmap, investigation, and the move functions. More
                details about these functions can be found below.
**************************************************************************************************/

#include "Chemical.hpp"
#include <iostream>
using std::cout;
using std::endl;

//default constructor for the Chemical class
Chemical::Chemical(){

    open = false; 
    setNorth(nullptr);
    setEast(nullptr);
    setSouth(nullptr);
    setWest(nullptr);
    setObject(powder);          //Chemical has the gun powder for the user to take
} 


/**************************************************************************************************
** Description: Function is called to print the map of the bunker and show the current location of
                the user. This function is overridden to update the player location.
**************************************************************************************************/
void Chemical::showMap(int steps){

    cout << "\n\n                      MOVES REMAINING: " << steps << endl; 
    cout << "________________________________________________________________" << endl;
    cout << "|    /               |      |______|      |      |------|      |" << endl; 
    cout << "|   / CHEMICAL                TOOLS`              LADDER       |" << endl;   
    cout << "|  /   LOCKER        |                    |                    |" << endl;   
    cout << "| /       O                                                    |" << endl;   
    cout << "|/       /|\\         |                    |                    |" << endl;   
    cout << "|         A                                                    |" << endl;   
    cout << "|        / \\         |                    |                    |" << endl;
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
** Description: Function is used to interact with the structurs of this class. Each derived class 
                uses this function to allow the user to pick up an item or turn on a light, or
                do something else that progresses the game. This class has a chemical locker that
                the user can open. After the user opens the locker, there is some gun powder that
                the user can take to make the bomb needed to get out of the bunker.
**************************************************************************************************/
bool Chemical::investigate(std::vector<item> &backpack){

    int choice = 0;             //stores user's choice

    //if the chemical locker has not been opened yet 
    if(!open){
        cout << "\nYou see a chemical locker in the corner. What do you do" << endl;
        cout << "1. Open it" << endl;
        cout << "2. Leave it closed" << endl;
        cout << "\nSelection: ";
        choice = integerValidation(1, 2);

        //user chose to open the locker, so the following is presented 
        if(choice == 1){
            open = true;        //variable keeping track of locker open or closed
            cout << "\nYou open the locker and see various chemicals. The gun powder" << endl;
            cout << "peaks your interest. What do you do? " << endl;
            cout << "1. Take the gunpowder" << endl;
            cout << "2. Leave it" << endl;
            cout << "\nSelection: ";
            choice = integerValidation(1, 2);

            //user wants the gunpowder the the powder has not been taken yet 
            if(choice == 1 && object == powder){
                backpack.at(1) = object;    //gun powder put in backpack
                object = none;              //gun powder removed from locker 
                cout << "\nYou took the gun powder" << endl; 
            }
        }
    }
    //user has already opened the locker and taken the gun powder 
    else if(open && object == none){
        cout << "\nYou already took the gun powder." << endl;
    }
    //user opened the locker last time, but they did not take the gun powder 
    else if(open && object == powder){
        cout << "\nWhat do you want to do with the gun powder?" << endl;
        cout << "1. Take it" << endl;
        cout << "2. Leave it" << endl;
        cout << "\nSelection: ";
        choice = integerValidation(1, 2);
        //user chooses to take the gun powder this time
        if(choice == 1){
            backpack.at(1) = object;        //gun powder put in backpack
            object = none;                  //gun powder removed from locker
            cout << "\nYou took the gun powder" << endl;
        }
    }
    //returns true so the game can continue 
    return true; 
}

/**************************************************************************************************
** Description: Function is used to inform the user of the different directions they may move,
                asks the user to choose a direction, and then returns a pointer to the space in
                the direction so the player location can be updated.
**************************************************************************************************/
Space* Chemical::move(){

    int pick = 0;           //stores the user's choice

    cout << "\nWhat direction would you like to move?" << endl;
    cout << "1. Right" << endl;
    cout << "2. Down" << endl;
    cout << "Selection: ";
    pick = integerValidation(1, 2);

    //returns pointer of space to the right of this current one 
    if(pick == 1){
        return this->getEast();
    }
    //returns pointer of space just below this current one 
    else{
        return this->getSouth();
    }
}

/**************************************************************************************************
** Program Name:Final Project       
** Author:      Clinton Hawkes
** Date:        06/05/2019
** Description: Implementation file for the Parts class. This class is derived from the Space class
                The Space class is abstract, so this class must override three pure virtual 
                functions. More information about these function overrides can be found below.
**************************************************************************************************/

#include "Parts.hpp"
#include <iostream>
using std::cout;
using std::endl;

//default constructor for the Parts class
Parts::Parts(){

    setNorth(nullptr);
    setEast(nullptr);
    setSouth(nullptr);
    setWest(nullptr);
    setObject(pipe);                //a pipe is the object in this class
}

/**************************************************************************************************
** Description: Function is called to print the map of the bunker and show the current location of
                the player on the map.
**************************************************************************************************/
void Parts::showMap(int steps){

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
    cout << "|___                 |                    |         O          |" << endl;   
    cout << "| G |                                              /|\\         |" << endl;   
    cout << "| E |                |   _____________    |         A          |" << endl;   
    cout << "| A |                    | WORKBENCH |             / \\         |" << endl;   
    cout << "|_R_|                |   |___________|    |    SPARE PARTS     |" << endl;   
    cout << "|                                              ###########     |" << endl;   
    cout << "|____________________|____________________|____|_________|_____|" << endl;   
}

/**************************************************************************************************
** Description: Function is used to interact with the structures of the class. Each class derived
                from Space uses this function to allow the user to pick up an item, or turn on a
                light, or do something else to further the game. This class has a pipe object that
                is used to make the explosive needed to get out of the bunker. The user first
                chooses to look through the pile and then has the option to take the pipe.
**************************************************************************************************/
bool Parts::investigate(std::vector<item> &backpack){
    
    int choice = 0;             //stores the user's choice

    cout << "\nThere is a pile of parts and scrap metal left over from the construction" << endl;
    cout << "of the bunker. What do you want to do?" << endl;
    cout << "1. Rifle through the pile" << endl;
    cout << "2. Nothing. Looks dangerous" << endl;
    cout << "\nSelection: ";
    choice = integerValidation(1, 2);

    //user wants to look through the pile of parts 
    if(choice == 1){
        //pipe has not been taken yet, so user is given choice to take it 
        if(object == pipe){
            cout << "\nYou find a pipe that you can use as a container for an explosive." << endl;
            cout << "What do you want to do?" << endl;
            cout << "1. Take the pipe" << endl;
            cout << "2. Leave it" << endl;
            cout << "\nSelection: ";
            choice = integerValidation(1, 2);

            //user chooses to take the pipe  
            if(choice == 1){
                backpack.at(0) = object;
                setObject(none);
                cout << "\nYou now have the pipe" << endl; 
            }
        }
        //user has already taken the pipe but chose to investigate 
        else{
            cout << "\nLooks like you already took the pipe" << endl;
        }
    }
    return true;            //returns true so the game can continue
}

/**************************************************************************************************
** Description: Function is used to inform the user of the different directions them may move, 
                asks the user to choose a direction, and then retunes a pointer to the Space in
                the direction chosen by the user so the player location can be updated.
**************************************************************************************************/
Space* Parts::move(){
    
    int pick = 0;                //stores the user's choice

    cout << "\nWhat direction would you like to move?" << endl;
    cout << "1. Left" << endl;
    cout << "2. Up" << endl;
    cout << "\nSelection: ";
    pick = integerValidation(1, 2);

    //user chooses to go left, so a pointer to the left space is returned    
    if(pick == 1){
        return this->getWest();
    }
    //user chooses to go up, so a pointer to the space above is returned 
    else{
        return this->getNorth();
    }
}

/*******************************************************************************    
** Program Name:Langton's Ant
** Name:        Clinton Hawkes
** Date:        04/08/2019
** Description: Implementation file for the menu functions. The two menu 
                functions have different uses. The mainMenu is used at the 
                start of the program while the secondaryMenu is used at the
                end of the Ant simulation. The logic of these functions is 
                explained below.
*******************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include "validation.hpp"


/*******************************************************************************
** Description: function prints the main menu to the console and asks the user
                to make a selection. The integerValidation function is called
                to read and validate the user's input. If the user wants to 
                start the simulation, true is returned to main. If the user
                wants to quit, false is returned to main.
*******************************************************************************/
int mainMenu(){

    int choice;

    cout << "Welcome to Langton's Ant Simulator." << endl;
    cout << "=======================================================" << endl;
    cout << "1. Start Langont's Ant Simulation." << endl;
    cout << "2. Quit" << endl;
    cout << "Please enter the number next to your selection." << endl;
    
    //gets user input with integerValidation. min=1  max=2 
    choice = integerValidation(1, 2);

    if(choice == 1){        //user want to start simulation 
        return true;
    }
    else                    //user wants to quit
        return false;
}  


/*******************************************************************************
** Description: function prints seconday menu to the console asking user to 
                make a selection. The integerValidation function is used to
                read and validate the user's input. If the user wants to play
                again, true is returned to main. If the user wants to quit, 
                false is returned to main.
*******************************************************************************/
int secondaryMenu(){

    int choice; 
    
    cout << "Langton's Ant Simulator is complete." << endl;
    cout << "=======================================================" << endl;
    cout << "1. Play again." << endl;
    cout << "2. Quit" << endl;
    cout << "Please enter the number next to your selection." << endl;
    
    //gets user input with integerValidation. min=1  max=2 
    choice = integerValidation(1, 2);

    if(choice == 1){        //user wants to start simulation
        return true;
    }
    else                    //user wants to quit
        return false;
}  
    

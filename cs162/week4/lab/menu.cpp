/**************************************************************************************************
** Program Name:OSU Info System
** Author:      Clinton Hawkes
** Date:        04/25/2019
** Description: Menu implementation file. This contains the main menu that is used by the OSU
                Info System. Menu options are printed on the console and the user is able to 
                choose the option they desire. The number chosen is passed back to the calling 
                function for processing.
**************************************************************************************************/

#include "menu.hpp"
#include "validation.hpp"
#include <iostream>
using std::cout;
using std::endl;

int mainMenu(){

    int selection = 0; 

    cout << "              OREGON STATE UNIVERSITY              " << endl;
    cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl << endl;

    cout << "Please select an option from the following list." << endl << endl;

    cout << "1. Print information about all OSU buildings." << endl;
    cout << "2. Print information about everybody at OSU." << endl;
    cout << "3. Choose a person to do work." << endl;
    cout << "4. Exit the program." << endl << endl;
    
    cout << "Selection: ";
    
    //user's input is validated to be correct type and within range.  
    selection = integerValidation(1, 4);

    //returns user's selection back to the calling function. 
    return selection;
}


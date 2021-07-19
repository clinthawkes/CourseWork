/**************************************************************************************************
** Program Name:Final Project 
** Author:      Clinton Hawkes
** Date:        06/9/2019
** Description: Implementation file for the menu function. This function presents that available
                options to the user, user is allowed to enter the value they would like, input 
                validation is ran on the input to ensure it is valid, and then the option the user
                chose is passed back to the main function so the proper function can be called.
**************************************************************************************************/

#include "menu.hpp" 
#include "validation.hpp"
#include <iostream>
using std::cout;
using std::endl;

/**************************************************************************************************
** Description: function is used to start the game. The user is presented with the option to
                play or quit. If the user wants to play the game, an introduction and brief
                set of instructions is printed to the screen before it starts.
**************************************************************************************************/
bool startMenu(){

    int choice = 0;         //stores the user's choice
    
    system("clear"); 
    
    cout << "\n================================================================" << endl;
    cout << "                  Welcome to Disaster Escape               " << endl;
    cout << "================================================================" << endl;
    cout << "\nPlease choose from the following options " << endl;
    cout << "\n1. Play the game" << endl;
    cout << "2. Exit program" << endl;
    cout << "\nSelection: ";

    //user chooses and option and the input validation is ran on the input 
    choice = integerValidation(1, 2);   

    //if user quits, the program will terminate 
    if(choice == 2){
        return false;
    }

    cout << "\nYou are TRAPPED!!! Please remain calm. You have survived the enemy attack," << endl;
    cout << "thanks to your underground bunker, but there is one problem. It's been months" << endl;
    cout << "and you are running out of food/water. The only exit has been sealed shut, so" << endl;
    cout << "you need to find a way to 'blow' the hatch open. Your survival depends on it!" << endl;
    cout << "Search around the bunker for items that can be used to make an explosive." << endl;
    cout << "Once you find all the items, assemble the bomb and get out of there!!!" << endl;
    
    //user's valid choice is returned to the main function 
    return true;

}

/**************************************************************************************************
** Description: Function is used as the main menu throughout the game. Each time the user wants
                to perform an action, this is the menu that will be used. The user's choice will
                be returned to the calling function so the correct function can be called.
**************************************************************************************************/
int menu(){

    int choice = 0;         //stores the user's choice
    
    cout << "\n================================================================" << endl;
    cout << "                       Choose an Option  " << endl;
    cout << "================================================================" << endl;
    cout << "\n1. Investigate" << endl;
    cout << "2. Move around" << endl;
    cout << "3. View backpack contents" << endl; 
    cout << "\nSelection: ";

    //user chooses and option and the input validation is ran on the input 
    choice = integerValidation(1, 3);   
    
    return choice;
}


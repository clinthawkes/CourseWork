/**************************************************************************************************
** Program Name:Linked List 
** Author:      Clinton Hawkes
** Date:        05/05/2019
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

int menu(){

    int choice = 0;         //stores the user's choice
    
    cout << "\n===========================================================" << endl;
    cout << "               Welcome to STL Learning Lab               " << endl;
    cout << "===========================================================" << endl;
    cout << "\nPlease choose from the following options " << endl;
    cout << "\n1. Run buffer simulation" << endl;
    cout << "2. Create a palindrome" << endl;
    cout << "3. Exit program" << endl;
    cout << "\nSelection: ";

    //user chooses and option and the input validation is ran on the input 
    choice = integerValidation(1, 3);   

    //user's valid choice is returned to the main function 
    return choice;

}

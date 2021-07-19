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
    cout << "               Welcome to LinkedList Builder               " << endl;
    cout << "===========================================================" << endl;
    cout << "\nPlease choose from the following options " << endl;
    cout << "\n1. Add a new node to the head" << endl;
    cout << "2. Add a new node to the tail" << endl;
    cout << "3. Delete node from the head" << endl;
    cout << "4. Delete node from the tail" << endl;
    cout << "5. Traverse the list reversely" << endl;
    cout << "6. Print value of the head node" << endl;
    cout << "7. Print value of the tail node" << endl;
    cout << "8. Exit program" << endl;
    cout << "\nSelection: ";

    //user chooses and option and the input validation is ran on the input 
    choice = integerValidation(1, 8);   

    //user's valid choice is returned to the main function 
    return choice;

}

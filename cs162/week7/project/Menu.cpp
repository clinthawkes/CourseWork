/**************************************************************************************************
** Program Name:Fantasy Combat
** Author:      Clinton Hawkes
** Date:        05/01/2019
** Description: Implementation file for the Menu class. The Menu class handles all the object
                creations and function calls for the testing of the characters. Information
                about the Menu functions can be found below.
**************************************************************************************************/

#include "Menu.hpp"
#include "Character.hpp"
#include "validation.hpp"
#include "Vampire.hpp"
#include "Barbarian.hpp"
#include "Medusa.hpp"
#include "BlueMen.hpp"
#include "HarryPotter.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

//default constructor
Menu::Menu(){
}

/**************************************************************************************************
** Description: Function is used for the very first interaction with the user. The user has the
                choice to play the game or quit. The user's choice is returned to the calling
                function.
**************************************************************************************************/
bool Menu::startMenu(){

    int choice = 0;             //stores user's choice from menu

    system("clear");

    cout << "\n                Welcome to Fantasy Combat              " << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
    cout << "Please select from the options: " << endl << endl;
    cout << "1. Play " << endl;
    cout << "2. Quit " << endl;
    cout << "\nSelection: ";
    
    choice = integerValidation(1, 2);

    //choice is returned to the calling function  
    if(choice == 1){
        return true;
    }
    else{
        return false;
    }
}

/**************************************************************************************************
** Description: Function displays the options available to the user and asks them to make a 
                selection. If the user chooses to quit, a nullptr is returned to the calling 
                function and the program terminates. If the user chooses one of the characters
                to assign to player one, that specific type of character is created and a pointer
                referencing that character is returned to the calling function.
**************************************************************************************************/
Character* Menu::menu1(int now, int total){
    
    //holds pointer that will be returned 
    Character* newbie = nullptr; 
    std::string name = ""; 
    int choice = 0;
    
    system("clear"); 

    cout << "\n                Welcome to Fantasy Combat              " << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
    cout << "Please select a character for team 1:" << endl << endl;

    cout << "1. Vampire" << "                     Character " << now << " of " << total << endl;
    cout << "2. Barbarian" << endl;
    cout << "3. Blue Men" << endl;
    cout << "4. Medusa" << endl;
    cout << "5. Harry Potter" << endl << endl;
    cout << "Selection: ";

    choice = integerValidation(1,5);
    
    cout << "\nWhat would you like this fighter's name to be? " << endl;
    cout << "Name:  ";
    getline(cin, name);

        switch(choice){

            case 1: newbie = new Vampire(name);       //vampire is created if user chooses option 1
                    break;

            case 2: newbie = new Barbarian(name);     //barbarian is created if user chooses option 2
                    break;

            case 3: newbie = new BlueMen(name);       //bluemen is created if user chooses option 3
                    break;

            case 4: newbie = new Medusa(name);        //medusa is created if user chooses option 4
                    break;

            case 5: newbie = new HarryPotter(name);   //harrypotter is created if user chooses option 5
                    break;
                    
        }                    
        
    //pointer to the object that was created is returned to the calling function 
    return newbie;               
}

/**************************************************************************************************
** Description: Function displays the options available to the user and asks them to make a 
                selection. If the user chooses to quit, a nullptr is returned to the calling 
                function and the program terminates. If the user chooses one of the characters
                to assign to player one, that specific type of character is created and a pointer
                referencing that character is returned to the calling function.
**************************************************************************************************/
Character* Menu::menu2(int now, int total){
    
    //holds pointer referencing the user's chosen character object 
    Character* newbie = nullptr; 
    std::string name = ""; 
    int choice = 0;
    
    system("clear"); 

    cout << "\n                Welcome to Fantasy Combat              " << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
    cout << "Please select a character for team 2:" << endl << endl;

    cout << "1. Vampire" << "                     Character " << now << " of " << total << endl;
    cout << "2. Barbarian" << endl;
    cout << "3. Blue Men" << endl;
    cout << "4. Medusa" << endl;
    cout << "5. Harry Potter" << endl << endl;
    cout << "Selection: ";

    choice = integerValidation(1,5);

    cout << "\nWhat would you like this fighter's name to be? " << endl;
    cout << "Name:  ";
    getline(cin, name);
    
        switch(choice){

            case 1: newbie = new Vampire(name);       //vampire is created if user chooses option 1
                    break;

            case 2: newbie = new Barbarian(name);     //barbarian is created if user chooses option 2
                    break;

            case 3: newbie = new BlueMen(name);       //bluemen is created if user chooses option 3
                    break;

            case 4: newbie = new Medusa(name);        //medusa is created if user chooses option 4
                    break;

            case 5: newbie = new HarryPotter(name);   //harrypotter is created if user chooses option 5
                    break;
                    
        }                    
    //pointer to the object that was created is returned to the calling function 
    return newbie; 
}

/**************************************************************************************************
** Description: Function is called after the tournament to ask the user if they would like to 
                continue or quit the game. 
**************************************************************************************************/
bool Menu::endMenu(){

    int answer = 0;             //stores user's choice from menu

    cout << "\n\nPlease select an option below." << endl;
    cout << "1. Play again" << endl;
    cout << "2. Exit" << endl;
    cout << "Selection: ";

    //if user quits, 0 is returned. if user continues, 1 is returned 
    answer = integerValidation(1, 2);
    
    if(answer == 1){
        return true;
    }
    else{
        return false;
    }
}

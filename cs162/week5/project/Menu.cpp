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
** Description: Function displays the options available to the user and asks them to make a 
                selection. If the user chooses to quit, a nullptr is returned to the calling 
                function and the program terminates. If the user chooses one of the characters
                to assign to player one, that specific type of character is created and a pointer
                referencing that character is returned to the calling function.
**************************************************************************************************/
Character* Menu::menu1(){
    
    //holds pointer that will be returned 
    Character* newbie = nullptr; 
    int choice = 0;
    
    system("clear"); 

    cout << "\n                Welcome to Fantasy Combat              " << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
    cout << "Please select the first of two characters you want to battle:" << endl << endl;

    cout << "1. Vampire" << endl;
    cout << "2. Barbarian" << endl;
    cout << "3. Blue Men" << endl;
    cout << "4. Medusa" << endl;
    cout << "5. Harry Potter" << endl;
    cout << "6. Quit Game" << endl << endl;
    cout << "Selection: ";

    choice = integerValidation(1,6);

        switch(choice){

            case 1: newbie = new Vampire;       //vampire is created if user chooses option 1
                    break;

            case 2: newbie = new Barbarian;     //barbarian is created if user chooses option 2
                    break;

            case 3: newbie = new BlueMen;       //bluemen is created if user chooses option 3
                    break;

            case 4: newbie = new Medusa;        //medusa is created if user chooses option 4
                    break;

            case 5: newbie = new HarryPotter;   //harrypotter is created if user chooses option 5
                    break;

            case 6: return nullptr;             //nullptr is returned if user wants to quit
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
Character* Menu::menu2(Character* p1){
    
    //holds pointer referencing the user's chosen character object 
    Character* newbie = nullptr; 
    int choice = 0;
    
    system("clear"); 

    cout << "\n                Welcome to Fantasy Combat              " << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
    cout << "Please select the second of two characters you want to battle:" << endl << endl;

    cout << "1. Vampire" << "                     First character is a " << p1->getType() << endl;
    cout << "2. Barbarian" << endl;
    cout << "3. Blue Men" << endl;
    cout << "4. Medusa" << endl;
    cout << "5. Harry Potter" << endl;
    cout << "6. Quit Game" << endl << endl;
    cout << "Selection: ";

    choice = integerValidation(1,6);

        switch(choice){

            case 1: newbie = new Vampire;       //vampire is created if user chooses option 1
                    break;

            case 2: newbie = new Barbarian;     //barbarian is created if user chooses option 2
                    break;

            case 3: newbie = new BlueMen;       //bluemen is created if user chooses option 3
                    break;

            case 4: newbie = new Medusa;        //medusa is created if user chooses option 4
                    break;

            case 5: newbie = new HarryPotter;   //harrypotter is created if user chooses option 5
                    break;

            case 6: return nullptr;             //nullptr is returned if user chooses to quit
                    break;
                    
        }                    
    //pointer to the object that was created is returned to the calling function 
    return newbie; 
}

/**************************************************************************************************
** Description: This function is the brains of the testing program. It is responsible for creating 
                pointers to the different types of characters chosen by the user, calling menus,
                creating battle loops, calling the various functions for the characters and 
                displaying all the information to the user for testing purposes.
**************************************************************************************************/
void Menu::test(){
    
    bool game = true;
    Character* p1 = nullptr;        //pointer to player 1 object
    Character* p2 = nullptr;        //pointer to player 2 object
    Character* winner = nullptr;    //pointer to the winner of the battle

     
    while(game == true){ 
      
        //menu1 asks user to choose a character for player 1 and the address to the object is returned to p1 
        p1 = menu1(); 
        //if user chose to quit in the menu, the program will terminate 
        if(p1 == nullptr){
            return;
        }
       
        //menu2 asks user to choose a character for player 2 and the address to the object is returned to p2 
        p2 = menu2(p1); 
        //if user chose to quit in the menu, the program will terminate 
        if(p2 == nullptr){
            return;
        }
      
        bool battle = true; 
        int rnd = 1,                //round counter
            p1Roll = 0,             //holds attack and inflicted damage values for player 1
            p2Roll = 0;             //holds attack and inflicted damage values for player 2
        std::string victor = "";    //halds the victors type variable
              

        while(battle == true){
                      
            //if round number is even 
            if(rnd%2 == 1){ 
                
                cout << "\nRound number " << (rnd + 1) / 2 << endl; 
                cout << "___________________________________________________________________________" << endl; 
                cout << "Player 1 the attacker is a " << p1->getType() << "." << endl;
                cout << "Player 2 the defender is a " << p2->getType() << ". Armor is " << p2->getArmor() 
                     << ". Strength Points is a " << p2->getSP() << "." << endl;
                
                //player 1 attack function returns an attack value to be passes to player 2 defense 
                p1Roll = p1->attack();
                
                cout << "Attacker rolled a " << p1Roll << "." << endl;
                
                //player 2 defense function returns the actual inflicted damage value 
                p2Roll = p2->defense(p1Roll);
                
                cout << "Total inflicted damage was " << p2Roll << "." << endl;
                cout << "Player 2 the defender's updated Strength Points is " << p2->getSP() << "." << endl;
                
                //if the defender has sp of 0 or less, the defender loses 
                if(p2->getSP() <= 0){
                    
                    cout << "Player 1 wins" << endl;
                    cout << "___________________________________________________________________________" << endl; 
                    winner = p1; 
                    victor = "Player 1 "; 
                    battle = false; 
                }
                
                rnd++;
            }
            else {
                
                cout << "\nPlayer 2 the attacker is a " << p2->getType() << "." << endl;
                cout << "Player 1 the defender is a " << p1->getType() << ". Armor is " << p1->getArmor() 
                     << ". Strength Points is a " << p1->getSP() << "." << endl;
                
                //player 2 attack function returns an attack value to be passes to player 1 defense 
                p2Roll = p2->attack();
                
                cout << "Attacker rolled a " << p2Roll << "." << endl;
                
                //player 1 defense function returns the actual inflicted damage value 
                p1Roll = p1->defense(p2Roll);
                
                cout << "Total inflicted damage was " << p1Roll << "." << endl;
                cout << "Player 1 the defender's updated Strength Points is " << p1->getSP() << "." << endl;
                
                //if the defender has sp of 0 or less, the defender loses 
                if(p1->getSP() <= 0){
                    cout << "Player 2 wins" << endl;
                    winner = p2; 
                    victor = "Player 2 "; 
                    battle = false; 
                }
                
                cout << "___________________________________________________________________________" << endl; 
                
                rnd++;             
            }            
        }        
        
        cout << "\n\n******************************************************************************" << endl;
        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "=======================    WINNER OF THE BATTLE IS   =========================" << endl;
        cout << "                             " << victor << winner->getType() << endl;
        cout << "==============================================================================" << endl;
        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "******************************************************************************" << endl;
            
        //player 1 character object is deleted  
        delete p1;
        p1 = nullptr;
        
        //player 2 character object is deleted 
        delete p2;
        p2 = nullptr;
        
        winner = nullptr; 
        
        //small menu is called asking user if they want to continue or quit 
        game = endMenu(); 

    }
}

/**************************************************************************************************
** Description: Function is called after each round to ask the user if they would like to continue
                or quit the game. 
**************************************************************************************************/
bool Menu::endMenu(){

    bool answer = true;

    cout << "\nWould you like to Continue or Quit? (1=Continue / 0=Quit)" << endl << endl;

    cout << "Selection: ";

    //if user quits, 0 is returned. if user continues, 1 is returned 
    answer = integerValidation(0, 1);

    return answer;
}

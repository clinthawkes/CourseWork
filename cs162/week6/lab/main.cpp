/**************************************************************************************************
** Program Name:Linked List
** Author:      Clinton Hawkes
** Date:        05/05/2019
** Description: Implementation file for the main function. The main function is responsible for 
                creating a LinkedList object, calling the menu function to allow user to choose
                what function they want to call, and then calling the function that the user
                chose. This repeats until the user selects that they want to quit the program.
**************************************************************************************************/

#include "LinkedList.hpp"
#include "menu.hpp"
#include <iostream>
using std::cout;
using std::endl;

int main(){

    bool state = true;              //controls the state of the program. false = quit
    int choice = 0;                 //stores the option the user chooses
    LinkedList list;                //object used to build the linked list
 
    system("clear"); 

    while(state == true){           //program will run until this is false
        
        choice = menu();            //menu called to present options to user
        
        switch(choice){

            //will create a new node at the head of the list when user chooses 1 
            case 1: list.newHead(); 
                    break; 
                    
            //will create a new node at the tail of the list when user chooses 2 
            case 2: list.newTail();
                    break; 
        
            //will remove the node at the head of the list if one exists         
            case 3: list.rmHead();
                    break; 
                    
            //will remove the node at the tail of the list if one exists 
            case 4: list.rmTail();
                    break; 
                    
            //will display the values of each node in the list from tail to head        
            case 5: list.revTraverse(); 
                    break; 
                    
            //will display the value stored in the node at the head of the list 
            case 6: list.printHead(); 
                    break; 
                    
            //will display the value stored in the node at the tail of the list        
            case 7: list.printTail();
                    break; 
                    
            //will terminate the program if the user chooses to do so 
            case 8: state = false;
                    break;
        
        } 
    } 
    
    return 0;
}

/**************************************************************************************************
** Program Name:Circular List
** Author:      Clinton Hawkes
** Date:        05/15/2019
** Description: Implementation file for the menu function. This function presents that available
                options to the user, user is allowed to enter the value they would like, input 
                validation is ran on the input to ensure it is valid, and then the option the user 
                chose is implemented through a switch statement and function calls.
**************************************************************************************************/

#include "Queue.hpp"
#include "menu.hpp" 
#include "validation.hpp"
#include <iostream>
using std::cout;
using std::endl;

void menu(){

    Queue list;             //foundational object of the circular linked list
    int choice = 0,         //stores the user's choice
        value = 0;          //stores the user's integer input 
    bool state = true;      //controls state of the program(run or quit)
    
    while(state){

        cout << "\n===========================================================" << endl;
        cout << "          Welcome to Circular LinkedList Builder           " << endl;
        cout << "===========================================================" << endl;
        cout << "\nPlease choose from the following options " << endl;
        cout << "\n1. Enter value to be added to the back of queue" << endl;
        cout << "2. Display first node (front) value" << endl;
        cout << "3. Remove first node (front) value" << endl;
        cout << "4. Display the queue contents" << endl;
        cout << "5. Exit program" << endl;
        cout << "\nSelection: ";

        //user chooses and option and the input validation is ran on the input 
        choice = integerValidation(1, 5);   

        switch(choice){

            case 1: cout << "\nWhat value do you want to enter? (min=-10000/max=10000)" << endl;
                    value = integerValidation(-10000, 10000);
                    
                    //node with the user's input is added to the back of the list 
                    list.addBack(value);
                    break;
                    
            case 2: //value of front node is printed if the list is not empty 
                    if(list.isEmpty()){
                        
                        cout << "\n*** ERROR: Nothing to return ***" << endl;
                    }
                    else{
                        
                        cout << "\nThe first node value is: " << list.getFront() << endl;
                    } 
                    break;
                    
            case 3: //if there is a node in the list, the front node is removed from the list 
                    if(list.isEmpty()){
                        
                        cout << "\n*** ERROR: Nothing to remove ***" << endl;
                    } 
                    else{    
                        
                        list.removeFront();
                    }                        
                    break;
                    
            case 4: //list is printed from the head to the end 
                    if(list.isEmpty()){
                        
                        cout << "\n*** Queue is empty ***" << endl;
                    } 
                    else{    
                        
                        list.printQueue();
                    }                        
                    break;
                    
            case 5: //program terminates if user chooses option 5 
                    state = false;
                    break;
                    
        }
    }
}

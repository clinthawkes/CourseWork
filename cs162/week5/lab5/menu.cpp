/**************************************************************************************************
** Program Name:Recursive Functions 
** Author:      Clinton Hawkes
** Date:        05/01/2019
** Description: This is the implementation file for the menu function. The menu function is the 
                brains of this assignment. First the user is presented with options to test out
                three different recursive functions. First is the string reversal where the 
                function will reverse a string the user provides. Second is a function that will 
                sum a list of numbers provided by the user. Third is a function that will calculate
                the triangle number of an integer provided by the user.
**************************************************************************************************/

#include "menu.hpp"
#include "validation.hpp"
#include "stringReverse.hpp"
#include "sumOfArray.hpp"
#include "triangularNumber.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int menu(){
    
    bool state = true; 
    
    //program will run until user chooses to quit 
    while(state == true){ 
    
        int choice = 0, 
            input = 0,
            size = 0;
        int* numArray = nullptr;        //holds numbers provided by user to be summed
        std::string userString = "";    //holds string provided by user 
        
        system("clear"); 

        cout << "\n                Welcome to the Lab 5 Main Menu        " << endl;
        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl << endl;
        cout << "Please select from the options below:" << endl << endl;

        cout << "1. Print a string in reverse" << endl;
        cout << "2. Sum a list of integers" << endl;
        cout << "3. Calculate the triangle number of an integer" << endl;
        cout << "4. Exit program " << endl << endl; 
        cout << "Selection: ";

        choice = integerValidation(1,4);

            switch(choice){

                case 1: cout << "\nPlease type the string you would like printed in " 
                             << "reverse. (ending with enter)" << endl << endl;
                        
                        //gets the string that the user wants printed in reverse 
                        getline(cin, userString);
                        cout << endl;   //adds empty line for formatting output
                        
                        //prints out the user's string in reverse 
                        stringReverse(userString);
                        
                        //pauses the console so user can see the string printed in reverse 
                        cout << endl << "Press enter to continue... ";
                        cin.get();
                        
                        break;

                case 2: cout << "\nHow many integers would you like to sum? (min=2/max=100)" << endl << endl;
                        
                        //gets a value for the number of ints the user wants to sum 
                        size = integerValidation(2,100); 
                        
                        //creates an array to hold the numbers to be summed 
                        numArray = new int[size];
                        
                        cout << "\nPlease enter the " << size << " integers you would like " 
                             << "to sum. (min=-1000000/max=1000000)" << endl; 
                        
                        //asks user for the numbers, one by one, and stores them in the array 
                        for(int i = 0; i < size; i++){
                            cout << "\nInteger #" << i+1 << ": "; 
                            numArray[i] = integerValidation(-1000000, 1000000);
                        }
                        
                        //prints out the sum of all the numbers entered by the user 
                        cout << "\nThe sum of your integers is " << sumOfArray(numArray, size) << "." << endl << endl;
                        
                        //pauses the console so the user can see the sum 
                        cout << "Press enter to continue...";
                        cin.get();
                        
                        //deletes the array that was created to store the user's numbers 
                        delete [] numArray;
                        
                        break;

                case 3: cout << "\nPlease enter the integer for which you would like to calculate " 
                             << "the triangle number. (min=1/max=10000)" << endl << endl;
                        
                        //asks user to enter a number for which they want the triangle number 
                        input = integerValidation(1, 10000);
                        
                        //calculates and outputs the triangle number for the user 
                        cout << "\nThe triangle number of " << input << " is " 
                             << triangularNumber(input) << "." << endl << endl;
                        
                        //pauses the console so the user can see the triangle nubmer 
                        cout << "Press enter to continue...";
                        cin.get();
                        
                        break;

                        //quits program if user chooses option 4 
                case 4: state = false;
                        break;

                        
            }
        }
    return 0; 
}

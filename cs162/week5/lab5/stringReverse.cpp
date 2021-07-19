/**************************************************************************************************
** Program Name:Recursive Functions
** Author:      Clinton Hawkes
** Date:        05/01/2019
** Description: This is the implementation file for the string reversal function using recursion.
                The function takes in a string argument and then prints it out to the console
                letter by letter in reverse.
**************************************************************************************************/

#include "stringReverse.hpp"
#include <iostream>

void stringReverse (std::string stringIn){
    
    //newline character is returned when size of the string is 0 
    if(stringIn.size() < 1){ 
        std::cout << "\n"; 
    } 
    //starting from the end, prints out characters in string one by one until the start of the 
    //string is reached
    else{
        std::cout << stringIn.at(stringIn.size()-1); 
        stringReverse(stringIn.substr(0, stringIn.size()-1));
    }

}

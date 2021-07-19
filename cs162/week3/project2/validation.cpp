/*******************************************************************************    
** Program Name:Zoo Tycoon
** Name:        Clinton Hawkes
** Date:        04/25/2019
** Description: Implementation file for the validation functions. The two 
                validation functions below have different applications. The 
                integerValidation is used for integers and the yesNoValidation
                function is used when yes or no is required. The logic of
                these functions is explained below.
*******************************************************************************/

#include "validation.hpp"
#include <string>
#include <iostream>
#include <sstream>


/*******************************************************************************
** Description: function take in two int parameters as the minimum and maximum
                values the user's integer input can be. User now enters some 
                value, the value is streamed into the variable "answer", and if
                the stream reaches the end of the stream with no errors, the 
                value is checked against the min and max values passed as
                parameters. If the user's input passes both these tests, the
                user's value is returned to main.
*******************************************************************************/
int integerValidation(int min, int max){
    
    bool state = false;         //used to control while loop 
    std::string value;          //stores user's input
    int answer;            //stores validated integer to be returned 
    
    while(state == false){
        
        //captures user's input from console and stores in value variable 
        std::getline(std::cin, value); 
        std::stringstream ss(value);
        
        //if user's input passes test and is in valid range, value is returned 
        if((ss >> answer) && ss.eof()){
            if(answer >= min && answer <= max){ 
                state = true;
            } 
            //if tests fail, user is asked for another entry 
            else{
                std::cout << "Please enter a valid integer." << std::endl;
            } 
        } 
        else{
            std::cout << "Please enter a valid integer." << std::endl;
        }            
    }
        
    std::cin.clear(); 
    return answer; 
}


/*******************************************************************************
** Description: function captures user's input and stores it in the variable
                "input". The first character of the user's input is made into
                lower case and stored in the variable "letter". If the value of
                "letter" is == y or ==n, then "letter" is returned to main. If
                "letter" is not a y or n, then user is propted for new entry.
                Function will continue to loop until a valid entry is entered.
*******************************************************************************/
char yesNoValidation(){
    
    std::string input;          //stores user input
    char letter;                //stores lower case letter
    bool status = false;        //controls while loop

    while(status == false){

        std::cin >> input;

        //first character of user's input is converted to lower case  
        letter = tolower(input[0]); 
    
        //if lower letter is y or n, loop ends and letter is returned to main 
        if(letter == 'y' || letter == 'n'){
            status = true;
        } 
        
        //if lower letter is not y or n, user is prompted for new entry 
        else{
            std::cout << "Please enter yes or no." << std::endl;
        }            
    }
    std::cin.ignore(); 
    return letter; 

}



/*******************************************************************************    
** Program Name:File I/O
** Name:        Clinton Hawkes
** Date:        04/10/2019
** Description: Implementation file containing the logic for the count_letters
                function. Details can be found below.
*******************************************************************************/

#include "count_letters.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>

/*******************************************************************************
** Description: The function takes in two arguements: an ifstream object being
                read from by reference and an array of ints. First the array of
                ints is reset so all values in array are set to 0. Then the 
                function reads one paragraph from the input file and stores it
                in a string variable. All letters in the string are converted 
                to lower case letters and a loop is used to count the frequency
                of each letter in to alphabet. The frequency is then stored in
                the array.
*******************************************************************************/
void count_letters(std::ifstream& input, int* count){

    std::string paragraph;      //stores current paragraph
    int position;
    char letter; 
    
    //sets all array values to zero 
    for(int a = 0; a < 26; a++){
        count[a] = 0;}

    //reads a paragraph from the input file and stores it as a string 
    std::getline(input, paragraph);

        //loops through the string and counts the frequency of each alphabet letter 
        for(int i = 0; i < paragraph.length(); i++){
            letter = tolower(paragraph[i]); 
            if(letter >= 'a' && letter <= 'z'){
                position = letter - 'a';
                count[position]++;
            }
        }
}


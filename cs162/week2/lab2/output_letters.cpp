/*******************************************************************************    
** Program Name:File I/O
** Name:        Clinton Hawkes
** Date:        04/10/2019
** Description: Implementation file containing the logic for the output_letters
                function. Details can be found below.
*******************************************************************************/

#include "output_letters.hpp"
#include <iostream>
#include <fstream>
#include <string>

/*******************************************************************************
** Description: function takes in two arguements: an ofstream object by ref. and 
                an array of ints. First, the function checks to see if the 
                current working paragraph is empty. If it is empty, the function
                exits and the write process is skipped. If the paragraph was not
                empty, each letter of the alphabet and its frequency in the 
                paragraph is written to the output file. The user is prompted
                to name the output file to their liking.
*******************************************************************************/
void output_letters(std::ofstream &output, int* count){

    std::string fileName;       //stores output file name
    char character; 
    int sum = 0;
/*
    //sums the total alphabet count in the array     
    for(int j = 0; j < 26; j++){
        sum += count[j];
    }
     
    //if the last paragraph was empty, the function skips the writing process  
    if(sum == 0){
        return;
    }
 */   
    std::cout << "What would you like your output file to be named?" << std::endl;
    std::cin >> fileName;       //get file name from user

    output.open(fileName);      //file is opened for writing

    //writes each letter of the alphabet the its frequency in the previous 
    //paragraph to the output file.
    for(int i = 0; i < 26; i++){
        character = i + 'a';
        output << character << ':' << ' ' << count[i] << std::endl << std::endl;
    }
    
    output.close();         //closes output file
}

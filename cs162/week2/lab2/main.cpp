/*******************************************************************************    
** Program Name:File I/O
** Name:        Clinton Hawkes
** Date:        04/10/2019
** Description: Program is used to open and read a text file one paragraph at a
                time, count the frequency of each alphabet letter in the 
                paragraph, ask user what the name of the output file should be 
                for the current paragraph, and then write the frequency of each
                alphabet letter contained in the paragraph to the output file
                named by the user. This is repeated until the end of the input
                text file is reached.
*******************************************************************************/

#include "count_letters.hpp"
#include "output_letters.hpp"
#include <iostream>
#include <fstream>

int main(){

    int freq[26] = {0};     //hold the frequency of the alphabet letters
    std::ifstream ifs;      //object used to read a text file   
    std::ofstream ofs;      //object used to write the frequency results
    std::string inFile;     //stores input file name
     
    ifs.open("file_fun.txt");

    //if the file above is not opened, the following loop asks user to enter a
    //valid file name until a file is successfully opened.
    while(ifs.fail()){
        std::cout << "Please enter a valid file name to read from." << std::endl;
        std::cin >> inFile; 
        ifs.open(inFile);
    }
    
    //reads a paragraph from the input file, counts the frequency of letters,
    //writes the frequencies to an output file, and repeats until eof is reached.
    while(!ifs.eof()){ 
        count_letters(ifs, freq);   //reads ifs and saves letter frequency to freq
        output_letters(ofs, freq);  //writes frequency of letters (freq) to ofs
    } 

    return 0; 
}

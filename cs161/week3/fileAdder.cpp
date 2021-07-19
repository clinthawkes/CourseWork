/*****************************************************************************************************
 * Name:        Clinton Hawkes  
 * Date:        01/19/2019
 * Description: Asks for the name of a file containing a list of integers to open and read. The 
 *              program will sum all the integers in the file. A file named sum.txt will be created
 *              and the sum will be written to it. A confirmation message will be printed if 
 *              everything was successful. 
*****************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    std::ifstream inputFile;        //declare ifstream variable
    std::ofstream outputFile;       //declare ofstream variable
    std::string readFile;           //declare string variable
    int total = 0,                  //declare int variables
        value;

    //asks user to enter filename containing ints to be summed 
    cout << "Please enter your filename." << endl;
    cin >> readFile;

    //open the input file
    inputFile.open(readFile);

    //verifies the filename accurate and usable and informs user if it is not 
    if (inputFile.fail())
        cout << "could not access file" << endl;
    else
    {
        //loop reads values and adds them to total until end of file is reached then closes file
        while (inputFile >> value) 
            total += value;
     
        inputFile.close(); 
        
        //open the output file, record total, and close output file
        outputFile.open("sum.txt");
        outputFile << total << endl;
        outputFile.close(); 
        
        //prints confirmation when input file is read and the sum is recorded to output file 
        cout << "result written to sum.txt" << endl;
    } 
    return 0;
}


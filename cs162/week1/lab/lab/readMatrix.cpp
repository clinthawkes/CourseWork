/*******************************************************************************    
** Program Name:Matrix Calculator
** Author:      Clinton Hawkes
** Date:        04/02/2019 
** Description: Implementation file for the readMatrix function 
*******************************************************************************/

#include "readMatrix.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void readMatrix(int** pointer, int size){ 

    //asks user to enter a specific quanitity of numbers to fill the matrix. 
    cout << "Please enter the " << (size*size) << " numbers for the matrix." << endl;
    cout << "The numbers will be filled in by row moving from left to right." << endl;

    //fills in the matrix with the user input according to the order indicated above 
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cin >> pointer[i][j];
        }
}}

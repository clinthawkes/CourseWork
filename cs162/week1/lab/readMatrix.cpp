
/*******************************************************************************    
** Program Name:
** Name:        Clinton Hawkes04/02/2019
** Date:        
** Description: 
*******************************************************************************/

#include "readMatrix.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void readMatrix(int** pointer, int size){ 

    cout << "Please enter the " << (size*size) << " numbers for the matrix." << endl;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cin >> pointer[i][j];
        }
}}

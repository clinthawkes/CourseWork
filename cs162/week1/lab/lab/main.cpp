/*******************************************************************************    
** Program Name:Matrix Calculator 
** Author:      Clinton Hawkes
** Date:        04/02/2019
** Description: Main implementation file for the Matrix Calculator program.
                Program asks user for what size of matrix they need to calculate
                a determinant, asks user to fill in the matrix values, and then
                calculates and returns the result to the console.
*******************************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include "readMatrix.hpp"
#include "determinant.hpp"

int main(){

    int sizeOfMatrix,
        result; 

    cout << "Enter 2 if you need a 2x2 matrix, or enter 3 if you need a 3x3 matrix." << endl;
    cin >> sizeOfMatrix;

    //verifies the number entered is a 2 or a 3 
    while(sizeOfMatrix < 2 || sizeOfMatrix > 3){
        cout << "Please enter a valid number." << endl;
        cin >> sizeOfMatrix;}
    
    //dynamically creates a 2d array of ints 
    int** matrix = new int*[sizeOfMatrix];
    for(int i = 0; i < sizeOfMatrix; i++){
        matrix[i] = new int[sizeOfMatrix];
    } 

    //uses the readMatrix function to fill in the 2d array 
    readMatrix(matrix, sizeOfMatrix);

    //uses the determinant function to find the determinant of the 2d array 
    result = determinant(matrix, sizeOfMatrix);

    //clears the console so the result appears 'cleaner' 
    system("clear"); 
    
    //displays the 2d array on the console 
    for(int k = 0; k < sizeOfMatrix; k++){
        for(int j = 0; j < sizeOfMatrix; j++){
            cout << " " << matrix[k][j] << " ";
        }
        cout << endl;
    }

    //displays the determinant of the 2d array on the console 
    cout << "\nThe determinant of the matrix is " << result << "." << endl;

    //the remaining lines are memory deletion and cleanup 
    for(int j = 0; j < sizeOfMatrix; j++){
        delete [] matrix[j];
    } 
    
    delete [] matrix;
    
    matrix = nullptr;

    return 0;
}

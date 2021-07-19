/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        04/02/2019
** Description: 
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

    while(sizeOfMatrix < 2 || sizeOfMatrix > 3){
        cout << "Please enter a valid number." << endl;
        cin >> sizeOfMatrix;}
    
    int** matrix = new int*[sizeOfMatrix];
    for(int i = 0; i < sizeOfMatrix; i++){
        matrix[i] = new int[sizeOfMatrix];
    } 

    readMatrix(matrix, sizeOfMatrix);

    result = determinant(matrix, sizeOfMatrix);

    system("clear"); 
    
    for(int k = 0; k < sizeOfMatrix; k++){
        for(int j = 0; j < sizeOfMatrix; j++){
            cout << " " << matrix[k][j] << " ";
        }
        cout << endl;
    }

    cout << "\nThe determinant of the matrix is " << result << "." << endl;

    for(int j = 0; j < sizeOfMatrix; j++){
        delete [] matrix[j];
    } 
    
    delete [] matrix;
    
    matrix = nullptr;

    return 0;
}

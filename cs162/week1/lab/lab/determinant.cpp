/*******************************************************************************    
** Program Name:Matrix Calculator
** Author:      Clinton Hawkes
** Date:        04/02/2019
** Description: Implementation file for the determinant function. Calculates
                the determinants of the matrix.
*******************************************************************************/

#include "determinant.hpp"


int determinant(int** pointer, int size){

    //calculates  and returns the determinant of the matrix if it's size is 2x2 
    if(size == 2){
        
        return ((pointer[0][0])*(pointer[1][1]))-((pointer[0][1])*(pointer[1][0]));
    }
    
    //calculates and returns the determinant of the matix if it's size is 3x3 
    else{
        int a = pointer[0][0],     //initializes to first value in top row of matrix
            b = pointer[0][1],     //initializes to second value in top row of matrix
            c = pointer[0][2],     //initializes to third value in top row of matrix
            det1,
            det2,
            det3;
    
        //calculates the determinants of the sub matricies needed in the final calculation 
        det1 = ((pointer[1][1])*(pointer[2][2]))-((pointer[1][2])*(pointer[2][1]));
        det2 = ((pointer[1][0])*(pointer[2][2]))-((pointer[1][2])*(pointer[2][0]));
        det3 = ((pointer[1][0])*(pointer[2][1]))-((pointer[1][1])*(pointer[2][0]));

        //returns the determinant of the 3x3 matrix 
        return (a * det1) - (b * det2) + (c * det3);
    } 
}


/*******************************************************************************    
** Program Name:
** Name:        Clinton Hawkes
** Date:        
** Description: 04/02/2019
*******************************************************************************/

#include "determinant.hpp"


int determinant(int** pointer, int size){

    if(size == 2){
        
        return ((pointer[0][0])*(pointer[1][1]))-((pointer[0][1])*(pointer[1][0]));
    }
    
    else{
        int a = pointer[0][0],     
            b = pointer[0][1],
            c = pointer[0][2],
            det1,
            det2,
            det3;

        det1 = ((pointer[1][1])*(pointer[2][2]))-((pointer[1][2])*(pointer[2][1]));
        det2 = ((pointer[1][0])*(pointer[2][2]))-((pointer[1][2])*(pointer[2][0]));
        det3 = ((pointer[1][0])*(pointer[2][1]))-((pointer[1][1])*(pointer[2][0]));

        return (a * det1) - (b * det2) + (c * det3);
    } 
}


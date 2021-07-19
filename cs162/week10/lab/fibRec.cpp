/**************************************************************************************************
** Program Name:Recursive Fibonacci Function
** Author:      Clinton Hawkes
** Date:        06/04/2019
** Description: Implementation file for the recursive function. 
                ***Algorithm taken from resource provided in lab specs. (Code Project)
**************************************************************************************************/

#include "fibRec.hpp"

long fibRec(const int n){

    if(n == 0){
        return 0;               //first base case
    }
    else if(n == 1){
        return 1;               //second base case
    }
    //call recursive function for two prior terms and then sum them and return the sum 
    return fibRec(n-1) + fibRec(n-2);   
}

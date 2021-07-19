/**************************************************************************************************
** Program Name:Iterative Fibonacci Function
** Author:      Clinton Hawkes
** Date:        06/04/2019
** Description: Implementation file for the iterative function. Take in an int and computes that
                fibonacci term.
                ***Algorithm taken from resource provided in lab specs. (Code Project)
**************************************************************************************************/

#include "fibNonRec.hpp"

long fibNonRec(const int n){

    long first = 0;             //first term in the calculation
    long second = 1;            //second term in the calculation
    long counter = 2;           //starts calculation at the third term

    while(counter < n){

        //computes the specified fibonacci term 
        long temp = second;
        second = first + second;
        first = temp;
        ++counter;
    }

    //must return 0 if n is 0. There are no terms below n = 0 to use for calculations 
    if(n == 0){
        return 0;
    }
    else{
        return first + second;
    }
}

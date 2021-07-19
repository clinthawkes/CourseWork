/**************************************************************************************************
** Program Name:Recursive Functions
** Author:      Clinton Hawkes
** Date:        05/01/2019
** Description: This is the implementation file for the array of ints summing function. There are
                two arguments passed to this function, a pointer to an array of ints and an int
                stating how many numbers are in the array. The function sums the numbers in the
                array using recursion. 
**************************************************************************************************/

#include "sumOfArray.hpp"
#include <iostream>

int sumOfArray(int* array, int num){ 

    //function ends when the last number to be summed is passed to the function (0) 
    if(num < 1){
        return 0;
    }
    //numbers in array are summed using recursion 
    else{
        return array[num-1] + sumOfArray(array, num-1);
    } 
    
}

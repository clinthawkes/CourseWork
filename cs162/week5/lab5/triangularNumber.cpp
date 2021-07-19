/**************************************************************************************************
** Program Name:Recursive Functions
** Author:      Clinton Hawkes
** Date:        05/01/2019
** Description: This is the implementation file for the function that calculates the triangle 
                number of a an int passed to it as an argument. The function calculates the
                triangle number using recursion. The number passed to the function is added to the
                sum, then a number one less is added to the sum, then a number one less is 
                added to the sum..... until a number one less == 0. The sum is then returned. 
**************************************************************************************************/

#include "triangularNumber.hpp"

int triangularNumber(int number){

    //if the number passed to the function is 0, the function ends 
    if(number < 1){
        return 0;
    }
    //if the number is bigger than 0, recursion is used calculate the triangle number 
    else{
        return number + triangularNumber(number - 1);
    }
}

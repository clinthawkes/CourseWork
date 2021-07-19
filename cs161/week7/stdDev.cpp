/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/15/2019
** Description: File contains a function named stdDev that takes in an array of
                Person objects for the first parameter and an int relaying the
                size of the array for the second parameter. The function 
                calculates the standard deviation of the Person object's age
                variable. It returns the standard deviation as a double.
*******************************************************************************/
#include "Person.hpp"
#include <cmath>

//function calculates the standard deviation of the ages of the list of 
//Person objects. This is explained above in the description.
double stdDev(Person list[], int size)
{
    int sum = 0;                //initializing all variables to zero
    double mean = 0,
           diff = 0;

    //loops through the list of Person objects and sums the age values 
    for(int x=0; x < size; x++)
        sum += list[x].getAge();

    //calculates the mean age of Persons in the list
    mean = (double)sum / size;

    //loops through the list of Persons and calculates the mean difference 
    for(int x=0; x < size; x++) 
        diff += std::pow(mean-list[x].getAge(), 2);
    
    //calculates the standard deviation of ages and returns it as a double 
    return std::sqrt(diff/size);
}

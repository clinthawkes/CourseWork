/*******************************************************************************    
** Program Name:War Games
** Author:      Clinton Hawkes
** Date:        04/16/2019
** Description: Implementation file for the Die class. This is the parent class
                to the LoadedDie class. Function of this class is storage of 
                a number in N which is a number chosen by the user to indicate
                number of sides on a die. Also, a random number generator is
                included to simulate the roll of a die.
*******************************************************************************/

#include "Die.hpp"
#include <cstdlib>

//default constructor
Die::Die(){
    N = 0;
}

//default destructor
Die::~Die(){
}

//setter for the N variable
void Die::setN(int number){
    N = number;
}

//getter for the N variable
int Die::getN() const {
    return N;
}


/*******************************************************************************
** Description: Function generates a random number between 1 and the number
                of sides found on the die(variable N). The random number is 
                generated using the rand() function and has been seeded in the
                main function.
*******************************************************************************/
int Die::rollDie(){
    
    return (rand()%N + 1);
}
 

/**************************************************************************************************
** Program Name:Zoo Tycoon
** Author:      Clinton Hawkes
** Date:        04/21/2019
** Description: Main function for the Zoo Tycoon. The main plays a very small part in this project.
                All the main function does is seed the random number generator, creates the Zoo
                object and then calls the Zoo run function. All the brains can be found in the
                Zoo class files.
**************************************************************************************************/

#include "Zoo.hpp"
#include <cstdlib>
#include <ctime>

int main(){

    //seeds the random number generator 
    srand(time(NULL));

    Zoo myZoo;

    myZoo.run();

    return 0;

}

    

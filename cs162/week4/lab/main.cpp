/**************************************************************************************************
** Program Name:OSU Info System
** Author:      Clinton Hawkes
** Date:        04/24/2019
** Description: Main function file for the OSU Info System. This file is only used to seed the 
                rand() function, create a University object and then call the run function on the
                University object to start the program.
**************************************************************************************************/

#include "University.hpp"
#include <cstdlib>
#include <ctime>

int main(){

    //seeding the random number generator 
    srand(time(NULL));

    //create University object 
    University osu;

    //starts the Info system program 
    osu.run();

    return 0;
}

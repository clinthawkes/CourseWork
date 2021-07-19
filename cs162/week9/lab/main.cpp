/**************************************************************************************************
** Program Name:STL Stack and Queue
** Author:      Clinton Hawkes
** Date:        05/28/2019
** Description: This is the main function for the simulation program. The main is used to seed
                the random number function and then start the simulation. The Simulation class
                handles most of the function calls for the program.
**************************************************************************************************/

#include "Simulation.hpp"
#include <ctime>
#include <cstdlib>

int main(){

    srand(time(NULL));          //seed the rand() function
    
    system("clear"); 

    Simulation sim;

    sim.run();                  //starts the simulation

    return 0;

}

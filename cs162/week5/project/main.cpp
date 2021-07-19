/**************************************************************************************************
** Program Name:Fantasy Combat
** Author:      Clinton Hawkes
** Date:        05/02/2019
** Description: Main function for the Fantasy Combat game. Main is used to seed the rand()
                and to call the menu for testing the characters.
**************************************************************************************************/

#include "Menu.hpp"
#include <ctime>
#include <cstdlib>

int main(){

    srand(time(NULL));      //seeding the random number generator
    
    Menu menu;

    menu.test();            //function used for all testing
    
    return 0;

}

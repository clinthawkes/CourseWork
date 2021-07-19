/**************************************************************************************************
** Program Name:Circular List
** Author:      Clinton Hawkes
** Date:        05/14/2019
** Description: Main function is used to clear the console before calling the menu function. The
                menu is the driver of this program.
**************************************************************************************************/

#include "menu.hpp"
#include <iostream>

int main(){

    system("clear");

    menu();             //menu interacts with the queue structure
    
    return 0;
}

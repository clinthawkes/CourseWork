/*******************************************************************************    
** Program Name:War Games   
** Author:      Clinton Hawkes
** Date:        04/16/2019
** Description: Header file for the LoadedDie class. This contains the class
                variables and function prototypes. The implementation for these
                can be found in the LoadedDie.cpp file. This class is derived
                from the Die class.
*******************************************************************************/

#ifndef LOADEDDIE_HPP
#define LOADEDDIE_HPP
#include "Die.hpp"

class LoadedDie : public Die {
   
    private:
        long round;         //current round counter

    public:
        LoadedDie();
        ~LoadedDie();
        int rollDie();

};

#endif

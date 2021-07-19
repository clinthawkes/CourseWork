/**************************************************************************************************
** Program Name:STL Stack and Queue
** Author:      Clinton Hawkes
** Date:        05/28/2019
** Description: Header file for the Simulation class. Contains the functions needed to run the 
                simulation. Details of the functions below can be found in the implementation
                file. (Simulation.cpp)
**************************************************************************************************/

#ifndef SIMULATION_HPP
#define SIMULATION_HPP
#include <queue>
#include <stack>
#include <list>
#include <iostream>
#include <string>

class Simulation{

    private:

    public:
        Simulation();
        void run();
        void buffer();
        void printBuffer(std::queue<int, std::list<int>>); 
        std::string palindrome();
        int randomInt(int max);

};

#endif

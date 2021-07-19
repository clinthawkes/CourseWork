/**************************************************************************************************
** Program Name:Zoo Tycoon
** Author:      Clinton Hawkes
** Date:        04/21/2019
** Description: Header file for the Zoo class. The Zoo class is the brains of Zoo Tycoon. It is 
                responsible for calling functions, creating animal objects, managing memory and
                interacting with the user. This file contains the member variables and function
                prototypes used by the Zoo class. Detailed information about the various functions
                can be found in the Zoo.cpp file.
**************************************************************************************************/

#ifndef ZOO_HPP
#define ZOO_HPP
#include "Animal.hpp"
#include "Penguin.hpp"
#include "Tiger.hpp"
#include "Turtle.hpp"
#include "validation.hpp"
#include <fstream>

class Zoo{

    private:
        std::ifstream inFile;
        std::ofstream outFile;
        std::string message; 
        bool penguinParents,        //true if one or more penguins are age 3
             tigerParents,          //true if one or more tigers are age 3
             turtleParents;         //true if one or more turtles are age 3
        long bankBalance;           //bank account value
        int dayNumber,              //day counter
            bonus,                  //stores bonus for a day
            numPenguins,
            numTigers,
            numTurtles,
            penguinArraySize,
            tigerArraySize,
            turtleArraySize;
        Animal** penguinList;
        Animal** tigerList;
        Animal** turtleList;
         
    public:
        Zoo();
        ~Zoo();
        bool mainMenu();
        void run(); 
        void randomEvent();
        void sickness();
        void boom();
        void babyBorn();
        void addPenguin();
        void addTiger();
        void addTurtle();
        void removePenguin();
        void removeTiger();
        void removeTurtle();
        int dailyCost();
        int dailyPayoff();
        void ageAnimals(); 
        void checkIfAdult(); 
        void endOfDay(); 
        void buyAdult(); 
};

#endif

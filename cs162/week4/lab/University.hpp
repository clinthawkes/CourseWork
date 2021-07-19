/**************************************************************************************************
** Program Name:OSU Info System
** Author:      Clinton Hawkes
** Date:        04/24/2019
** Description: Header file for the University class. Contains the member variables and function
                prototypes used by the class. Implementation for the class can be found in the
                University.cpp file.
**************************************************************************************************/

#ifndef UNIVERSITY_HPP
#define UNIVERSITY_HPP
#include "Building.hpp"
#include "Person.hpp"
#include "Student.hpp"
#include "Instructor.hpp"
#include <string>
#include <vector>

class University {
    
    protected:
        std::string name;
        std::vector<Building*> buildings;
        std::vector<Person*> people;

    public:
        University();
        ~University(); 
        void printBuildingInfo();
        void printPeopleInfo();
        void run(); 
        void peopleMenu();
};

#endif


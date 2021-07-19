/**************************************************************************************************
** Program Name:OSU Info System 
** Author:      Clinton Hawkes
** Date:        04/24/2019
** Description: Header file for the Instructor class. Contains the member variable and function
                prototypes for the class. Implementation for the class can be found in the 
                Instructor.cpp file. Instructor is a derived class from the Person class.
**************************************************************************************************/

#ifndef INSTRUCTOR_HPP
#define INSTRUCTOR_HPP
#include "Person.hpp"

class Instructor : public Person{
    
    private:
        double rating;

    public:
        Instructor(); 
        Instructor(std::string, int, double); 
        ~Instructor(); 
        void do_work();
        void printGrade(); 
        double getRating();
        void setRating(double);

};

#endif

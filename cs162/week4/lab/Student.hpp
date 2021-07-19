/**************************************************************************************************
** Program Name:OSU Info System
** Author:      Clinton Hawkes
** Date:        04/24/2019
** Description: Header file for the Student class. Contains the member variable and function
                prototypes for the class. Implementation for the class can be found in the 
                Person.cpp file. Student is derived from the Person class.
**************************************************************************************************/

#ifndef STUDENT_HPP
#define STUDENT_HPP
#include "Person.hpp"

class Student : public Person {

    private:
        double GPA;

    public: 
        Student();
        Student(std::string, int, double); 
        ~Student(); 
        void do_work();
        void printGrade(); 
        double getGPA();
        void setGPA(double);
        
};

#endif

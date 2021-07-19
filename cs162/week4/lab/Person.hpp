/**************************************************************************************************
** Program Name:OSU Info System
** Author:      Clinton Hawkes
** Date:        04/24/2019
** Description: Header file for the Person class. Contains all the member variables and function
                prototypes used by the class. Implementation for the class can be found in the
                Person.cpp file.
**************************************************************************************************/

#ifndef PERSON_HPP
#define PERSON_HPP
#include <string>

class Person {

    protected:
        std::string name;
        int age;

    public:
        Person();
        Person(std::string, int); 
        ~Person(); 
        //abstract function used by Student and Instructor classes 
        virtual void do_work() = 0;
        //abstract function used by Student and Instructor classes 
        virtual void printGrade() = 0; 
        int getAge();
        void setAge(int);
        std::string getName();
        void setName(std::string);
}; 

#endif

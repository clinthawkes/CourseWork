/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/15/2019
** Description: This is the header file for the Person class. It contains the
                It contains the variable declarations and the constuctor/
                function prototypes.
*******************************************************************************/
#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

class Person
{
    private:
        std::string name;
        double age;

    public:
        Person(); 
        Person(std::string, double);
        std::string getName();
        double getAge();
};

#endif

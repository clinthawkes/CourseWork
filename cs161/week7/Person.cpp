/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/15/2019
** Description: Person.cpp contains the constructors and get functions for the 
                two variables of a Person object. The logic of the functions
                is detailed below.
*******************************************************************************/
#include "Person.hpp"
#include <string>

//default constructor for a Person object
Person::Person()
{   
    name = "";
    age = 0;
}

//constructor with parameter inputs for the Person object
Person::Person(std::string who, double years)
{
    name = who;
    age = years;
}

//returns the name of a Person object
std::string Person::getName()
{
    return name;
}

//returns the age of a Person object
double Person::getAge()
{
    return age;
}



/**************************************************************************************************
** Program Name:OSU Info System
** Author:      Clinton Hawkes
** Date:        04/24/2019
** Description: Implementation file for the Person class. The Person class stores the name and
                age of all Person objects. In addition to the member variables, this class 
                has two abstract functions that are defined in the derived classes.
**************************************************************************************************/

#include "Person.hpp"

//default constructor
Person::Person(){
    
    name = "";
    age = 17;
}

//constructor with two arguments
Person::Person(std::string name, int age){
    
    this->name = name;
    this->age = age;
}

//destructor
Person::~Person(){
}

//getter for the age variable
int Person::getAge(){
    
    return age;
}

//setter for the age variable
void Person::setAge(int age){
    
    this->age = age;
}

//getter for the name variable
std::string Person::getName(){
    
    return name;
}

//setter for the name variable
void Person::setName(std::string name){
    
    this->name = name;
}

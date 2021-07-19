/**************************************************************************************************
** Program Name:OSU Info System
** Author:      Clinton Hawkes
** Date:        04/24/2019
** Description: Implementation file for the Building class. The Building class stores the name,
                size and address of the buildings entered into the system. No member functions
                othere than constructors, getters and setters are needed in this class.
**************************************************************************************************/

#include "Building.hpp"

//default constructor
Building::Building(){

    name = "";
    address = "";
    size = 0;
}

//constructor with three arguments
Building::Building(std::string name, std::string address, long size){
    
    this->name = name;
    this->address = address;
    this->size = size;
}

//destructor
Building::~Building(){
}
    
//getter for the name variable
std::string Building::getName() const{
    
    return name;
}

//setter for the name variable
void Building::setName(std::string name){

    this->name = name;
}

//getter for the size variable
long Building::getSize() const{
    
    return size;
}

//setter for the size variable
void Building::setSize(long size){

    this->size = size;
}

//getter for the address variable
std::string Building::getAddress() const{
    
    return address;
}

//setter for the address variable
void Building::setAddress(std::string address){

    this->address = address;
}

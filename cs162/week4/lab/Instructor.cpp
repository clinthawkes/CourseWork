/**************************************************************************************************
** Program Name:OSU Info System     
** Author:      Clinton Hawkes
** Date:        04/24/2019
** Description: Implementation file for the Instructor class. The Instructor class stores info
                about the instructors of a University. They are representy by Instructor objects,
                which are devrived from the Person class. The Instructor class adds the member
                variable "rating" and inherits name and age. This class has two member functions
                that display information about it's objects. Further info can be found below.
**************************************************************************************************/

#include "Instructor.hpp"
#include <iostream>
#include <iomanip>

//default constructor
Instructor::Instructor(){
    
    rating = 0;
}

//constructor with three arguments
Instructor::Instructor(std::string name, int age, double rating){
    
    this->name = name;
    this->age = age;
    this->rating = rating;
}

//destructor
Instructor::~Instructor(){
}

//getter for rating of instructor
double Instructor::getRating(){
    
    return rating;
}

//setter for rating of instructor
void Instructor::setRating(double rating){
    
    this->rating = rating;
}

/**************************************************************************************************
** Description: Function overrides the abstract function in the Person's class to print out a 
                statement about an instructor grading papers for a certain amount of hours. The
                number of hours is a number between 1 and 12 generated randomly. 
**************************************************************************************************/
void Instructor::do_work(){
    
    //generates random number between 1 and 12 
    int random = rand()%12 + 1;

    std::cout << std::endl << name << " graded papers for " << random << " hours." << std::endl;
}

/**************************************************************************************************
** Description: Function prints out the "rating" member variable value when it is called.
**************************************************************************************************/
void Instructor::printGrade(){
    
    //makes print out of rating information consistent in appearance with one decimal point 
    std::cout << std::fixed << std::showpoint << std::setprecision(1); 
    
    std::cout << "Rating: " << rating << std::endl;
}


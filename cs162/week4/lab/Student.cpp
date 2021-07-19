/**************************************************************************************************
** Program Name:OSU Info System
** Author:      Clinton Hawkes
** Date:        04/24/2019
** Description: Implementation file for the Student class. The Student classs stores info about
                students of the University. The students are represented by Student objects in the
                class. The Student class is derived from the Person class and adds a member 
                variable "GPA". This class has two member functions that print out information
                about the students. More details of these functions can be found below.
**************************************************************************************************/

#include "Student.hpp"
#include <iostream>
#include <iomanip>

//default constructor
Student::Student(){
    
    GPA = 0;
}

//constructor with three arguments
Student::Student(std::string name, int age, double gpa){
    
    this->name = name;
    this->age = age;
    this->GPA = gpa;
}

//destructor
Student::~Student(){
}

//getter for GPA variable
double Student::getGPA(){
    
    return GPA;
}

//setter for GPA variable
void Student::setGPA(double GPA){
    
    this->GPA = GPA;
}

/**************************************************************************************************
** Description: Function overrides the abstract function in the Person class to print out a 
                statement about a student doing homework for a certain number of hours. The
                number of hours is a number between 1 and 14 generated randomly.
**************************************************************************************************/
void Student::do_work(){
    
    //generates a random number between 1 and 14 
    int random = rand()%14 + 1;

    std::cout << std::endl << name << " did " << random << " hours of homework." << std::endl;
}

/**************************************************************************************************
** Description: Function prints out the "GPA" variable value when it is called.
**************************************************************************************************/
void Student::printGrade(){
    
    //makes print out of GPA information consistent in appearance with one decimal point  
    std::cout << std::fixed << std::showpoint << std::setprecision(1); 
    
    std::cout << "GPA: " << GPA << std::endl;
}
    

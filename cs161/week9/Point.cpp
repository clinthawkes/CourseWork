/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/27/2019
** Description: File contains the constructors and the functions used by the
                Point class. 
*******************************************************************************/

#include "Point.hpp"
#include <cmath>

//default constructor  
Point::Point(){
    xCoord = 0;
    yCoord = 0;
}

//constructor taking in two doubles as arguments
Point::Point(double xInput, double yInput){
    xCoord = xInput;
    yCoord = yInput;
}

//setter function for xCoord variable
void Point::setXCoord(double xInput){
    xCoord = xInput;
}

//getter function for xCoord variable   
double Point::getXCoord(){
    return xCoord;
}

//setter function for yCoord variable
void Point::setYCoord(double yInput){
    yCoord = yInput;
}

//getter function for yCoord variable
double Point::getYCoord(){
    return yCoord;
}

/*******************************************************************************
** Description: This function calculates the distance between two points. The
                the distance formula is used on the calling Point object and
                the Point object passed as an argument.
*******************************************************************************/
double Point::distanceTo(Point location){
    double square;

    square = pow(getXCoord() - location.getXCoord(), 2) + pow(getYCoord() - location.getYCoord(), 2);

    return sqrt(square);
}

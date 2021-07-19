/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/27/2019
** Description: File contains the logic of the constuctors and functions used
                by the LineSegment class. More indepth description of the 
                functions is included below.
*******************************************************************************/

#include "LineSegment.hpp"

//default constructor   
LineSegment::LineSegment(){
    end1 = nullptr;
    end2 = nullptr;
}

//constructor taking in two Point pointers as arguments
LineSegment::LineSegment(Point* input1, Point* input2){
    end1 = input1;
    end2 = input2;
}

//setter function for end1
void LineSegment::setEnd1(Point* newPtr1){
    end1 = newPtr1;
}

//getter function for end1
Point* LineSegment::getEnd1(){
    return end1;
}

//setter function for end2
void LineSegment::setEnd2(Point* newPtr2){
    end2 = newPtr2;
}

//getter function for end2
Point* LineSegment::getEnd2(){
    return end2;
}

/*******************************************************************************
** Description: Calculates the length of the calling LineSegment object. Each
                LineSegment is composed of two Point objects. This function 
                uses the getter functions to retrieve end1 and end2. These are
                then used in the distanceTo function of the Point class to find
                the length.
*******************************************************************************/
double LineSegment::length(){
    return getEnd1()->distanceTo(*getEnd2());
}

/*******************************************************************************
** Description: Calculates the slope of the calling LineSegment object. This 
                retrieves the x and y coordinates of end1 and end2 variables 
                and uses the coordinates in the slope formula to calculate the
                slope.
*******************************************************************************/
double LineSegment::slope(){
    double yVal,
           xVal;

    yVal = getEnd2()->getYCoord() - getEnd1()->getYCoord();
    xVal = getEnd2()->getXCoord() - getEnd1()->getXCoord();

    return yVal/xVal;
}

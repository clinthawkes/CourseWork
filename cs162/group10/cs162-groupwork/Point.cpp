/******************************************************************************* 
** Program Name: Project 1 
** Author: Catrina Joos
** Date: 4/7/2019
** Description: Source Code for the point class
*******************************************************************************/
#include "Point.hpp"

// default constructor
Point::Point(){
	Point::setX(0);
	Point::setY(0);
}

// constructor with user input
Point::Point(int row, int column){
	Point::setX(column);
	Point::setY(row);
}

// mutator
void Point::setX(int x){
	xCoord=x;
}

//accessor
int Point::getX(){
	return xCoord;
}
// mutator
void Point::setY(int y){
	yCoord=y;
}

//accessor
int Point::getY(){
	return yCoord;
}

//moves point to the left
void Point::moveLeft(){
	Point::setX(xCoord-1);
}

//moves point to the right
void Point::moveRight(){
	Point::setX(xCoord+1);
}

//moves point up
void Point::moveUp(){
	Point::setY(yCoord-1);
}

//moves point down
void Point::moveDown(){
	Point::setY(yCoord+1);
}


bool Point::isEqual(Point p){
	if(this->getX() == p.getX() && this->getY() == p.getY()){
		return true;
	}
	return false;
}

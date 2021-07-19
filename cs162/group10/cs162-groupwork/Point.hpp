/******************************************************************************* 
** Program Name: Langton's Ant/Project 1
** Author: Catrina Joos
** Date: 4/7/2019 
** Description: Point Header File
*******************************************************************************/

#ifndef POINT_HPP
#define POINT_HPP

class Point {

	private:
		int xCoord;
		int yCoord;
        
	public:
		Point(int,int);
		Point();
		bool isEqual(Point);
		void setX(int);
		void setY(int);
		int getX();
		int getY();
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();

};
#endif


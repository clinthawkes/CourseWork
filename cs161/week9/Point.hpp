/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/27/2019
** Description: Header file for the Point class. Declares the variables of the
                Point objects and includes the function prototypes for the 
                class.
*******************************************************************************/

#ifndef POINT_HPP
#define POINT_HPP

class Point
{
    private:
        double xCoord,
               yCoord;

    public:
        Point();
        Point(double, double);
        void setXCoord(double);
        double getXCoord();
        void setYCoord(double);
        double getYCoord();
        double distanceTo(Point);
};

#endif

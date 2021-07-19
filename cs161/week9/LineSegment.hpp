/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/27/2019
** Description: Header file for the LineSegment classs. This declares the 
                variables used as Point pointers and includes the constructors
                and function prototypes used by the class. The logic of the 
                functions is included in the LineSegment.cpp file.
*******************************************************************************/

#ifndef LINESEGMENT_HPP
#define LINESEGMENT_HPP
#include "Point.hpp"

class LineSegment
{
    private:
        Point* end1;
        Point* end2;
        
    public:
        LineSegment(); 
        LineSegment(Point*, Point*);
        void setEnd1(Point*);
        Point* getEnd1();
        void setEnd2(Point*);
        Point* getEnd2();
        double length();
        double slope();
};

#endif

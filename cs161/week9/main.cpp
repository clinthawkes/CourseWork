#include <iostream>
#include "LineSegment.hpp"

using std::cout;
using std::cin;
using std::endl;

int main()
{
    Point p1(4.3, 7.52);
    Point p2(-17.0, 1.5);
    LineSegment ls1(&p1, &p2);
    double length = ls1.length();
    double slope = ls1.slope();
     
    cout << "x of end 2 is " << ls1.getEnd2()->getXCoord() << endl; 
    cout << "y of end 2 is " << ls1.getEnd2()->getYCoord() << endl; 
    cout << "x of end 1 is " << ls1.getEnd1()->getXCoord() << endl; 
    cout << "y of end 1 is " << ls1.getEnd1()->getYCoord() << endl;
    cout << length << endl;
    cout << slope << endl;
    
    ls1.setEnd2(&p1);
    ls1.setEnd1(&p2); 
    cout << "x of end 2 is " << ls1.getEnd2()->getXCoord() << endl; 
    cout << "y of end 2 is " << ls1.getEnd2()->getYCoord() << endl; 
    cout << "x of end 1 is " << ls1.getEnd1()->getXCoord() << endl; 
    cout << "y of end 1 is " << ls1.getEnd1()->getYCoord() << endl;
    cout << ls1.length() << endl;
    cout << ls1.slope() << endl;
    
    ls1.getEnd2()->setXCoord(22);
    ls1.getEnd1()->setXCoord(33);
    cout << "x of end 2 is " << ls1.getEnd2()->getXCoord() << endl; 
    cout << "y of end 2 is " << ls1.getEnd2()->getYCoord() << endl; 
    cout << "x of end 1 is " << ls1.getEnd1()->getXCoord() << endl; 
    cout << "y of end 1 is " << ls1.getEnd1()->getYCoord() << endl;
    cout << ls1.length() << endl;
    cout << ls1.slope() << endl;
    
    ls1.getEnd2()->setYCoord(2);
    ls1.getEnd1()->setYCoord(2);
    cout << "x of end 2 is " << ls1.getEnd2()->getXCoord() << endl; 
    cout << "y of end 2 is " << ls1.getEnd2()->getYCoord() << endl; 
    cout << "x of end 1 is " << ls1.getEnd1()->getXCoord() << endl; 
    cout << "y of end 1 is " << ls1.getEnd1()->getYCoord() << endl;
    cout << ls1.length() << endl;
    cout << ls1.slope() << endl;
    
    return 0;
}

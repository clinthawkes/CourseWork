/*******************************************************************************    
** Name:        Clinton Hawkes
** Date:        02/03/2019
** Description: 
*******************************************************************************/

#include <iostream>
#include "Box.hpp"

using std::cout;
using std::cin;
using std::endl;

int main()
{
    Box box1(2.4, 7.1, 5.0);
    Box box2;
    double volume1 = box1.calcVolume();
    double surfaceArea1 = box1.calcSurfaceArea();
    double volume2 = box2.calcVolume();
    double surfaceArea2 = box2.calcSurfaceArea();

    cout << "This is what the file prints when ran." << endl;
    cout << volume1 << endl;
    cout << surfaceArea1 << endl;
    cout << volume2 << endl;
    cout << surfaceArea2 << endl;
    
    box2.setHeight(2.0);
    box2.setWidth(4.0);
    box2.setLength(6.0);
    
    cout << "The volume of 2 is " << box2.calcVolume() << endl;
    cout << "The surface area of 2 is " << box2.calcSurfaceArea() << endl;


    return 0;
}

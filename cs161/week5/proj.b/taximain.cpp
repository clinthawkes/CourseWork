#include "Taxicab.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    Taxicab cab1;
    Taxicab cab2(5, -8);

    cab1.moveX(3);
    cab1.moveY(-4);
    cab1.moveX(-1);
    cout << cab1.getDistanceTraveled() << endl;
    cout << cab1.getYCoord() << endl; 
    cout << cab1.getXCoord() << endl; 
    cab2.moveY(7);
    cab2.moveX(-5); 
    cout << cab2.getDistanceTraveled() << endl;
    cout << cab2.getYCoord() << endl;
    cout << cab2.getXCoord() << endl; 
    cout << "Total of both cars is " << cab1.getDistanceTraveled() + cab2.getDistanceTraveled() << endl; 

    return 0;
}

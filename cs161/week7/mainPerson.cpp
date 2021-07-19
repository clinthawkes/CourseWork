#include <iostream>
#include "Person.hpp"

using std::cout;
using std::endl;

double stdDev(Person [], int);

int main()
{
    double stdev;    
    Person group[]={Person("me", 53), Person("you", 30), Person("him", 15)};

    stdev = stdDev(group, 3);

    cout << "The standard deviation is " << stdev << endl;
    cout << "Person two is " << group[1].getName() << endl; 

    return 0;
}
    

    

/**************************************************************************************
 * Name:        Clinton Hawkes
 * Date:        January 27, 2019
 * Description: Function fallDistance takes in some double argument and returns
 *              calculation from formula d=(1/2)gt^2.
 *************************************************************************************/  
/*
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

function prototype
double fallDistance (double);


int main()
{
    double time,
           distance;
    
    cout << "How many seconds has the object been falling?" << endl;
    cin >> time;

    distance = fallDistance (time);

    cout << "The object fell " << distance << " meters." << endl;

    return 0;
}
*/

/**************************************************************************************
 * Description: Takes in a double argument and returns a double after calculating
 *              the fall distance in meters.
 *************************************************************************************/

const double GRAVITY = 9.8;

double fallDistance (double fallTime)
{
    return (.5 * GRAVITY * (fallTime * fallTime));
}




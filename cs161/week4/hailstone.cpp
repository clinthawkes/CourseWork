/**************************************************************************************
 * Name:        Clinton Hawkes
 * Date:        January 27, 2019
 * Description: Function receives int argument, checks if int is even or odd, if it 
 *              is even it divides it by 2 and that becomes the new value. If the int
 *              is odd, it is multiplied by 3 and adds 1. Loop continues to evaluate
 *              and manipulate until the value of the int is 1. Then the number of
 *              steps it took to get to 1 is returned to the main function.
 **************************************************************************************/
/*
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int hailstone (int);


int main ()
{
    int number,
        count;  
    
    cout << "Please enter a starting integer." << endl;
    cin >> number;

    count = hailstone(number);

    cout << "It took " << count << " steps to reach 1." << endl;

    return 0;
}
*/

/*************************************************************************************
 * Description: See the summary above.
 ************************************************************************************/

int hailstone (int start)
{
    int steps = 0;                      //initialized variable used for counting 
    
    while (start != 1)                  //loops until start == 1
    {   
        if (start % 2 == 0)
            start /= 2;                 //divides start by 2 if even    
        else
            start = (start * 3) + 1;    //multiplies start by 3 and adds 1 if odd

        steps++;                        //increases counting variable with each loop
    }
    return steps;                       //returns number of steps when start == 1
}

/***********************************************************************************************************************
 * Name:        Clinton Hawkes
 * Date:        01/19/2019
 * Description: Asks user how many integers they would like to enter. User enters that number of integers and then
 *              receives a print out of the min and max of their entries.
 **********************************************************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
    int min,            //declare int variables
        max,
        numTests,
        numIn;

    //asks user how many integers they would like to enter 
    cout << "How many integers would you like to enter?" << endl;
    cin >> numTests;

    //asks user to enter the number of integers they specified  
    cout << "Please enter " << numTests << " integers." << endl;
    cin >> numIn;
    min=max=numIn;

    //loops until the number of integers entered matches user's specifications 
    for ( int count = 2; count <= numTests ; count++ ) 
    {        
        cin >> numIn;

        //evaluates entered number against min and max values 
        if (numIn < min)
            min = numIn;
        else if (numIn > max)
            max = numIn;
    }

    //prints out the min and max of the numbers entered 
    cout << "min: " << min << endl;
    cout << "max: " << max << endl;

    return 0;
}



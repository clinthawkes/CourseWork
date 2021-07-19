#include <iostream>

using std::cout;
using std::endl;

double findMedian(int [], int);


int main()
{
    int size = 4; 
    int array[size] = {10,11,10,11};
    double median;

    median = findMedian(array, size);

    cout << "The median is " << median << endl;

    return 0;
}
    

    
